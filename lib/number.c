/* number.c: Implements arbitrary precision numbers. */
/*
    Copyright (C) 1991, 1992, 1993, 1994, 1997, 2000, 2012-2017 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License , or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to:

      The Free Software Foundation, Inc.
      51 Franklin Street, Fifth Floor
      Boston, MA 02110-1301  USA


    You may contact the author by:
       e-mail:  philnelson@acm.org
      us-mail:  Philip A. Nelson
                Computer Science Department, 9062
                Western Washington University
                Bellingham, WA 98226-9062
       
*************************************************************************/

#include <stdio.h>
#include <config.h>
#include <number.h>
#include <assert.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <ctype.h>

/* Prototypes needed for external utility routines. */

#define bc_rt_warn rt_warn
#define bc_rt_error rt_error
#define bc_out_of_memory out_of_memory

#define	COMP(a, b)	( (a) > (b) ? 1 : ( (a) < (b) ? -1 : 0 ) )
#define	SIGN(a)		( (a) > 0 ? 1 : ( (a) < 0 ? -1 : 0) )
#define	TO_SCALE(dec_scale)			( ( (dec_scale) + LOG10_RADIX - 1 ) / LOG10_RADIX )
//#define	TO_EVEN_SCALE(dec_scale)	( 2 * ( ( (dec_scale) + 2*LOG10_RADIX - 1 ) / (2*LOG10_RADIX) ) )

void rt_warn (const char *mesg ,...);
void rt_error (const char *mesg ,...);
void out_of_memory (void);

extern dig_t	g_pow10[];

/* Storage used for special numbers. */
bc_num  _zero_;
bc_num  _one_;
bc_num  _two_;

static bc_num _bc_Free_list = NULL;

/* new_num allocates a number and sets fields to known values. */

bc_num
bc_new_num (len_t len, len_t scale)
{
	bc_num temp;
	len_t size;

	if(len < 0)
	{
		len = 0;
	}
	if(scale < 0)
	{
		scale = 0;
	}

	size = len + scale + 1;

	if (_bc_Free_list != NULL)
	{
		temp = _bc_Free_list;
		_bc_Free_list = temp->n_next;
	}
	else
	{
		temp = (bc_num) malloc (sizeof(bc_struct));
		if (temp == NULL)
			bc_out_of_memory ();
	}
	temp->n_sign = 0;
	temp->n_len = 0;
	temp->n_scale = scale;
	temp->n_dec_scale = LOG10_RADIX*scale;
	temp->n_refs = 1;
	temp->n_value = bi_malloc(size, __LINE__);
	if (temp->n_value == NULL)
		bc_out_of_memory();
	memset (temp->n_value, 0, temp->n_scale*sizeof(dig_t));
	return temp;
}

// Duplicate
bc_num
bc_dup_num (bc_num num)
{
	bc_num	n = bc_new_num(num->n_len, num->n_scale);
	n->n_sign = num->n_sign;
	n->n_len = num->n_len;
	n->n_dec_scale = num->n_dec_scale;
	memcpy(n->n_value, num->n_value, sizeof(dig_t)*(n->n_len + n->n_scale));
	return n;
}

// length in decimal
len_t
bc_dec_len(bc_num num)
{
	if(num->n_len <= 0)
	{
		return num->n_dec_scale > 0 ? num->n_dec_scale : 1;
	}
	else
	{
		len_t	rscale = TO_SCALE(num->n_dec_scale);
		len_t	len = bi_b10_len(num->n_value + (num->n_scale - rscale), rscale + num->n_len);
		if(len <= 0)
		{
			len = 1;
		}
		return len;
	}
}

/* "Frees" a bc_num NUM.  Actually decreases reference count and only
   frees the storage if reference count is zero. */

void
bc_free_num (bc_num *num)
{
	if (*num == NULL)
		return;
	(*num)->n_refs--;
	if ((*num)->n_refs == 0)
	{
		if ((*num)->n_value)
			free ((*num)->n_value);
		(*num)->n_next = _bc_Free_list;
		_bc_Free_list = *num;
	}
	*num = NULL;
}

/* Intitialize the number package! */

void
bc_init_numbers (void)
{
	_zero_ = bc_new_num (1,0);

	_one_  = bc_new_num (1,0);
	_one_->n_sign = 1;
	_one_->n_value[0] = 1;
	_one_->n_len = 1;

	_two_  = bc_new_num (1,0);
	_two_->n_sign = 1;
	_two_->n_value[0] = 2;
	_two_->n_len = 1;
}


/* Make a copy of a number!  Just increments the reference count! */

bc_num
bc_copy_num (bc_num num)
{
	num->n_refs++;
	return num;
}


/* Initialize a number NUM by making it a copy of zero. */

void
bc_init_num (bc_num *num)
{
	*num = bc_copy_num (_zero_);
}

#if	0
/* For many things, we may have leading zeros in a number NUM.
   _bc_rm_leading_zeros just moves the data "value" pointer to the
   correct place and adjusts the length. */
// Now, just decrease num->n_len.
static void
_bc_rm_leading_zeros (bc_num num)
{
	/* We can move n_value to point to the first non zero digit! */
	len_t i = num->n_scale + num->n_len - 1;
	while (i >= num->n_scale && num->n_value[i] == 0)
	{
		i--;
	}
	i++;
	num->n_len = i - num->n_scale;
}
#endif

/* Compare two bc numbers.  Return value is 0 if equal, -1 if N1 is less
   than N2 and +1 if N1 is greater than N2.  If USE_SIGN is false, just
   compare the magnitudes. */

static int
_bc_do_compare (bc_num n1, bc_num n2, int use_sign)//, int ignore_last )
{
	len_t i1, i2;
	int dir = (!use_sign || n1->n_sign >= 0) ? 1 : -1;

	if (use_sign && n1->n_sign != n2->n_sign)
	{
		return COMP(n1->n_sign, n2->n_sign);
	}

	if (n1->n_len != n2->n_len)
	{
		return dir * COMP(n1->n_len, n2->n_len);
	}

	i1 = n1->n_len + n1->n_scale - 1;
	i2 = n2->n_len + n2->n_scale - 1;
	while(i1 >= 0 && i2 >= 0 && n1->n_value[i1] == n2->n_value[i2])
	{
		i1--;
		i2--;
	}
	if(i1 >= 0 && i2 >= 0)
	{
		return dir * COMP(n1->n_value[i1], n2->n_value[i2]);
	}
	while(i1 >= 0 && n1->n_value[i1] == 0)
	{
		i1--;
	}
	while(i2 >= 0 && n2->n_value[i2] == 0)
	{
		i2--;
	}
	if(i1 >= 0)
	{
		return dir;
	}
	if(i2 >= 0)
	{
		return -dir;
	}
	return 0;
}

/* This is the "user callable" routine to compare numbers N1 and N2. */

int
bc_compare ( bc_num n1, bc_num n2 )
{
	return _bc_do_compare (n1, n2, TRUE);//, FALSE);
}

/* In some places we need to check if the number is negative. */

char
bc_is_neg (bc_num num)
{
	return (num->n_sign < 0);
}

/* In some places we need to check if the number NUM is zero. */

char
bc_is_zero (bc_num num)
{
	return (0 == num->n_sign);
#if 0
	len_t i;

	if (num == _zero_)
		return TRUE;

	if(num->n_len > 0)
	{
		return FALSE;
	}
	if(num->n_scale <= 0)
	{
		return TRUE;
	}
	for(i = 0; i < num->n_scale; i++)
	{
		if(num->n_value[i])
		{
			return FALSE;
		}
	}
	return TRUE;
#endif
}

/* Perform addition: N1 is added to N2 and the value is
   returned.  The signs of N1 and N2 are ignored.
   SCALE_MIN is to set the minimum scale of the result. */

// must be |n1| > 0 or |n2| > 0
static bc_num
_bc_do_add (bc_num n1, bc_num n2, len_t dec_scale_min)
{
	bc_num	sum;
	len_t	len, scale, dec_scale, g1, g2, l1, l2;

	len = MAX(n1->n_len, n2->n_len);
	len++;

	scale = MAX(n1->n_scale, n2->n_scale);
	scale = MAX(scale, TO_SCALE(dec_scale_min));

	dec_scale = MAX(n1->n_dec_scale, n2->n_dec_scale);
	dec_scale = MAX(dec_scale, dec_scale_min);

	sum = bc_new_num(len, scale);

	g1 = scale - n1->n_scale;
	g2 = scale - n2->n_scale;

	memset(sum->n_value, 0, sizeof(dig_t)*g1);
	memcpy(sum->n_value + g1, n1->n_value, sizeof(dig_t)*(n1->n_scale+n1->n_len));
	for(l1 = g1 + n1->n_scale + n1->n_len - 1; l1 >= 0 && 0 == sum->n_value[l1]; l1--)
	{
		;
	}
	l1++;
	for(l2 = n2->n_scale + n2->n_len - 1; l2 >= 0 && 0 == n2->n_value[l2]; l2--)
	{
		;
	}
	l2++;

	len = l1;
	bi_add_shift(sum->n_value, &len, n2->n_value, l2, g2);
	if(len >= scale)
	{
		sum->n_len = len - scale;
	}
	else
	{
		sum->n_len = 0;
	}
	sum->n_dec_scale = dec_scale;
	//if(bc_is_zero(sum))
	//{
	//	sum->n_sign = 0;
	//}
	//else
	//{
		sum->n_sign = 1;
	//}
	return sum;
}


/* Perform subtraction: N2 is subtracted from N1 and the value is
   returned.  The signs of N1 and N2 are ignored.  Also, N1 is
   assumed to be larger than N2.  SCALE_MIN is the minimum scale
   of the result. */

// must be |n1| > |n2|
static bc_num
_bc_do_sub (bc_num n1, bc_num n2, len_t dec_scale_min)
{
	bc_num	sum;
	len_t	len, scale, dec_scale, g1, g2, l1, l2;

	len = MAX(n1->n_len, n2->n_len);
	len++;

	scale = MAX(n1->n_scale, n2->n_scale);
	scale = MAX(scale, TO_SCALE(dec_scale_min));

	dec_scale = MAX(n1->n_dec_scale, n2->n_dec_scale);
	dec_scale = MAX(dec_scale, dec_scale_min);

	sum = bc_new_num(len, scale);

	g1 = scale - n1->n_scale;
	g2 = scale - n2->n_scale;

	memset(sum->n_value, 0, sizeof(dig_t)*g1);
	memcpy(sum->n_value + g1, n1->n_value, sizeof(dig_t)*(n1->n_scale+n1->n_len));
	for(l1 = g1 + n1->n_scale + n1->n_len - 1; l1 >= 0 && 0 == sum->n_value[l1]; l1--)
	{
		;
	}
	l1++;
	for(l2 = n2->n_scale + n2->n_len - 1; l2 >= 0 && 0 == n2->n_value[l2]; l2--)
	{
		;
	}
	l2++;

	len = l1;
	bi_sub_shift(sum->n_value, &len, n2->n_value, l2, g2);
	if(len >= scale)
	{
		sum->n_len = len - scale;
	}
	else
	{
		sum->n_len = 0;
	}
	sum->n_dec_scale = dec_scale;
	//if(bc_is_zero(sum))
	//{
	//	sum->n_sign = 0;
	//}
	//else
	//{
		sum->n_sign = 1;
	//}
	return sum;
}


/* Here is the full subtract routine that takes care of negative numbers.
   N2 is subtracted from N1 and the result placed in RESULT.  SCALE_MIN
   is the minimum scale for the result. */

void
bc_sub (bc_num n1, bc_num n2, bc_num *result, len_t dec_scale_min)
{
	bc_num	diff;
	len_t	scale, dec_scale;

	scale = MAX(n1->n_scale, n2->n_scale);
	scale = MAX(scale, TO_SCALE(dec_scale_min));
	dec_scale = MAX(n1->n_dec_scale, n2->n_dec_scale);
	dec_scale = MAX(dec_scale, dec_scale_min);

	if(n1->n_sign * n2->n_sign <= 0)
	{
		if(0 != n1->n_sign || 0 != n2->n_sign)
		{
			diff = _bc_do_add(n1, n2, dec_scale_min);
			if(n1->n_sign <= n2->n_sign)
			{
				diff->n_sign = -diff->n_sign;
			}
		}
		else
		{
			diff = bc_new_num(1, scale);
			diff->n_dec_scale = dec_scale;
		}
	}
	else
	{
		int		cmp_res = _bc_do_compare(n1, n2, FALSE);//, FALSE);

		if(cmp_res < 0)
		{
			// +100 - +200
			// -100 - -200
			diff = _bc_do_sub(n2, n1, dec_scale_min);
			diff->n_sign = -n1->n_sign;
		}
		else if(cmp_res > 0)
		{
			// +200 - +100
			// -200 - -100
			diff = _bc_do_sub(n1, n2, dec_scale_min);
			diff->n_sign = n1->n_sign;
		}
		else	// 0.000000
		{
			diff = bc_new_num(1, scale);
			diff->n_dec_scale = dec_scale;
		}
	}
	bc_free_num(result);
	*result = diff;
}


/* Here is the full add routine that takes care of negative numbers.
   N1 is added to N2 and the result placed into RESULT.  SCALE_MIN
   is the minimum scale for the result. */

// scale_min --> dec scale
void
bc_add (bc_num n1, bc_num n2, bc_num *result, len_t dec_scale_min)
{
	bc_num	diff;
	len_t	scale, dec_scale;

	scale = MAX(n1->n_scale, n2->n_scale);
	scale = MAX(scale, TO_SCALE(dec_scale_min));
	dec_scale = MAX(n1->n_dec_scale, n2->n_dec_scale);
	dec_scale = MAX(dec_scale, dec_scale_min);

	if(n1->n_sign * n2->n_sign >= 0)
	{
		if(0 != n1->n_sign || 0 != n2->n_sign)
		{
			diff = _bc_do_add(n1, n2, dec_scale_min);
			diff->n_sign = (n1->n_sign > 0 || n2->n_sign > 0 ? 1 : -1);
		}
		else
		{
			diff = bc_new_num(1, scale);
			diff->n_dec_scale = dec_scale;
		}
	}
	else
	{
		int		cmp_res = _bc_do_compare (n1, n2, FALSE);//, FALSE);  /* Compare magnitudes. */

		if(cmp_res < 0)
		{
			// +100 + -200
			// -100 + +200
			diff = _bc_do_sub (n2, n1, dec_scale_min);
			diff->n_sign = n2->n_sign;
		}
		else if(cmp_res > 0)
		{
			// +200 + -100
			// -200 + +100
			diff = _bc_do_sub (n1, n2, dec_scale_min);
			diff->n_sign = n1->n_sign;
		}
		else	// 0.00000
		{
			diff = bc_new_num(1, scale);
			diff->n_dec_scale = dec_scale;
		}
	}
	bc_free_num(result);
	*result = diff;
}

/* Recursive vs non-recursive multiply crossover ranges. */
#if defined(MULDIGITS)
#include "muldigits.h"
#else
#define MUL_BASE_DIGITS 80
#endif

int mul_base_digits = MUL_BASE_DIGITS;
#define MUL_SMALL_DIGITS mul_base_digits/4

void
bc_clear_extra_fraction(bc_num num)
{
	int	not_zero = 0;
	len_t	i = num->n_scale - 1, dec_scale = num->n_dec_scale;

	while(dec_scale > LOG10_RADIX)
	{
		if(!not_zero && num->n_value[i])
		{
			not_zero = 1;
		}
		dec_scale -= LOG10_RADIX;
		i--;
	}
	if(dec_scale > 0)
	{
		num->n_value[i] -= ( num->n_value[i] % g_pow10[LOG10_RADIX - dec_scale] );
		if(!not_zero && num->n_value[i])
		{
			not_zero = 1;
		}
		i--;
	}
	while(i >= 0)
	{
		num->n_value[i--] = 0;
	}
	if(num->n_len <= 0 && !not_zero)
	{
		num->n_sign = 0;
	}
}

/* The multiply routine.  N2 times N1 is put int PROD with the scale of
   the result being MIN(N2 scale+N1 scale, MAX (SCALE, N2 scale, N1 scale)).
   */

void
bc_multiply (bc_num n1, bc_num n2, bc_num *prod, len_t dec_scale)
{
	bc_num	pval; 
	len_t	scale1 = TO_SCALE(n1->n_dec_scale);
	len_t	scale2 = TO_SCALE(n2->n_dec_scale);
	len_t	full_dec_scale, prod_dec_scale;
	dig_t	*tn1, *tn2;
	len_t	tn1len, tn2len;

	full_dec_scale = n1->n_dec_scale + n2->n_dec_scale;
	prod_dec_scale = MAX(n1->n_dec_scale, n2->n_dec_scale);
	prod_dec_scale = MAX(dec_scale, prod_dec_scale);
	prod_dec_scale = MIN(full_dec_scale, prod_dec_scale);

	tn1 = n1->n_value + (n1->n_scale - scale1);
	tn1len = scale1 + n1->n_len;

	tn2 = n2->n_value + (n2->n_scale - scale2);
	tn2len = scale2 + n2->n_len;

	pval = bc_new_num(tn1len + tn2len, 0);

	tn1len--;
	while(tn1len >= 0 && tn1[tn1len] == 0)
	{
		tn1len--;
	}
	tn1len++;

	tn2len--;
	while(tn2len >= 0 && tn2[tn2len] == 0)
	{
		tn2len--;
	}
	tn2len++;

	bi_mul2(
		tn1, tn1len,
		tn2, tn2len,
		pval->n_value, &pval->n_len);
	pval->n_sign = n1->n_sign*n2->n_sign;
	pval->n_scale = scale1 + scale2;
	if(pval->n_len >= pval->n_scale)
	{
		pval->n_len -= pval->n_scale;
	}
	else
	{
		len_t	i;
		for(i = pval->n_len; i < pval->n_scale; i++)
		{
			pval->n_value[i] = 0;
		}
		pval->n_len = 0;
	}
	pval->n_dec_scale = prod_dec_scale;
	bc_clear_extra_fraction(pval);

	bc_free_num (prod);
	*prod = pval;
}

int bc_factorial(bc_num *n)
{
	len_t	in;
	dig_t*	res;
	len_t	reslen;
	bc_num	nn = *n;

	if(!bc_num2long(nn, &in))
	{
		bc_rt_error ("input too large in F(n)");
		return 0;
	}
	if(in < 0)
	{
		return 0;
	}

	bi_fac(0, in, &res, &reslen, NULL);

	nn = bc_new_num(1, 0);
	nn->n_len = reslen;
	nn->n_sign = 1;

	bi_free(nn->n_value);
	nn->n_value = res;

	bc_free_num(n);
	*n = nn;
	return 1;
}

int bc_permutation(bc_num *n, bc_num *r)
{
	len_t	in, ir;
	dig_t*	res;
	len_t	reslen;
	bc_num	nn = *n, rr = *r;

	if(!bc_num2long(nn, &in) || !bc_num2long(rr, &ir))
	{
		bc_rt_error ("inputs too large in P(n,r)");
		return 0;
	}
	if(in < 0 || ir <= 0 || in < ir)
	{
		return 0;
	}

	bi_fac(in-ir, in, &res, &reslen, NULL);

	nn = bc_new_num(1, 0);
	nn->n_len = reslen;
	nn->n_sign = 1;

	bi_free(nn->n_value);
	nn->n_value = res;

	bc_free_num(n);
	*n = nn;
	return 1;
}

int bc_combination(bc_num *n, bc_num *r)
{
	len_t in, ir;
	dig_t *p1, *p2;
	len_t p1len, p2len, zn;
	bc_num nn = *n, rr = *r;

	if(!bc_num2long(nn, &in) || !bc_num2long(rr, &ir))
	{
		bc_rt_error ("inputs too large in C(n,r)");
		return 0;
	}
	if(in < 0 || ir < 0 || in < ir)
	{
		return 0;
	}

	if(in-ir < ir)
	{
		ir = in-ir;
	}

	bi_fac(in-ir, in, &p1, &p1len, NULL);
	bi_fac(0, ir, &p2, &p2len, NULL);

	for(zn = 0; 0 == p1[zn] && 0 == p2[zn]; zn++)
	{
		;
	}
	p1len -= zn;
	p2len -= zn;

	nn = bc_new_num(p1len - p2len + 1, 0);
	nn->n_sign = 1;

	bi_div1(p1+zn, &p1len, p2+zn, p2len, nn->n_value, &(nn->n_len));

	bi_free(p1);
	bi_free(p2);

	assert(p1len == 0);

	bc_free_num(n);
	*n = nn;
	return 1;
}

/* The full division routine. This computes N1 / N2.  It returns
   0 if the division is ok and the result is in QUOT.  The number of
   digits after the decimal point is SCALE. It returns -1 if division
   by zero is tried.  The algorithm is found in Knuth Vol 2. p237. */

int
bc_divide (bc_num n1, bc_num n2, bc_num *quot, len_t dec_scale)
{
	dig_t	*a, *b, *temp1 = (dig_t*)0, *temp2 = (dig_t*)0;
	len_t	alen, blen, qlen, scale, scale1, scale2;
	bc_num	qval;

	if(0 == n2->n_sign)
	{
		return -1;
	}

	scale = TO_SCALE(dec_scale);

	scale1 = TO_SCALE(n1->n_dec_scale);
	a = n1->n_value + (n1->n_scale - scale1);
	alen = scale1 + n1->n_len;

	scale2 = TO_SCALE(n2->n_dec_scale);
	b = n2->n_value + (n2->n_scale - scale2);
	blen = scale2 + n2->n_len;

	if(scale1 == scale2)
	{
		if(dec_scale <= 0)
		{
		}
		else
		{
			temp1 = bi_malloc(scale + alen, __LINE__);
			memcpy(temp1, a, sizeof(dig_t)*alen);
			a = temp1;
		}
	}
	else if(scale1 > scale2)
	{
		len_t	d = scale1 - scale2;

		if(dec_scale <= 0)
		{
		}
		else
		{
			temp1 = bi_malloc(scale + alen, __LINE__);
			memcpy(temp1, a, sizeof(dig_t)*alen);
			a = temp1;
		}
		temp2 = bi_malloc(d + blen, __LINE__);
		memset(temp2, 0, sizeof(dig_t)*d);
		memcpy(temp2 + d, b, sizeof(dig_t)*blen);
		b = temp2;
		blen += d;
	}
	else
	{
		len_t	d = scale2 - scale1;

		temp1 = bi_malloc(scale + d + alen, __LINE__);
		memset(temp1, 0, sizeof(dig_t)*d);
		memcpy(temp1 + d, a, sizeof(dig_t)*alen);
		a = temp1;
		alen += d;
	}

	{
		len_t	i;

		for(i = alen-1; i >= 0 && a[i] == 0; i--)
		{
			;
		}
		alen = i+1;

		for(i = blen-1; i >= 0 && b[i] == 0; i--)
		{
			;
		}
		blen = i+1;
	}

	if(alen > 0 && dec_scale > 0)
	{
		len_t	i;

		for(i = alen-1; i >= 0; i--)
		{
			a[i+scale] = a[i];
		}
		for(i = 0; i < scale; i++)
		{
			a[i] = 0;
		}
		alen += scale;
	}

	qval = bc_new_num(alen - blen + 1, scale);
	qval->n_dec_scale = dec_scale;

	bi_div2(a, alen, b, blen, qval->n_value, &qlen, NULL, NULL);
	if(temp1)
	{
		bi_free(temp1);
	}
	if(temp2)
	{
		bi_free(temp2);
	}

	if(qlen <= qval->n_scale)
	{
		memset(qval->n_value + qlen, 0, sizeof(dig_t)*(qval->n_scale - qlen));
		qval->n_len = 0;
	}
	else
	{
		qval->n_len = qlen - qval->n_scale;
	}

	qval->n_sign = n1->n_sign * n2->n_sign;
	bc_clear_extra_fraction(qval);
	*quot = qval;

	return 0;
}


/* Division *and* modulo for numbers.  This computes both NUM1 / NUM2 and
   NUM1 % NUM2  and puts the results in QUOT and REM, except that if QUOT
   is NULL then that store will be omitted.
 */

int
bc_divmod (bc_num num1, bc_num num2, bc_num *quot, bc_num *rem, len_t dec_scale)
{
	bc_num	quotient = NULL;
	bc_num	temp;
	len_t	r_dec_scale;

	/* Check for correct numbers. */
	if (bc_is_zero (num2))
		return -1;

	/* Calculate final scale. */
	r_dec_scale = MAX (num1->n_dec_scale, num2->n_dec_scale + dec_scale);
	bc_init_num(&temp);

	/* Calculate it. */
	bc_divide (num1, num2, &temp, dec_scale);
	if (quot)
		quotient = bc_copy_num (temp);
	bc_multiply (temp, num2, &temp, r_dec_scale);
	bc_sub (num1, temp, rem, r_dec_scale);
	bc_free_num (&temp);

	if (quot)
	{
		bc_free_num (quot);
		*quot = quotient;
	}

	return 0;	/* Everything is OK. */
}


/* Modulo for numbers.  This computes NUM1 % NUM2  and puts the
   result in RESULT.   */

int
bc_modulo ( bc_num num1, bc_num num2, bc_num *result, len_t dec_scale)
{
	return bc_divmod (num1, num2, NULL, result, dec_scale);
}

/* Raise BASE to the EXPO power, reduced modulo MOD.  The result is
   placed in RESULT.  If a EXPO is not an integer,
   only the integer part is used.  */

int
bc_raisemod (bc_num base, bc_num expo, bc_num mod, bc_num *result, len_t dec_scale)
{
	bc_num	power, exponent, parity, temp;
	len_t	dec_rscale;

	/* Check for correct numbers. */
	if (bc_is_zero(mod))
		return -1;
	if (bc_is_neg(expo))
		return -1;

	/* Set initial values.  */
	power = bc_copy_num (base);
	exponent = bc_copy_num (expo);
	temp = bc_copy_num (_one_);
	bc_init_num(&parity);

	/* Check the base for scale digits. */
	if (base->n_dec_scale != 0)
		bc_rt_warn ("non-zero scale in base");

	/* Check the exponent for scale digits. */
	if (exponent->n_dec_scale != 0)
	{
		bc_rt_warn ("non-zero scale in exponent");
		bc_divide (exponent, _one_, &exponent, 0); /*truncate */
	}

	/* Check the modulus for scale digits. */
	if (mod->n_dec_scale != 0)
	{
		bc_rt_warn ("non-zero scale in modulus");
	}

	/* Do the calculation. */
	dec_rscale = MAX(dec_scale, base->n_dec_scale);
	while ( !bc_is_zero(exponent) )
	{
		(void) bc_divmod (exponent, _two_, &exponent, &parity, 0);
		if ( !bc_is_zero(parity) )
		{
			bc_multiply (temp, power, &temp, dec_rscale);
			(void) bc_modulo (temp, mod, &temp, dec_scale);
		}

		bc_multiply (power, power, &power, dec_rscale);
		(void) bc_modulo (power, mod, &power, dec_scale);
	}

	/* Assign the value. */
	bc_free_num (&power);
	bc_free_num (&exponent);
	bc_free_num (result);
	*result = temp;
	return 0;	/* Everything is OK. */
}

/* Raise NUM1 to the NUM2 power.  The result is placed in RESULT.
   Maximum exponent is LONG_MAX.  If a NUM2 is not an integer,
   only the integer part is used.  */

void
bc_raise (bc_num num1, bc_num num2, bc_num *result, len_t dec_scale)
{
	bc_num	temp, power;
	len_t	exponent;
	len_t	uexponent;
	len_t	dec_rscale;
	len_t	pwrscale;
	len_t	calcscale;
	char	neg;

	/* Check the exponent for scale digits and convert to a long. */
	if (num2->n_dec_scale != 0)
		bc_rt_warn ("non-zero scale in exponent");
	//if (exponent == 0 && (num2->n_len > 1 || num2->n_value[0] != 0))
	if(!bc_num2long (num2, &exponent))
	{
		bc_rt_error ("exponent too large in raise");
		return;
	}
	/* Special case if exponent is a zero. */
	if (exponent == 0)
	{
		bc_free_num (result);
		*result = bc_copy_num (_one_);
		return;
	}

	/* Other initializations. */
	if (exponent < 0)
	{
		neg = TRUE;
		uexponent = -exponent;
		dec_rscale = dec_scale;
	}
	else
	{
		neg = FALSE;
		uexponent = exponent;
		dec_rscale = MIN(num1->n_dec_scale*uexponent, MAX(dec_scale, num1->n_dec_scale));
	}

	/* Set initial value of temp.  */
	power = bc_copy_num (num1);
	pwrscale = num1->n_dec_scale;
	while ((uexponent & 1) == 0)
	{
		pwrscale <<= 1;
		bc_multiply (power, power, &power, pwrscale);
		uexponent = uexponent >> 1;
	}
	temp = bc_copy_num (power);
	calcscale = pwrscale;
	uexponent >>= 1;

	/* Do the calculation. */
	while (uexponent > 0)
	{
		pwrscale <<= 1;
		bc_multiply (power, power, &power, pwrscale);
		if ((uexponent & 1) == 1)
		{
			calcscale = pwrscale + calcscale;
			bc_multiply (temp, power, &temp, calcscale);
		}
		uexponent >>= 1;
	}

	/* Assign the value. */
	if (neg)
	{
		bc_divide (_one_, temp, result, dec_rscale);
		bc_free_num (&temp);
	}
	else
	{
		bc_free_num (result);
		*result = temp;
		if ((*result)->n_dec_scale > dec_rscale)
		{
			(*result)->n_dec_scale = dec_rscale;
		}
	}
	bc_free_num (&power);
}

/* Take the square root NUM and return it in NUM with SCALE digits
   after the decimal place. */

int
bc_sqrt (bc_num *num, len_t dec_scale)
{
	bc_num	n = *num;

	if(n->n_sign < 0)
	{
		//bc_rt_error("negative number in sqrt.");
		return 0;
	}

	if(0 == n->n_sign)	// just for doing as original version.
	{
		n = bc_copy_num(_zero_);
	}
	else if(n->n_scale <= 0 && 1 == n->n_len && n->n_value[0] == 1)	// just for doing as original version.
	{
		n = bc_copy_num(_one_);
	}
	else
	{
		dig_t	*a;
		len_t	alen, rlen, nscale = TO_SCALE(n->n_dec_scale), scale = TO_SCALE(dec_scale), res_scale;

		res_scale = MAX(nscale, scale);
		a = n->n_value + (n->n_scale - nscale);
		alen = nscale + n->n_len - 1;
		while(alen >= 0 && 0 == a[alen])
		{
			alen--;
		}
		alen++;

		assert(alen > 0);

		n = bc_new_num((n->n_len+1)/2 + 2, res_scale);
		n->n_sign = 1;

		// a == n * base^nscale
		// Calculate sqrt( a * base^(2*res_scale - nscale) )
		// a * base^(2*res_scale - nscale) == n * base^(2*res_scale)
		bi_sqrt(a, alen, 2*res_scale - nscale, n->n_value, &rlen);

		n->n_len = rlen - res_scale;
		n->n_dec_scale = MAX((*num)->n_dec_scale, dec_scale);
		bc_clear_extra_fraction(n);
	}

	bc_free_num(num);
	*num = n;
	return 1;
}


/* The following routines provide output for bcd numbers package
   using the rules of POSIX bc for output. */

/* This structure is used for saving digits in the conversion process. */
typedef struct stk_rec {
	int  digit;
	struct stk_rec *next;
} stk_rec;

/* The reference string for digits. */
static char ref_str[] = "0123456789ABCDEF";


int		bc_dec_num2str(dig_t d, char *str, int leading_zero)
{
	int		i = LOG10_RADIX-1, len = 0;

	if(!leading_zero)
	{
		while(i >= 0)
		{
			if((d/g_pow10[i])%10)
			{
				break;
			}
			i--;
		}
	}
	while(i >= 0)
	{
		if(str)
		{
			*str++ = '0' + (d/g_pow10[i])%10;
		}
		i--;
		len++;
	}
	if(str)
	{
		*str = '\0';
	}
	return len;
}

/* A special output routine for "multi-character digits."  Exactly
   SIZE characters must be output for the value VAL.  If SPACE is
   non-zero, we must output one space before the number.  OUT_CHAR
   is the actual routine for writing the characters. */

void
bc_out_long (long val, int size, int space, void (*out_char)(int))
{
  char digits[40];
  int len, ix;

  if (space) (*out_char) (' ');
  len = bc_dec_num2str(val, digits, 0);
  //snprintf (digits, sizeof(digits), "%ld", val);
  //len = strlen (digits);
  while (size > len)
    {
      (*out_char) ('0');
      size--;
    }
  for (ix=0; ix < len; ix++)
    (*out_char) (digits[ix]);
}

/* Output of a bcd number.  NUM is written in base O_BASE using OUT_CHAR
   as the routine to do the actual output of the characters. */

void
bc_out_num (bc_num num, int o_base, void (*out_char)(int), int leading_zero)
{
	int		fdigit, pre_space;
	stk_rec	*digits, *temp = NULL;
	bc_num	int_part, frac_part, base, cur_dig, t_num;//, max_o_digit;

	/* The negative sign if needed. */
	if(num->n_sign < 0)
	{
		(*out_char) ('-');
	}

	/* Output the number. */
	if (bc_is_zero (num))
	{
		(*out_char) ('0');
		return;
	}
	if (o_base == 10)
	{
		len_t i, size = num->n_scale + num->n_len;
		int j;
		dig_t *ptr = num->n_value + (size-1);
		char str[40];

		if (leading_zero && bc_is_zero (num))
			(*out_char) ('0');

		for(i = 0; i < num->n_len; i++)
		{
			bc_dec_num2str(*ptr--, str, i > 0);
			for(j = 0; str[j]; j++)
			{
				(*out_char)(str[j]);
			}
		}
		if(num->n_dec_scale > 0)
		{
			len_t	scale = TO_SCALE(num->n_dec_scale);
			(*out_char)('.');
			for(i = 0; i < scale-1; i++)
			{
				bc_dec_num2str(*ptr--, str, 1);
				for(j = 0; str[j]; j++)
				{
					(*out_char)(str[j]);
				}
			}
			{
				int   r = num->n_dec_scale % LOG10_RADIX;

				if(0 == r)
				{
					r = LOG10_RADIX;
				}
				if(r > 0)
				{
					bc_dec_num2str(*ptr--, str, 1);
					for(j = 0; j < r; j++)
					{
						(*out_char)(str[j]);
					}
				}
			}
		}
	}
	else
	{
		int		digit_size;
		/* special case ... */
		if (leading_zero && bc_is_zero (num))
			(*out_char) ('0');

		/* The number is some other base. */
		digits = NULL;
		bc_init_num (&int_part);
		bc_divide (num, _one_, &int_part, 0);
		bc_init_num (&frac_part);
		bc_init_num (&cur_dig);
		bc_init_num (&base);
		bc_sub (num, int_part, &frac_part, 0);
		/* Make the INT_PART and FRAC_PART positive. */
		int_part->n_sign = int_part->n_sign*int_part->n_sign;
		frac_part->n_sign = frac_part->n_sign*frac_part->n_sign;
		bc_int2num (&base, o_base);
		//bc_init_num (&max_o_digit);
		//bc_int2num (&max_o_digit, o_base-1);
		digit_size = bc_dec_num2str(o_base-1, NULL, 0);

		/* Get the digits of the integer part and push them on a stack. */
		while (!bc_is_zero (int_part))
		{
			bc_modulo (int_part, base, &cur_dig, 0);
			temp = (stk_rec *) malloc (sizeof(stk_rec));
			if (temp == NULL) bc_out_of_memory();
			{
				len_t	t;
				bc_num2long (cur_dig, &t);
				temp->digit = t;
			}
			temp->next = digits;
			digits = temp;
			bc_divide (int_part, base, &int_part, 0);
		}

		/* Print the digits on the stack. */
		if (digits != NULL)
		{
			/* Output the digits. */
			while (digits != NULL)
			{
				temp = digits;
				digits = digits->next;
				if (o_base <= 16)
					(*out_char) (ref_str[ (int) temp->digit]);
				else
					bc_out_long (temp->digit, digit_size/*max_o_digit->n_len*/, 1, out_char);
				free (temp);
			}
		}

		/* Get and print the digits of the fraction part. */
		if (num->n_scale > 0)
		{
			(*out_char) ('.');
			pre_space = 0;
			t_num = bc_copy_num (_one_);
			while (t_num->n_len <= num->n_scale) {
				bc_multiply (frac_part, base, &frac_part, num->n_scale);
				{
					len_t	t;
					bc_num2long (frac_part, &t);
					fdigit = t;
				}
				bc_int2num (&int_part, fdigit);
				bc_sub (frac_part, int_part, &frac_part, 0);
				if (o_base <= 16)
					(*out_char) (ref_str[fdigit]);
				else {
					bc_out_long (fdigit, digit_size/*max_o_digit->n_len*/, pre_space, out_char);
					pre_space = 1;
				}
				bc_multiply (t_num, base, &t_num, 0);
			}
			bc_free_num (&t_num);
		}

		/* Clean up. */
		bc_free_num (&int_part);
		bc_free_num (&frac_part);
		bc_free_num (&base);
		bc_free_num (&cur_dig);
		//bc_free_num (&max_o_digit);
	}
}

/* Convert a number NUM to a long.  The function returns only the integer
   part of the number.  For numbers that are too large to represent as
   a long, this function returns a zero.  This can be detected by checking
   the NUM for zero after having a zero returned. */

int
bc_num2long (bc_num num, len_t* ret)
{
	len_t	val = 0;
	dig_t*	d = num->n_value + num->n_scale;
	int		i;
	len_t	b10_len = bi_b10_len(d, num->n_len);

	// sizeof(len_t) == 4
	// 2^31-1 = 2147483647
	// limit :   999999999 --> length == 9

	// sizeof(len_t) == 8
	// 2^63-1 = 9223372036854775807
	// limit :   999999999999999999 --> length == 18

	// sizeof(len_t) == 16
	// 2^127-1 = 170141183460469231731687303715884105727
	// limit :    99999999999999999999999999999999999999 --> length == 38

	// Avoiding overflow
	if(
		( 4 == sizeof(len_t) && b10_len >  9) ||
		( 8 == sizeof(len_t) && b10_len > 18) ||
		(16 == sizeof(len_t) && b10_len > 38) ||
		0)
	{
		*ret = 0;
		return 0;
	}

	for(i = num->n_len - 1; i >= 0; i--)
	{
		val = RADIX*val + d[i];
	}
	*ret = val;
	return 1;
}


/* Convert an integer VAL to a bc number NUM. */

void
bc_int2num (bc_num *num, len_t val)
{
	dig_t	d[16];
	len_t	i = 0;
	int		sign = SIGN(val);

	if(val < 0)
	{
		val = -val;
	}
	bc_free_num (num);
	while(val > 0)
	{
		d[i++] = val % RADIX;
		val /= RADIX;
	}
	*num = bc_new_num(i, 0);
	(*num)->n_len = i;
	(*num)->n_sign = sign;

	i--;
	while(i >= 0)
	{
		(*num)->n_value[i] = d[i];
		i--;
	}
}


#if	0
/* Convert a numbers to a string.  Base 10 only.*/

char
*bc_num2str (bc_num num)
{
  char *str, *sptr;
  char *nptr;
  int  i, signch;

  /* Allocate the string memory. */
  signch = ( num->n_sign == PLUS ? 0 : 1 );  /* Number of sign chars. */
  if (num->n_scale > 0)
    str = (char *) malloc (num->n_len + num->n_scale + 2 + signch);
  else
    str = (char *) malloc (num->n_len + 1 + signch);
  if (str == NULL) bc_out_of_memory();

  /* The negative sign if needed. */
  sptr = str;
  if (signch) *sptr++ = '-';

  /* Load the whole number. */
  nptr = num->n_value;
  for (i=num->n_len; i>0; i--)
    *sptr++ = BCD_CHAR(*nptr++);

  /* Now the fraction. */
  if (num->n_scale > 0)
    {
      *sptr++ = '.';
      for (i=0; i<num->n_scale; i++)
	*sptr++ = BCD_CHAR(*nptr++);
    }

  /* Terminate the string and return it! */
  *sptr = '\0';
  return (str);
}
#endif

#if	0
/* Convert strings to bc numbers.  Base 10 only.*/

void
bc_str2num	(bc_num *num, char *str, int scale)
{
  int digits, strscale;
  char *ptr, *nptr;
  char zero_int;

  /* Prepare num. */
  bc_free_num (num);

  /* Check for valid number and count digits. */
  ptr = str;
  digits = 0;
  strscale = 0;
  zero_int = FALSE;
  if ( (*ptr == '+') || (*ptr == '-'))  ptr++;  /* Sign */
  while (*ptr == '0') ptr++;			/* Skip leading zeros. */
  while (isdigit((int)*ptr)) ptr++, digits++;	/* digits */
  if (*ptr == '.') ptr++;			/* decimal point */
  while (isdigit((int)*ptr)) ptr++, strscale++;	/* digits */
  if ((*ptr != '\0') || (digits+strscale == 0))
    {
      *num = bc_copy_num (_zero_);
      return;
    }

  /* Adjust numbers and allocate storage and initialize fields. */
  strscale = MIN(strscale, scale);
  if (digits == 0)
    {
      zero_int = TRUE;
      digits = 1;
    }
  *num = bc_new_num (digits, strscale);

  /* Build the whole number. */
  ptr = str;
  if (*ptr == '-')
    {
      (*num)->n_sign = MINUS;
      ptr++;
    }
  else
    {
      (*num)->n_sign = PLUS;
      if (*ptr == '+') ptr++;
    }
  while (*ptr == '0') ptr++;			/* Skip leading zeros. */
  nptr = (*num)->n_value;
  if (zero_int)
    {
      *nptr++ = 0;
      digits = 0;
    }
  for (;digits > 0; digits--)
    *nptr++ = CH_VAL(*ptr++);


  /* Build the fractional part. */
  if (strscale > 0)
    {
      ptr++;  /* skip the decimal point! */
      for (;strscale > 0; strscale--)
	*nptr++ = CH_VAL(*ptr++);
    }
}
#endif

/* Debugging routines */

#ifdef DEBUG

/* pn prints the number NUM in base 10. */

static void
out_char (int c)
{
  putchar(c);
}


void
pn (bc_num num)
{
  bc_out_num (num, 10, out_char, 0);
  out_char ('\n');
}


/* pv prints a character array as if it was a string of bcd digits. */
void
pv (char *name, unsigned char *num, int len)
{
  int i;
  printf ("%s=", name);
  for (i=0; i<len; i++) printf ("%c",BCD_CHAR(num[i]));
  printf ("\n");
}

#endif
