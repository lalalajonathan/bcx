/* bi.c: Implements arbitrary precision numbers in base 10^k */
/*
    Copyright (C) 2015 Free Software Foundation, Inc.

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
       e-mail:  lalala72@gmail.com

*************************************************************************/

#include	<stdio.h>
#include	<stdlib.h>
#include	<memory.h>

#include	<config.h>
#ifdef	PARAL_MULT	// Supports multi-threaded multiplication.
	#include	<pthread.h>
#endif

#include	<assert.h>
#include	<unistd.h>
#include	"bi.h"

//#define		BI_ASSERT(x)
#define		BI_ASSERT(x)	assert(x)

#define		KARATSUBA_CUTOFF	64
#define		TC3_CUTOFF			2048

#define		MAX_PARAL_CNT		125	/* 5^3 */
#define		PARAL_START_DEPTH	2
#define		MIN_PARAL_BLK_SIZE	512

#ifdef	PARAL_MULT
static int	__g_paral_cnt = 1;
#endif

dig_t	g_pow10[LOG10_RADIX];

static len_t	__strlen(const char* str)
{
	len_t	len = 0;

	if(str)
	{
		while(*(str++))
		{
			len++;
		}
	}
	return len;
}

int		bi_from_string(dig_t* a, len_t* alen, const char* str, len_t len)
{
	len_t	i, j;
	len_t	qq = len / LOG10_RADIX;
	len_t	aalen = 0;
	dig_t	t, c;
	char	ch;

	if(len < 0)
	{
		len = __strlen(str);
	}

	for(i = len-1; qq > 0; qq--)
	{
		t = 0;
		for(j = 0; j < LOG10_RADIX; j++)
		{
			ch = str[i--];

			if(ch >= '0' && ch <= '9')
			{
				c = ch - '0';
			}
			else
			{
				return 0;
			}
			c *= g_pow10[j];
			t += c;
		}
		a[aalen++] = t;
	}

	if(i >= 0)
	{
		t = 0;
		for(j = 0; j < LOG10_RADIX && i >= 0; j++)
		{
			ch = str[i--];

			if(ch >= '0' && ch <= '9')
			{
				c = ch - '0';
			}
			else
			{
				return 0;
			}
			c *= g_pow10[j];
			t += c;
		}
		a[aalen++] = t;
	}

	while(aalen > 0 && 0 == a[aalen-1])
	{
		aalen--;
	}
	
	*alen = aalen;
	return 1;
}

int		bi_from_chars(dig_t* a, len_t* alen, const char* str, len_t len)
{
	len_t	i, j;
	len_t	qq = len / LOG10_RADIX;
	len_t	aalen = 0;
	dig_t	t;

	for(i = len-1; qq > 0; qq--)
	{
		t = 0;
		for(j = 0; j < LOG10_RADIX; j++)
		{
			t += g_pow10[j]*str[i--];
		}
		a[aalen++] = t;
	}

	if(i >= 0)
	{
		t = 0;
		for(j = 0; j < LOG10_RADIX && i >= 0; j++)
		{
			t += g_pow10[j]*str[i--];
		}
		a[aalen++] = t;
	}

	while(aalen > 0 && 0 == a[aalen-1])
	{
		aalen--;
	}
	
	*alen = aalen;
	return 1;
}

len_t	bi_to_chars(const dig_t* a, len_t alen, char* str)
{
	len_t	i, j, k;
	dig_t	d;
	int		tc[LOG10_RADIX];

	BI_ASSERT(alen == 0 || (alen > 0 && a[alen-1] > 0));

	if(alen <= 0)
	{
		return 0;
	}

	k = 0;

	{
		d = a[alen-1];
		for(j = LOG10_RADIX-1; j >= 0; j--)
		{
			tc[j] = (d%10);
			d /= 10;
		}
		for(j = 0; 0 == tc[j]; j++)
		{
			;
		}
		for(; j < LOG10_RADIX; j++)
		{
			*(str++) = (char)(tc[j]);
			k++;
		}
	}

	for(i = alen-2; i >= 0; i--)
	{
		d = a[i];
		str += LOG10_RADIX;
		for(j = 0; j < LOG10_RADIX; j++)
		{
			*(--str) = (d%10);
			d /= 10;
		}
		str += LOG10_RADIX;
		k += LOG10_RADIX;
	}

	return k;
}



#define		UNLIKELY(e)		__builtin_expect(e, 0)



#if		0
static len_t	__suff_digits(dig_t a, len_t b)
{
	if(a <= 1)
	{
		return 1;
	}
	if(a <= 10)
	{
		return ((len_t)25)*b/100 + 1;
	}
	if(a <= 100)
	{
		return ((len_t)38)*b/100 + 1;
	}
	if(a <= 10000)
	{
		return ((len_t)50)*b/100 + 1;
	}
	if(a <= 100000)
	{
		return ((len_t)63)*b/100 + 1;
	}
	if(a <= 1000000)
	{
		return ((len_t)75)*b/100 + 1;
	}
	if(a <= 10000000)
	{
		return ((len_t)88)*b/100 + 1;
	}
	return b + 1;	/* a <= 100000000 */
/*
	if(a <= 1000000000)
	{
		return ((len_t)113)*b/100 + 1;
	}
	if(a <= 0x7FFFFFFF)
	{
		return ((len_t)125)*b/100 + 1;
	}
	fprintf(stderr, "Too big exponent %d\n", b);
	exit(-1);
*/
}
#endif

int		bi_cmp(const dig_t* a, len_t alen, const dig_t* b, len_t blen)
{
	if(alen > blen)
	{
		return 1;
	}
	if(alen < blen)
	{
		return -1;
	}

	{
		len_t	i;

		for(i = alen-1; i >= 0; i--)
		{
			if(a[i] > b[i])
			{
				return 1;
			}
			if(a[i] < b[i])
			{
				return -1;
			}
		}
	}	
	return 0;
}

static int	__cmp_shift(const dig_t* a, len_t alen, const dig_t* b, len_t blen, len_t s)
{
	len_t	bblen = blen + s;
	
	if(alen > bblen)
	{
		return 1;
	}
	if(alen < bblen)
	{
		return -1;
	}

	{
		len_t	i;

		for(i = alen-1; i >= s; i--)
		{
			if(a[i] > b[i-s])
			{
				return 1;
			}
			if(a[i] < b[i-s])
			{
				return -1;
			}
		}
		for(; i >= 0 && 0 == a[i]; i--)
		{
			;
		}
		if(i >= 0)
		{
			return 1;
		}
	}	
	return 0;
}

#if 0
static void		bi_lshift(dig_t* a, len_t* alen, len_t d)
{
	if(UNLIKELY(*alen <= 0 || d <= 0))
	{
		return;
	}

	{
		len_t	i;

		for(i = *alen-1; i >= 0; i--)
		{
			a[i+d] = a[i];
		}
		for(i = d-1; i >= 0; i--)
		{
			a[i] = 0;
		}
		*alen += d;
	}
}
#endif

static void		bi_rshift(dig_t* a, len_t* alen, len_t d)
{
	if(UNLIKELY(*alen <= 0 || d <= 0))
	{
		return;
	}
	if(UNLIKELY(*alen <= d))
	{
		*alen = 0;
		return;
	}

	{
		len_t	i, aalen = *alen;

		for(i = d; i < aalen; i++)
		{
			a[i-d] = a[i];
		}
		*alen -= d;
	}
}

void	bi_inc(dig_t* a, len_t* alen)
{
	len_t	i, aalen = *alen;

	for(i = 0; i < aalen; i++)
	{
		a[i]++;
		if(a[i] < RADIX)
		{
			break;
		}
		else
		{
			a[i] = 0;
		}
	}

	if(i < aalen)
	{
	}
	else
	{
		a[i++] = 1;
		(*alen)++;
	}
}

void	bi_dec(dig_t* a, len_t* alen)
{
	// a must be positive.
	len_t	i, aalen = *alen;

	BI_ASSERT(*alen > 0 && a[*alen-1] > 0);

	for(i = 0; i < aalen && a[i] == 0; i++)
	{
		a[i] = RADIX-1;
	}
	a[i]--;
	if(0 == a[aalen-1])
	{
		*alen = aalen-1;
	}
}

void	bi_add1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen)
{
	ddig_t	d = 0;
	len_t	i, aalen = *alen;

	if(UNLIKELY(blen <= 0))
	{
		return;
	}

	if(aalen <= blen)
	{	
		for(i = 0; i < aalen; i++)
		{
			d += a[i];
			d += b[i];
			if(d >= RADIX)
			{
				a[i] = d - RADIX;
				d = 1;
			}
			else
			{
				a[i] = d;
				d = 0;
			}
		}

		for(; d && i < blen; i++)
		{
			d += b[i];
			if(d >= RADIX)
			{
				a[i] = d - RADIX;
				d = 1;
			}
			else
			{
				a[i] = d;
				d = 0;
			}
		}

		for(; i < blen; i++)
		{
			a[i] = b[i];
		}
	}
	else
	{	
		for(i = 0; i < blen; i++)
		{
			d += a[i];
			d += b[i];
			if(d >= RADIX)
			{
				a[i] = d - RADIX;
				d = 1;
			}
			else
			{
				a[i] = d;
				d = 0;
			}
		}

		for(; d && i < aalen; i++)
		{
			d += a[i];
			if(d >= RADIX)
			{
				a[i] = d - RADIX;
				d = 1;
			}
			else
			{
				a[i] = d;
				d = 0;
			}
		}
		
		i = aalen;
	}

	if(d)
	{
		a[i++] = 1;
	}

	*alen = i;
}

void	bi_add2(
	const dig_t* a, len_t alen, 
	const dig_t* b, len_t blen, 
	dig_t* c, len_t* clen)
{
	ddig_t	d = 0;
	len_t	i;

	if(alen > blen)
	{
		const dig_t*	t;
		len_t	l;
		
		t = a;
		a = b;
		b = t;
		l = alen;
		alen = blen;
		blen = l;
	}

	for(i = 0; i < alen; i++)
	{
		d += a[i];
		d += b[i];
		if(d >= RADIX)
		{
			c[i] = d - RADIX;
			d = 1;
		}
		else
		{
			c[i] = d;
			d = 0;
		}
	}

	for(; d && i < blen; i++)
	{
		d += b[i];
		if(d >= RADIX)
		{
			c[i] = d - RADIX;
			d = 1;
		}
		else
		{
			c[i] = d;
			d = 0;
		}
	}

	for(; i < blen; i++)
	{
		c[i] = b[i];
	}

	if(d)
	{
		c[i++] = 1;
	}

	*clen = i;
}

void	bi_add_shift(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	len_t s)
{
	len_t	i, aalen = *alen;

	if(UNLIKELY(blen <= 0))
	{
		return;
	}

	if(aalen >= s)
	{
		aalen -= s;
	}
	else
	{
		for(i = aalen; i < s; i++)
		{
			a[i] = 0;
		}
		aalen = 0;
	}
	bi_add1(a+s, &aalen, b, blen);
	*alen = aalen + s;
}

void	bi_sub1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen)
{
	ddig_t	d = 0;
	len_t	i, aalen = *alen;

	if(UNLIKELY(blen <= 0))
	{
		return;
	}

	for(i = 0; i < blen; i++)
	{
		d += a[i];
		d -= b[i];
		if(d >= 0)
		{
			a[i] = d;
			d = 0;
		}
		else
		{
			a[i] = d + RADIX;
			d = -1;
		}
	}

	for(; d && i < aalen; i++)
	{
		d += a[i];
		if(d >= 0)
		{
			a[i] = d;
			d = 0;
		}
		else
		{
			a[i] = d + RADIX;
			d = -1;
		}
	}

	i = aalen-1;
	while(i >= 0 && 0 == a[i])
	{
		i--;
	}

	*alen = i+1;
}

void	bi_sub2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	ddig_t	d = 0;
	len_t	i;

	for(i = 0; i < blen; i++)
	{
		d += a[i];
		d -= b[i];
		if(d >= 0)
		{
			c[i] = d;
			d = 0;
		}
		else
		{
			c[i] = d + RADIX;
			d = -1;
		}
	}

	for(; d && i < alen; i++)
	{
		d += a[i];
		if(d >= 0)
		{
			c[i] = d;
			d = 0;
		}
		else
		{
			c[i] = d + RADIX;
			d = -1;
		}
	}

	for(; i < alen; i++)
	{
		c[i] = a[i];
	}

	i = alen-1;
	while(i >= 0 && 0 == c[i])
	{
		i--;
	}

	*clen = i+1;
}

void	bi_sub_shift(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen, len_t s)
{
	len_t	i, aalen = *alen;

	if(UNLIKELY(blen <= 0))
	{
		return;
	}

	aalen -= s;
	bi_sub1(a+s, &aalen, b, blen);
	aalen += s;

	i = aalen-1;
	while(i >= 0 && 0 == a[i])
	{
		i--;
	}

	*alen = i+1;
}

void	bi_elementary_mul(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	dig_t	*ta;
	len_t	i, j;

	// for performance
	if(alen < blen)
	{
		const dig_t*	td;
		len_t	tl;

		td = a;
		a = b;
		b = td;

		tl = alen;
		alen = blen;
		blen = tl;
	}

	ta = bi_malloc(alen+1, __LINE__);

	*clen = 0;
	for(i = 0; i < blen; i++)
	{
		ddig_t	bb = b[i];
		if(bb)
		{
			ddig_t	d = 0;

			for(j = 0; j < alen; j++)
			{
				d += a[j]*bb;
				ta[j] = d%RADIX;
				d /= RADIX;
			}
			if(d)
			{
				ta[j++] = d;
			}
			bi_add_shift(c, clen, ta, j, i);
		}
	}
	bi_free(ta);
}

static void		__bi_mul_karatsuba(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	// #of allocated digits of c must be greater than or equal to (alen+blen+1)
	if(UNLIKELY(alen <= 0 || blen <= 0))
	{
		*clen = 0;
		return;
	}
	
	if(UNLIKELY(blen <= KARATSUBA_CUTOFF))
	{
		bi_elementary_mul(a, alen, b, blen, c, clen);
		return;
	}
/*
	if(2*blen <= alen)
	{
		dig_t*	t = bi_malloc(2*blen, __LINE__);
		len_t	ss = 0;

		*clen = 0;
		while(alen > 0)
		{
			len_t	l = (alen >= blen ? blen : alen);
			for(l--; l >= 0 && 0 == a[l]; l--)
			{
				;
			}
			l++;

			if(l > 0)
			{
				len_t	tlen;
				__bi_mul_karatsuba(a, l, b, blen, t, &tlen);
				bi_add_shift(c, clen, t, tlen, ss);
			}
			a += blen;
			alen -= blen;
			ss += blen;
		}
		bi_free(t);
		return;
	}
*/
	{
		len_t	m;
		len_t	i;
		const dig_t	*x0, *x1, *y0, *y1;
		dig_t	*z0, *z1, *z2;
		len_t	x0len = 0, x1len = 0, y0len = 0, y1len = 0, z0len = 0, z1len = 0, z2len = 0, txlen, tylen;

		m = alen;
		if(m < blen)
		{
			m = blen;
		}

		m = (m+1)/2;

		if(alen > m)
		{
			x1 = a + m;
			x1len = alen - m;

			x0 = a;
			x0len = m;
			for(i = m-1; i >= 0 && 0 == x0[i]; i--)
			{
				;
			}
			x0len = i+1;
		}
		else
		{
			x1 = (dig_t*)0;
			x0 = a;
			x0len = alen;
		}

		if(blen > m)
		{
			y1 = b + m;
			y1len = blen - m;

			y0 = b;
			y0len = m;
			for(i = m-1; i >= 0 && 0 == y0[i]; i--)
			{
				;
			}
			y0len = i+1;
		}
		else
		{
			y1 = (dig_t*)0;
			y0 = b;
			y0len = blen;
		}

		// z0 = x0*y0;
		z0 = c;//bi_malloc(alen+blen, __LINE__);
		__bi_mul_karatsuba(x0, x0len, y0, y0len, z0, &z0len);
		*clen = z0len;

		// z2 = x1*y1;
		z2 = bi_malloc(x1len+y1len, __LINE__);
		__bi_mul_karatsuba(x1, x1len, y1, y1len, z2, &z2len);

		{
			dig_t	*tx, *ty;

			tx = bi_malloc(m+1, __LINE__);
			ty = bi_malloc(m+1, __LINE__);

			// z1 = (x1+x0)*(y1+y0)-z2-z0;
			memcpy(tx, x1, sizeof(dig_t)*x1len);
			txlen = x1len;
			bi_add1(tx, &txlen, x0, x0len);

			memcpy(ty, y1, sizeof(dig_t)*y1len);
			tylen = y1len;
			bi_add1(ty, &tylen, y0, y0len);

			z1 = bi_malloc(2*(m+1), __LINE__);
			__bi_mul_karatsuba(tx, txlen, ty, tylen, z1, &z1len);
			bi_free(tx);
			bi_free(ty);
		}

		bi_sub1(z1, &z1len, z2, z2len);
		bi_sub1(z1, &z1len, z0, z0len);

		// c already contains z0

		// return x0*y0 + z1*r^m + z2*r^(2m)
		bi_add_shift(c, clen, z1, z1len, m);
		bi_free(z1);
		
		bi_add_shift(c, clen, z2, z2len, 2*m);
		bi_free(z2);
	}
}

static void		__bi_sadd(int* asign, dig_t* a, len_t* alen, int bsign, const dig_t* b, len_t blen)
{
	int		aas = *asign;
	len_t	aalen = *alen;
	len_t	i;
	int		d;

	if((aas > 0 && bsign > 0) || (aas < 0 && bsign < 0))
	{
		bi_add1(a, alen, b, blen);
		return;
	}

	d = bi_cmp(a, aalen, b, blen);
	if(0 == d)
	{
		*asign = 1;
		*alen = 0;
		return;
	}

	if(d > 0)	// abs = (a-b), sign = as
	{
		bi_sub1(a, alen, b, blen);
	}
	else		// abs = (b-a), sign = -as
	{
		dig_t*	t = bi_malloc(aalen, __LINE__);
		len_t	tlen = aalen;
		for(i = 0; i < aalen; i++)
		{
			t[i] = a[i];
		}
		bi_sub2(b, blen, t, tlen, a, alen);
		*asign = -aas;
		bi_free(t);
	}
}

void	bi_mul1_one_dig_t(
	dig_t* a, len_t* alen,
	dig_t b)
{
	ddig_t	d = 0, bb = b;
	len_t	i, aalen = *alen;

	for(i = 0; i < aalen; i++)
	{
		d += a[i]*bb;
		a[i] = d%RADIX;
		d /= RADIX;
	}
	if(d)
	{
		a[i] = d;
		(*alen)++;
	}
}

void	bi_mul2_one_digit(
	const dig_t* a, len_t alen,
	dig_t b,
	dig_t* c, len_t* clen)
{
	ddig_t	d = 0, bb = b;
	len_t	i;

	for(i = 0; i < alen; i++)
	{
		d += a[i]*bb;
		c[i] = d%RADIX;
		d /= RADIX;
	}
	if(d)
	{
		c[i++] = d;
	}
	*clen = i;
}

static void		__bi_div_by_2(
	dig_t*	a,
	len_t*	alen)
{
	ddig_t	d;
	len_t	i, j = 0, aalen = *alen;

	if(aalen > 0)
	{
		d = a[0];
		d *= RADIX/2;
		d /= RADIX;
		for(i = 1; i < aalen; i++)
		{
			d += a[i]*((ddig_t)(RADIX/2));
			a[j++] = d%RADIX;
			d /= RADIX;
		}
		if(d)
		{
			a[j++] = d;
		}
	}
	*alen = j;
}

// a must be a multiple of 3 and gcd(RADIX, 3) must be 1.
static void		__bi_div_by_3(
	dig_t*	a,
	len_t*	alen)
{
	dig_t	*t;
	len_t	tlen, aalen = *alen;
	ddig_t	d;
	len_t	i;

	t = a;

	tlen = aalen;

	for(i = 0; i < aalen && tlen > 0; i++)
	{
		d = (((ddig_t)ARI_INV_3)*(*t))%RADIX;
		*(t++) = d;
		d *= 3;
		tlen--;
		if(d >= RADIX)
		{
			d /= RADIX;
			bi_sub1(t, &tlen, (dig_t*)&d, 1);
		}
	}
	*alen = (len_t)(t-a);
}

static void		__bi_split3(
	const dig_t* a, len_t alen,
	len_t	bs,
	const dig_t** b0, len_t* b0len,
	const dig_t** b1, len_t* b1len,
	const dig_t** b2, len_t* b2len)
{
	const dig_t	*bb0, *bb1, *bb2;
	len_t	bb0len, bb1len, bb2len;

	bb0 = a;

	if(alen <= bs)
	{
		bb0len = alen;
		bb1 = (dig_t*)0;
		bb1len = 0;
		bb2 = (dig_t*)0;
		bb2len = 0;
	}
	else if(alen <= 2*bs)
	{
		bb0len = bs;
		bb1 = a + bs;
		bb1len = alen - bs;
		bb2 = (dig_t*)0;
		bb2len = 0;
	}
	else
	{
		bb0len = bs;
		bb1 = a + bs;
		bb1len = bs;
		bb2 = a + 2*bs;
		bb2len = alen - 2*bs;
	}

	for(bb0len--; bb0len >= 0 && 0 == bb0[bb0len]; bb0len--)
	{
		;
	}
	bb0len++;

	for(bb1len--; bb1len >= 0 && 0 == bb1[bb1len]; bb1len--)
	{
		;
	}
	bb1len++;

	for(bb2len--; bb2len >= 0 && 0 == bb2[bb2len]; bb2len--)
	{
		;
	}
	bb2len++;

	*b0 = bb0;
	*b0len = bb0len;
	*b1 = bb1;
	*b1len = bb1len;
	*b2 = bb2;
	*b2len = bb2len;
}

static void		__bi_eval_tc3(
	const dig_t* c0, len_t c0len,
	const dig_t* c1, len_t c1len,
	const dig_t* c2, len_t c2len,
	int v,	// -2, -1 or 1
	int* rsign, dig_t* r, len_t* rlen)
{
	len_t	i;
	int		rrsign;
	len_t	rrlen;

	rrsign = 1;
	for(i = 0; i < c0len; i++)
	{
		r[i] = c0[i];
	}
	rrlen = c0len;

	if(1 == v)
	{
		bi_add1(r, &rrlen, c1, c1len);
		bi_add1(r, &rrlen, c2, c2len);
	}
	else if(-1 == v)
	{
		__bi_sadd(&rrsign, r, &rrlen, -1, c1, c1len);
		__bi_sadd(&rrsign, r, &rrlen, 1, c2, c2len);
	}
	else	// if(-2)
	{
		len_t	m = c0len, tlen;
		dig_t*	t;

		if(c1len > m)
		{
			m = c1len;
		}
		if(c2len > m)
		{
			m = c2len;
		}

		t = bi_malloc(m+1, __LINE__);

		bi_mul2_one_digit(c1, c1len, 2, t, &tlen);
		__bi_sadd(&rrsign, r, &rrlen, -1, t, tlen);

		bi_mul2_one_digit(c2, c2len, 4, t, &tlen);
		__bi_sadd(&rrsign, r, &rrlen, 1, t, tlen);

		bi_free(t);
	}

	*rsign = rrsign;
	*rlen = rrlen;
}

static void		__bi_mul_toomcook3(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	// # of allocated digits of c must be greater than or equal to (alen+blen+1)
	if(UNLIKELY(alen <= 0 || blen <= 0))
	{
		*clen = 0;
		return;
	}

	if(UNLIKELY(blen < TC3_CUTOFF))
	{
		__bi_mul_karatsuba(a, alen, b, blen, c, clen);
		return;
	}

	{
		len_t	m;
		//len_t	i;
		const dig_t	*x0, *x1, *x2;
		len_t	x0len = 0, x1len = 0, x2len = 0;
		const dig_t	*y0, *y1, *y2;
		len_t	y0len = 0, y1len = 0, y2len = 0;
		dig_t	*z0, *z1, *z2, *z3, *z4;
		len_t	z0len = 0, z1len = 0, z2len = 0, z3len = 0, z4len = 0;
		int		/*sz0, */sz1, sz2, sz3/*, sz4*/;

		dig_t	*txm2, *tym2, *txm1, *tym1, *txp1, *typ1;
		len_t	txm2len = 0, tym2len = 0, txm1len = 0, tym1len = 0, txp1len = 0, typ1len = 0;
		int		stxm2 = 1, stym2 = 1, stxm1 = 1, stym1 = 1, stxp1 = 1, styp1 = 1;

		dig_t	*txym2, *txym1, *txyp1;
		len_t	txym2len = 0, txym1len = 0, txyp1len = 0;
		int		stxym2 = 1, stxym1 = 1, stxyp1 = 1;

		m = alen;
		if(m < blen)
		{
			m = blen;
		}
		m = (m+2)/3;

		__bi_split3(a, alen, m, &x0, &x0len, &x1, &x1len, &x2, &x2len);
		__bi_split3(b, blen, m, &y0, &y0len, &y1, &y1len, &y2, &y2len);

		// r0 = x0*y0
		z0 = c;
		__bi_mul_toomcook3(x0, x0len, y0, y0len, z0, &z0len);
		*clen = z0len;

		// r4 = x_inf * y_inf
		z4 = bi_malloc(2*m, __LINE__);
		__bi_mul_toomcook3(x2, x2len, y2, y2len, z4, &z4len);

		txm2 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -2, &stxm2, txm2, &txm2len);
		tym2 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -2, &stym2, tym2, &tym2len);
		txym2 = bi_malloc(2*(m+1), __LINE__);
		stxym2 = stxm2*stym2;
		__bi_mul_toomcook3(txm2, txm2len, tym2, tym2len, txym2, &txym2len);
		bi_free(txm2);
		bi_free(tym2);

		txm1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -1, &stxm1, txm1, &txm1len);
		tym1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -1, &stym1, tym1, &tym1len);
		txym1 = bi_malloc(2*(m+1), __LINE__);
		stxym1 = stxm1*stym1;
		__bi_mul_toomcook3(txm1, txm1len, tym1, tym1len, txym1, &txym1len);
		bi_free(txm1);
		bi_free(tym1);

		txp1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, 1, &stxp1, txp1, &txp1len);
		typ1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, 1, &styp1, typ1, &typ1len);
		txyp1 = bi_malloc(2*(m+1), __LINE__);
		stxyp1 = stxp1*styp1;
		__bi_mul_toomcook3(txp1, txp1len, typ1, typ1len, txyp1, &txyp1len);
		bi_free(txp1);
		bi_free(typ1);

		// r3  = (r(−2) - r(1))/3
		z3 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z3, txym2, sizeof(dig_t)*txym2len);
		z3len = txym2len;
		sz3 = stxym2;
		bi_free(txym2);
		__bi_sadd(&sz3, z3, &z3len, -stxyp1, txyp1, txyp1len);
		__bi_div_by_3(z3, &z3len);

		// r1 = (r(1) - r(−1))/2
		z1 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z1, txyp1, sizeof(dig_t)*txyp1len);
		z1len = txyp1len;
		sz1 = stxyp1;
		bi_free(txyp1);
		__bi_sadd(&sz1, z1, &z1len, -stxym1, txym1, txym1len);
		__bi_div_by_2(z1, &z1len);

		// r2 = r(−1) - r0
		z2 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z2, txym1, sizeof(dig_t)*txym1len);
		z2len = txym1len;
		sz2 = stxym1;
		bi_free(txym1);
		__bi_sadd(&sz2, z2, &z2len, -1, z0, z0len);

		// r3 = (r2 - r3)/2 + r4 + r4
		sz3 = -sz3;
		__bi_sadd(&sz3, z3, &z3len, sz2, z2, z2len);
		__bi_div_by_2(z3, &z3len);
		__bi_sadd(&sz3, z3, &z3len, 1, z4, z4len);
		__bi_sadd(&sz3, z3, &z3len, 1, z4, z4len);

		// r2 = r2 + r1 - r4
		__bi_sadd(&sz2, z2, &z2len, sz1, z1, z1len);
		__bi_sadd(&sz2, z2, &z2len, -1, z4, z4len);

		// r1 = r1 - r3
		__bi_sadd(&sz1, z1, &z1len, -sz3, z3, z3len);

		// c == z0 here
		bi_add_shift(c, clen, z1, z1len, 1*m);
		bi_free(z1);
		bi_add_shift(c, clen, z2, z2len, 2*m);
		bi_free(z2);
		bi_add_shift(c, clen, z3, z3len, 3*m);
		bi_free(z3);
		bi_add_shift(c, clen, z4, z4len, 4*m);
		bi_free(z4);
	}
}






#ifdef	PARAL_MULT

typedef struct
{
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	int		cnt;
} event;

static void		event_init(event* e)
{
	pthread_mutex_init(&e->lock, (pthread_mutexattr_t*)0);
	pthread_cond_init(&e->cond, (pthread_condattr_t*)0);
	e->cnt = 0;
}

static void		event_deinit(event* e)
{
	pthread_mutex_destroy(&e->lock);
	pthread_cond_destroy(&e->cond);
	e->cnt = 0;
}

static void		event_inc(event* e)
{
	pthread_mutex_lock(&e->lock);
	e->cnt++;
	pthread_cond_signal(&e->cond);
	pthread_mutex_unlock(&e->lock);
}

static void		event_dec(event* e)
{
	pthread_mutex_lock(&e->lock);
	while(e->cnt <= 0)
	{
		pthread_cond_wait(&e->cond, &e->lock);
	}
	e->cnt--;
	pthread_mutex_unlock(&e->lock);
}

static void		event_reset(event* e)
{
	pthread_mutex_lock(&e->lock);
	e->cnt = 0;
	pthread_mutex_unlock(&e->lock);
}

typedef struct
{
	int		state;	/* 0: empty, 1: ready, 2: computing, 3: finished */
	dig_t	*a, *b;
	dig_t	*r;
	len_t	alen, blen, rlen;
	int		eval_sign;
	int		free_ab;	
} mul_info;

static int	__g_bFinish = 0;
static pthread_t	__g_thr[MAX_PARAL_CNT];

static pthread_mutex_t	__g_lock;
static event	__g_event_put, __g_event_get;

static mul_info		__g_mi[MAX_PARAL_CNT];
static int	__g_mi_idx;

static void*	__mul_thread_proc(void* pParam)
{
	while(1)
	{
		int		i;
		mul_info*	mi = (mul_info*)0;

		event_dec(&__g_event_put);

		pthread_mutex_lock(&__g_lock);
		for(i = 0; i < sizeof(__g_mi)/sizeof(__g_mi[0]); i++)
		{
			if(1 == __g_mi[i].state)
			{
				mi = __g_mi + i;
				mi->state = 2;
				break;
			}
		}
		pthread_mutex_unlock(&__g_lock);

		if(mi)
		{
			__bi_mul_toomcook3(mi->a, mi->alen, mi->b, mi->blen, mi->r, &(mi->rlen));
			//__bi_mul_karatsuba(mi->a, mi->alen, mi->b, mi->blen, mi->r, &(mi->rlen));
			if(mi->free_ab)
			{
				bi_free(mi->a);
				bi_free(mi->b);
			}
			pthread_mutex_lock(&__g_lock);
			mi->state = 3;
			pthread_mutex_unlock(&__g_lock);

			event_inc(&__g_event_get);
		}
		else if(__g_bFinish)
		{
			break;
		}
	}
	return (void*)0;
}

static void		__bi_mul_toomcook3_paral(
	int depth,
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	// # of allocated digits of c must be greater than or equal to (alen+blen+1)
	if(UNLIKELY(alen <= 0 || blen <= 0))
	{
		*clen = 0;
		return;
	}

	if(UNLIKELY(blen < TC3_CUTOFF))
	{
		__bi_mul_karatsuba(a, alen, b, blen, c, clen);
		return;
	}

	{
		len_t	m;
//		len_t	i;
		const dig_t	*x0, *x1, *x2;
		len_t	x0len = 0, x1len = 0, x2len = 0;
		const dig_t	*y0, *y1, *y2;
		len_t	y0len = 0, y1len = 0, y2len = 0;
		dig_t	*z0, *z1, *z2, *z3, *z4;
		len_t	z0len = 0, z1len = 0, z2len = 0, z3len = 0, z4len = 0;
		int		/*sz0, */sz1, sz2, sz3/*, sz4*/;

		dig_t	*txm2, *tym2, *txm1, *tym1, *txp1, *typ1;
		len_t	txm2len = 0, tym2len = 0, txm1len = 0, tym1len = 0, txp1len = 0, typ1len = 0;
		int		stxm2 = 1, stym2 = 1, stxm1 = 1, stym1 = 1, stxp1 = 1, styp1 = 1;

		dig_t	*txym2, *txym1, *txyp1;
		len_t	txym2len = 0, txym1len = 0, txyp1len = 0;
		int		stxym2 = 1, stxym1 = 1, stxyp1 = 1;

		m = alen;
		if(m < blen)
		{
			m = blen;
		}
		m = (m+2)/3;

		__bi_split3(a, alen, m, &x0, &x0len, &x1, &x1len, &x2, &x2len);
		__bi_split3(b, blen, m, &y0, &y0len, &y1, &y1len, &y2, &y2len);

		// r0 = x0*y0
		if(PARAL_START_DEPTH != depth)
		{
			z0 = c;
			__bi_mul_toomcook3_paral(depth+1, x0, x0len, y0, y0len, z0, &z0len);
			*clen = z0len;
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;

			while(1)
			{
				int	do_break = 0;

				pthread_mutex_lock(&__g_lock);
				if(3 == mi->state)
				{
					mi->state = 0;
					z0 = mi->r;
					z0len = mi->rlen;
					do_break = 1;
				}
				pthread_mutex_unlock(&__g_lock);
				if(do_break)
				{
					if(z0len > 0)
					{
						memcpy(c, z0, sizeof(dig_t)*z0len);
						bi_free(z0);
					}
					z0 = c;
					*clen = z0len;
					break;
				}
				event_dec(&__g_event_get);
			}
		}

		// r4 = x_inf * y_inf
		if(PARAL_START_DEPTH != depth)
		{
			z4 = bi_malloc(2*m, __LINE__);
			__bi_mul_toomcook3_paral(depth+1, x2, x2len, y2, y2len, z4, &z4len);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;

			while(1)
			{
				int	do_break = 0;

				pthread_mutex_lock(&__g_lock);
				if(3 == mi->state)
				{
					mi->state = 0;
					z4 = mi->r;
					z4len = mi->rlen;
					do_break = 1;
				}
				pthread_mutex_unlock(&__g_lock);
				if(do_break)
				{
					break;
				}
				event_dec(&__g_event_get);
			}
		}

		if(PARAL_START_DEPTH != depth)
		{
			txm2 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -2, &stxm2, txm2, &txm2len);
			tym2 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -2, &stym2, tym2, &tym2len);
			txym2 = bi_malloc(2*(m+1), __LINE__);
			stxym2 = stxm2*stym2;
			__bi_mul_toomcook3_paral(depth+1, txm2, txm2len, tym2, tym2len, txym2, &txym2len);
			bi_free(txm2);
			bi_free(tym2);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;

			while(1)
			{
				int	do_break = 0;

				pthread_mutex_lock(&__g_lock);
				if(3 == mi->state)
				{
					mi->state = 0;
					txym2 = mi->r;
					txym2len = mi->rlen;
					stxym2 = mi->eval_sign;
					do_break = 1;
				}
				pthread_mutex_unlock(&__g_lock);
				if(do_break)
				{
					break;
				}
				event_dec(&__g_event_get);
			}
		}

		if(PARAL_START_DEPTH != depth)
		{
			txm1 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -1, &stxm1, txm1, &txm1len);
			tym1 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -1, &stym1, tym1, &tym1len);
			txym1 = bi_malloc(2*(m+1), __LINE__);
			stxym1 = stxm1*stym1;
			__bi_mul_toomcook3_paral(depth+1, txm1, txm1len, tym1, tym1len, txym1, &txym1len);
			bi_free(txm1);
			bi_free(tym1);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;

			while(1)
			{
				int	do_break = 0;

				pthread_mutex_lock(&__g_lock);
				if(3 == mi->state)
				{
					mi->state = 0;
					txym1 = mi->r;
					txym1len = mi->rlen;
					stxym1 = mi->eval_sign;
					do_break = 1;
				}
				pthread_mutex_unlock(&__g_lock);
				if(do_break)
				{
					break;
				}
				event_dec(&__g_event_get);
			}
		}

		if(PARAL_START_DEPTH != depth)
		{
			txp1 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, 1, &stxp1, txp1, &txp1len);
			typ1 = bi_malloc(m+1, __LINE__);
			__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, 1, &styp1, typ1, &typ1len);
			txyp1 = bi_malloc(2*(m+1), __LINE__);
			stxyp1 = stxp1*styp1;
			__bi_mul_toomcook3_paral(depth+1, txp1, txp1len, typ1, typ1len, txyp1, &txyp1len);
			bi_free(txp1);
			bi_free(typ1);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;

			while(1)
			{
				int	do_break = 0;

				pthread_mutex_lock(&__g_lock);
				if(3 == mi->state)
				{
					mi->state = 0;
					txyp1 = mi->r;
					txyp1len = mi->rlen;
					stxyp1 = mi->eval_sign;
					do_break = 1;
				}
				pthread_mutex_unlock(&__g_lock);
				if(do_break)
				{
					break;
				}
				event_dec(&__g_event_get);
			}
		}

		// r3  = (r(−2) - r(1))/3
		z3 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z3, txym2, sizeof(dig_t)*txym2len);
		z3len = txym2len;
		sz3 = stxym2;
		bi_free(txym2);
		__bi_sadd(&sz3, z3, &z3len, -stxyp1, txyp1, txyp1len);
		__bi_div_by_3(z3, &z3len);

		// r1 = (r(1) - r(−1))/2
		z1 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z1, txyp1, sizeof(dig_t)*txyp1len);
		z1len = txyp1len;
		sz1 = stxyp1;
		bi_free(txyp1);
		__bi_sadd(&sz1, z1, &z1len, -stxym1, txym1, txym1len);
		__bi_div_by_2(z1, &z1len);

		// r2 = r(−1) - r0
		z2 = bi_malloc(2*(m+1), __LINE__);
		memcpy(z2, txym1, sizeof(dig_t)*txym1len);
		z2len = txym1len;
		sz2 = stxym1;
		bi_free(txym1);
		__bi_sadd(&sz2, z2, &z2len, -1, z0, z0len);

		// r3 = (r2 - r3)/2 + r4 + r4
		sz3 = -sz3;
		__bi_sadd(&sz3, z3, &z3len, sz2, z2, z2len);
		__bi_div_by_2(z3, &z3len);
		__bi_sadd(&sz3, z3, &z3len, 1, z4, z4len);
		__bi_sadd(&sz3, z3, &z3len, 1, z4, z4len);

		// r2 = r2 + r1 - r4
		__bi_sadd(&sz2, z2, &z2len, sz1, z1, z1len);
		__bi_sadd(&sz2, z2, &z2len, -1, z4, z4len);

		// r1 = r1 - r3
		__bi_sadd(&sz1, z1, &z1len, -sz3, z3, z3len);

		// c == z0 here
		bi_add_shift(c, clen, z1, z1len, 1*m);
		bi_free(z1);
		bi_add_shift(c, clen, z2, z2len, 2*m);
		bi_free(z2);
		bi_add_shift(c, clen, z3, z3len, 3*m);
		bi_free(z3);
		bi_add_shift(c, clen, z4, z4len, 4*m);
		bi_free(z4);
	}
}

static void		__bi_mul_toomcook3_trigger(
	int depth,
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen)
{
	// # of allocated digits of c must be greater than or equal to (alen+blen+1)
	if(UNLIKELY(alen <= 0 || blen <= 0))
	{
		return;
	}

	if(UNLIKELY(blen < TC3_CUTOFF))
	{
		return;
	}

	{
		len_t	m;
		const dig_t	*x0, *x1, *x2;
		len_t	x0len = 0, x1len = 0, x2len = 0;
		const dig_t	*y0, *y1, *y2;
		len_t	y0len = 0, y1len = 0, y2len = 0;

		dig_t	*txm2, *tym2, *txm1, *tym1, *txp1, *typ1;
		len_t	txm2len = 0, tym2len = 0, txm1len = 0, tym1len = 0, txp1len = 0, typ1len = 0;
		int		stxm2 = 1, stym2 = 1, stxm1 = 1, stym1 = 1, stxp1 = 1, styp1 = 1;

		int		stxym2 = 1, stxym1 = 1, stxyp1 = 1;

		m = alen;
		if(m < blen)
		{
			m = blen;
		}
		m = (m+2)/3;

		__bi_split3(a, alen, m, &x0, &x0len, &x1, &x1len, &x2, &x2len);
		__bi_split3(b, blen, m, &y0, &y0len, &y1, &y1len, &y2, &y2len);

		// r0 = x0*y0
		if(PARAL_START_DEPTH != depth)
		{
			__bi_mul_toomcook3_trigger(depth+1, x0, x0len, y0, y0len);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;
			int	do_enq = 0;

			pthread_mutex_lock(&__g_lock);
			if(x0len > 0 && y0len > 0)
			{
				dig_t *xx0, *yy0;
				xx0 = bi_malloc(x0len, __LINE__);
				memcpy(xx0, x0, x0len*sizeof(dig_t));
				yy0 = bi_malloc(y0len, __LINE__);
				memcpy(yy0, y0, y0len*sizeof(dig_t));

				mi->state = 1;
				mi->a = xx0;
				mi->alen = x0len;
				mi->b = yy0;
				mi->blen = y0len;
				mi->free_ab = 1;
				mi->r = bi_malloc(mi->alen + mi->blen, __LINE__);
				mi->rlen = 0;
				mi->eval_sign = 1;
				do_enq = 1;
			}
			else
			{
				mi->state = 3;
				mi->free_ab = 0;
				mi->r = (dig_t*)0;
				mi->rlen = 0;
				mi->eval_sign = 1;
			}
			pthread_mutex_unlock(&__g_lock);
			if(do_enq)
			{
				event_inc(&__g_event_put);
			}
		}

		// r4 = x_inf * y_inf
		if(PARAL_START_DEPTH != depth)
		{
			__bi_mul_toomcook3_trigger(depth+1, x2, x2len, y2, y2len);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;
			int	do_enq = 0;

			pthread_mutex_lock(&__g_lock);
			if(x2len > 0 && y2len > 0)
			{
				dig_t *xx2, *yy2;
				xx2 = bi_malloc(x2len, __LINE__);
				memcpy(xx2, x2, x2len*sizeof(dig_t));
				yy2 = bi_malloc(y2len, __LINE__);
				memcpy(yy2, y2, y2len*sizeof(dig_t));

				mi->state = 1;
				mi->a = xx2;
				mi->alen = x2len;
				mi->b = yy2;
				mi->blen = y2len;
				mi->free_ab = 1;
				mi->r = bi_malloc(mi->alen + mi->blen, __LINE__);
				mi->rlen = 0;
				mi->eval_sign = 1;
				do_enq = 1;
			}
			else
			{
				mi->state = 3;
				mi->free_ab = 0;
				mi->r = (dig_t*)0;
				mi->rlen = 0;
				mi->eval_sign = 1;
			}
			pthread_mutex_unlock(&__g_lock);
			if(do_enq)
			{
				event_inc(&__g_event_put);
			}
		}

		txm2 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -2, &stxm2, txm2, &txm2len);
		tym2 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -2, &stym2, tym2, &tym2len);
		stxym2 = stxm2*stym2;
		if(PARAL_START_DEPTH != depth)
		{
			__bi_mul_toomcook3_trigger(depth+1, txm2, txm2len, tym2, tym2len);
			bi_free(txm2);
			bi_free(tym2);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;
			int	do_enq = 0;

			pthread_mutex_lock(&__g_lock);
			if(txm2len > 0 && tym2len > 0)
			{
				mi->state = 1;
				mi->a = txm2;
				mi->alen = txm2len;
				mi->b = tym2;
				mi->blen = tym2len;
				mi->free_ab = 1;
				mi->r = bi_malloc(mi->alen + mi->blen, __LINE__);
				mi->rlen = 0;
				mi->eval_sign = stxym2;
				do_enq = 1;
			}
			else
			{
				bi_free(txm2);
				bi_free(tym2);
				mi->state = 3;
				mi->free_ab = 0;
				mi->r = (dig_t*)0;
				mi->rlen = 0;
				mi->eval_sign = 1;
			}
			pthread_mutex_unlock(&__g_lock);
			if(do_enq)
			{
				event_inc(&__g_event_put);
			}
		}

		txm1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, -1, &stxm1, txm1, &txm1len);
		tym1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, -1, &stym1, tym1, &tym1len);
		stxym1 = stxm1*stym1;
		if(PARAL_START_DEPTH != depth)
		{
			__bi_mul_toomcook3_trigger(depth+1, txm1, txm1len, tym1, tym1len);
			bi_free(txm1);
			bi_free(tym1);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;
			int	do_enq = 0;

			pthread_mutex_lock(&__g_lock);
			if(txm1len > 0 && tym1len > 0)
			{
				mi->state = 1;
				mi->a = txm1;
				mi->alen = txm1len;
				mi->b = tym1;
				mi->blen = tym1len;
				mi->free_ab = 1;
				mi->r = bi_malloc(mi->alen + mi->blen, __LINE__);
				mi->rlen = 0;
				mi->eval_sign = stxym1;
				do_enq = 1;
			}
			else
			{
				bi_free(txm1);
				bi_free(tym1);
				mi->state = 3;
				mi->free_ab = 0;
				mi->r = (dig_t*)0;
				mi->rlen = 0;
				mi->eval_sign = 1;
			}
			pthread_mutex_unlock(&__g_lock);
			if(do_enq)
			{
				event_inc(&__g_event_put);
			}
		}

		txp1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(x0, x0len, x1, x1len, x2, x2len, 1, &stxp1, txp1, &txp1len);
		typ1 = bi_malloc(m+1, __LINE__);
		__bi_eval_tc3(y0, y0len, y1, y1len, y2, y2len, 1, &styp1, typ1, &typ1len);
		stxyp1 = stxp1*styp1;
		if(PARAL_START_DEPTH != depth)
		{
			__bi_mul_toomcook3_trigger(depth+1, txp1, txp1len, typ1, typ1len);
			bi_free(txp1);
			bi_free(typ1);
		}
		else
		{
			mul_info*	mi = __g_mi + __g_mi_idx++;
			int	do_enq = 0;

			pthread_mutex_lock(&__g_lock);
			if(txp1len > 0 && typ1len > 0)
			{
				mi->state = 1;
				mi->a = txp1;
				mi->alen = txp1len;
				mi->b = typ1;
				mi->blen = typ1len;
				mi->free_ab = 1;
				mi->r = bi_malloc(mi->alen + mi->blen, __LINE__);
				mi->rlen = 0;
				mi->eval_sign = stxyp1;
				do_enq = 1;
			}
			else
			{
				bi_free(txp1);
				bi_free(typ1);
				mi->state = 3;
				mi->free_ab = 0;
				mi->r = (dig_t*)0;
				mi->rlen = 0;
				mi->eval_sign = 1;
			}
			pthread_mutex_unlock(&__g_lock);
			if(do_enq)
			{
				event_inc(&__g_event_put);
			}
		}
	}
}

#endif





static void	__bi_mul(const dig_t* a, len_t alen, const dig_t* b, len_t blen, dig_t* c, len_t* clen)
{
	// # of allocated digits of c must be greater than or equal to (alen+blen+1)
	if(UNLIKELY(alen <= 0 || blen <= 0))
	{
		*clen = 0;
		return;
	}

	if(UNLIKELY(blen < TC3_CUTOFF))
	{
		__bi_mul_karatsuba(a, alen, b, blen, c, clen);
		return;
	}
#if	0
	if(3*blen <= alen)
	{
		dig_t*	t = bi_malloc(2*blen, __LINE__);
		len_t	ss = 0;

		*clen = 0;
		while(alen > 0)
		{
			len_t	l = (alen >= blen ? blen : alen);
			for(l--; l >= 0 && 0 == a[l]; l--)
			{
				;
			}
			l++;

			if(l > 0)
			{
				len_t	tlen;
				__bi_mul(a, l, b, blen, t, &tlen);
				bi_add_shift(c, clen, t, tlen, ss);
			}
			a += blen;
			alen -= blen;
			ss += blen;
		}
		bi_free(t);
		return;
	}
#endif
#ifdef	PARAL_MULT
	if(__g_paral_cnt >= 2 && (alen >= 9*MIN_PARAL_BLK_SIZE || blen >= 9*MIN_PARAL_BLK_SIZE))
	{
		event_reset(&__g_event_put);
		event_reset(&__g_event_get);
		__g_mi_idx = 0;
		__bi_mul_toomcook3_trigger(0, a, alen, b, blen);
		__g_mi_idx = 0;
		__bi_mul_toomcook3_paral(0, a, alen, b, blen, c, clen);
	}
	else
	{
#endif
		__bi_mul_toomcook3(a, alen, b, blen, c, clen);
#ifdef	PARAL_MULT
	}
#endif
}

void	bi_mul1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen)
{
	len_t	i, aalen = *alen;

	dig_t*	t = bi_malloc(aalen, __LINE__);
	len_t	tlen;

	for(i = 0; i < aalen; i++)
	{
		t[i] = a[i];
	}
	tlen = aalen;

	bi_mul2(t, tlen, b, blen, a, alen);

	bi_free(t);
}

void	bi_mul2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen)
{
	if(alen < blen)
	{
		const dig_t*	td;
		len_t	tl;
		td = a;
		a = b;
		b = td;
		tl = alen;
		alen = blen;
		blen = tl;
	}
	__bi_mul(a, alen, b, blen, c, clen);
}

static void		__div_basic(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	dig_t* q, len_t* qlen)
{
	len_t	i, j, d, aalen;
	dig_t*	tt;
	ddig_t	u, v, m;

	aalen = *alen;
	d = aalen - blen;
	tt = bi_malloc(blen+1, __LINE__);

	for(i = d; i >= 0; i--)
	{
		if(aalen > blen+i)
		{
			m = a[aalen-1];
			m *= RADIX;
			m += a[aalen-2];
			u = (m  )/(b[blen-1]+1);
			v = (m+1)/(b[blen-1]  );
		}
		else if(aalen == blen+i)
		{
			u = (a[aalen-1]  )/(b[blen-1]+1);
			v = (a[aalen-1]+1)/(b[blen-1]  );
		}
		else
		{
			u = 0;
			v = 0;
		}

		if(u < 1)
		{
			u = 1;
		}
		if(v >= RADIX)
		{
			v = RADIX-1;
		}

		if(v > 0)
		{
			while(u <= v)
			{
				ddig_t	mm = (u+v)/2;
				int		c;

				if(mm > 0)
				{
					m = 0;
					for(j = 0; j < blen; j++)
					{
						m += b[j]*mm;
						tt[j] = m%RADIX;
						m /= RADIX;
					}
					if(m > 0)
					{
						tt[j++] = m;
					}
				}
				else
				{
					j = 0;
				}

				c = __cmp_shift(a, aalen, tt, j, i);
				if(c > 0)
				{
					u = mm+1;
				}
				else if(c < 0)
				{
					v = mm-1;
				}
				else
				{
					v = mm;
					break;
				}
			}

			if(v > 0)
			{
				m = 0;
				for(j = 0; j < blen; j++)
				{
					m += b[j]*v;
					tt[j] = m%RADIX;
					m /= RADIX;
				}
				if(m > 0)
				{
					tt[j++] = m;
				}

				bi_sub_shift(a, &aalen, tt, j, i);
			}
		}

		q[i] = v;
	}

	bi_free(tt);

	for(i = d; i >= 0 && 0 == q[i]; i--)
	{
		;
	}
	*qlen = i+1;
	*alen = aalen;
}

void	bi_div1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	dig_t* q, len_t* qlen)
{
	// b must NOT be zero.
	int		d = bi_cmp(a, *alen, b, blen);

	if(UNLIKELY(d < 0))
	{
		*qlen = 0;
		return;
	}
	if(UNLIKELY(0 == d))
	{
		*alen = 0;
		q[0] = 1;
		*qlen = 1;
		return;
	}

	if(UNLIKELY(1 == *alen))
	{
		q[0] = a[0]/b[0];
		*qlen = 1;
		a[0] %= b[0];
		*alen = (a[0] > 0);
		return;
	}

	{
		len_t	diff = *alen - blen;
		if(diff < 0)
		{
			diff = -diff;
		}
#define		MIN_NR_DIV_LEN	64
		if(*alen < MIN_NR_DIV_LEN || blen < MIN_NR_DIV_LEN || diff < MIN_NR_DIV_LEN)
		{
			__div_basic(a, alen, b, blen, q, qlen);
			return;
		}
	}

#define		INIT_PREC	32	// Must be <= MIN_NR_DIV_LEN

// Newton Raphson method.
	{
		dig_t*	x1;
		dig_t*	x2;
		dig_t*	tnum;
		len_t	i, j, t;
		len_t	x1len, x2len, tnumlen, L;
		dig_t*	tdig;

		L = *alen + INIT_PREC;

		x1 = bi_malloc(2*L+1, __LINE__);
		x2 = bi_malloc(2*L+1, __LINE__);
		tnum = bi_malloc(L+1, __LINE__);

		x1len = L - blen + 1 - INIT_PREC;
		for(i = 0; i < x1len; i++)
		{
			x1[i] = 0;
		}

		{
//			dig_t	aa[2*INIT_PREC], bb[INIT_PREC+1];
			dig_t*	aa;
			dig_t*	bb;
			dig_t*	qq = x1 + x1len;
			len_t	aalen = 0, bblen = 0, qqlen = 0;

			aa = bi_malloc(2*INIT_PREC, __LINE__);
			bb = bi_malloc(INIT_PREC+1, __LINE__);

			for(i = 0; i < 2*INIT_PREC-1; i++)
			{
				aa[i] = 0;
			}
			aa[i++] = 1;
			aalen = 2*INIT_PREC;

			if(blen >= INIT_PREC)
			{
				for(i = 0; i < INIT_PREC; i++)
				{
					bb[i] = b[blen-INIT_PREC+i];
				}
			}
			else
			{
				for(i = 0, t = INIT_PREC-blen; i < t; i++)
				{
					bb[i] = 0;
				}
				for(j = 0; j < blen; j++)
				{
					bb[i++] = b[j];
				}
			}
			bblen = INIT_PREC;

			if(blen > INIT_PREC)
			{
				bi_inc(bb, &bblen);
			}

			for(i = 0; i < bblen; i++)
			{
				if(aa[i] || bb[i])
				{
					break;
				}
			}
			aalen -= i;
			bblen -= i;

			__div_basic(aa+i, &aalen, bb+i, bblen, qq, &qqlen);
			x1len += qqlen;

			bi_free(aa);
			bi_free(bb);
		}

		while(1)
		{
			// t1 = b*x1;
			bi_mul2(b, blen, x1, x1len, tnum, &tnumlen);

			// t1 = 2-b*x1;
			for(i = 0; 0 == tnum[i]; i++)
			{
				;
			}
			tnum[i] = RADIX - tnum[i];
			for(i++; i < tnumlen; i++)
			{
				tnum[i] = RADIX-1 - tnum[i];
			}
			for(; i < L; i++)
			{
				tnum[i] = RADIX-1;
			}
			tnum[L] = 1;
			tnumlen = L+1;

			// x2 = x1*(2-b*x1)
			bi_mul2(x1, x1len, tnum, tnumlen, x2, &x2len);

			// scale down x2 by L
			if(x2len > 2*L)
			{
				for(i = 0; i < L; i++)
				{
					x2[i] = x2[i+L];
				}
				x2[L] = x2[2*L];
			}
			else
			{
				for(i = 0, t = x2len-L; i < t; i++)
				{
					x2[i] = x2[i+L];
				}
			}
			x2len -= L;
		
			if(UNLIKELY(bi_cmp(x1, x1len, x2, x2len) >= 0))
			{
				break;
			}

			// x1 <-> x2;
			tdig = x1;
			x1 = x2;
			x2 = tdig;
			x1len = x2len;
		}

		bi_free(tnum);

		bi_mul2(a, *alen, x1, x1len, x2, &x2len);

		*qlen = x2len - L;
		for(i = 0, t = *qlen; i < t; i++)
		{
			q[i] = x2[i+L];
		}

		bi_free(x2);

		bi_mul2(b, blen, q, *qlen, x1, &x1len);

		bi_sub1(a, alen, x1, x1len);

		bi_free(x1);
	
		// Actually at most once if b divides a
		while(bi_cmp(a, *alen, b, blen) >= 0)
		{
			bi_sub1(a, alen, b, blen);
//			printf("========= %lld %lld\n", *alen, blen);
			bi_inc(q, qlen);
		}
	}
}

void	bi_div2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* q, len_t* qlen,
	dig_t* r, len_t* rlen)
{
	len_t		i;

	dig_t*	rr = bi_malloc(alen, __LINE__);
	len_t		rrlen;

	memcpy(rr, a, sizeof(dig_t)*alen);
	rrlen = alen;

	bi_div1(rr, &rrlen, b, blen, q, qlen);

	if(r && rlen)
	{
		for(i = 0; i < rrlen; i++)
		{
			r[i] = rr[i];
		}
		*rlen = rrlen;
	}
	bi_free(rr);
}

static dig_t	__simple_sqrt(ddig_t a)
{
	dig_t	u = 0, v = RADIX, m;
	ddig_t	d;

	while(u <= v)
	{
		m = (u+v)/2;
		d = ((ddig_t)m)*m;
		if(d < a)
		{
			u = m+1;
		}
		else if(d > a)
		{
			v = m-1;
		}
		else
		{
			return m;
		}
	}
	return v;
}

/*
	1. Calculate 1/sqrt(a) with y = x^(-2) - a
	2. Calculate sqrt(a) from a*(1/sqrt(a))

	Newton-Raphson iteration for y = x^(-2) - a
	    x <- x*(3-a*x^2)/2

	divide by 2 : Multiply by RADIX/2 and shift right by 1.

	No division envolved !!!
*/

// shift >= 0
// sqrt( a * RADIX^shift )
void	bi_sqrt(const dig_t* a, len_t alen, len_t shift, dig_t* r, len_t* rlen)
{
	dig_t	*x1, *x2, *t;
	len_t	i, x1len, x2len;
	len_t	ss;

	if(alen <= 0)
	{
		*rlen = 0;
		return;
	}
	if(0 == shift)
	{
		if(1 == alen)
		{
			r[0] = __simple_sqrt(a[0]);
			*rlen = 1;
			return;
		}
		if(2 == alen)
		{
			r[0] = __simple_sqrt(((ddig_t)RADIX)*a[1] + a[0]);
			*rlen = 1;
			return;
		}
	}

	ss = (alen+shift+1) + 2 + 4;
	x1 = bi_malloc(2*(ss+1), __LINE__);
	x2 = bi_malloc(2*(ss+1), __LINE__);

	{
		int		d;
		len_t	iz;
		dig_t	rt;
		ddig_t	m;

		// alen > 0 here.
		m = a[alen-1];
		if((alen+shift)%2)	// odd length
		{
			iz = (alen+shift)/2;
		}
		else	// even length
		{
			iz = (alen+shift)/2 - 1;
			m *= RADIX;
			if(alen >= 2)
			{
				m += a[alen-2];
			}
		}

		rt = __simple_sqrt(m);

		for(i = 0; i < iz; i++)
		{
			x1[i] = 0;
		}
		x1[i++] = rt;
		x1len = i;

		bi_mul2(x1, x1len, x1, x1len, x2, &x2len);
		d = __cmp_shift(x2, x2len, a, alen, shift);
		if(d < 0)
		{
			// rt = ceil(sqrt(m+1));
			m++;
			rt = __simple_sqrt(m);
			if(((ddig_t)rt)*((ddig_t)rt) < m)
			{
				rt++;
			}
		}
		else if(0 == d)	// Lucky!
		{
			for(i = 0; i < x1len; i++)
			{
				r[i] = x1[i];
			}
			*rlen = x1len;
			bi_free(x1);
			bi_free(x2);
			return;
		}

		// rt * R^iz
		if(rt <= 1)	// Must be 1. Actually, should not reach here.
		{
			// 1 * R^(-iz)
			x1len = ss-iz+1;
			i = x1len-1;
			x1[i--] = 1;
			while(i >= 0)
			{
				x1[i--] = 0;
			}
		}
		else
		{
			// R/rt * R^(-(iz+1))
			x1len = ss-(iz+1)+1;
			i = x1len-1;
			x1[i--] = RADIX/rt;
			while(i >= 0)
			{
				x1[i--] = 0;
			}
		}
	}

	x2len = 0;

	while(bi_cmp(x1, x1len, x2, x2len))
	{
		// Compute x <- x*(3-a*x^2)/2

		// x2 = 3 - a*x1^2
		for(i = 0; i < alen; i++)
		{
			x2[i+shift] = a[i];
		}
		for(i = 0; i < shift; i++)
		{
			x2[i] = 0;
		}
		x2len = alen;
		bi_mul1(x2+shift, &x2len, x1, x1len);
		bi_mul1(x2+shift, &x2len, x1, x1len);
		x2len += shift;
		bi_rshift(x2, &x2len, ss);
	
		for(i = 0; 0 == x2[i]; i++)
		{
			;
		}
		x2[i] = RADIX - x2[i];
		for(i++; i < x2len; i++)
		{
			x2[i] = RADIX-1 - x2[i];
		}
		for(; i < ss; i++)
		{
			x2[i] = RADIX-1;
		}
		x2[ss] = 2;
		x2len = ss+1;

		// x2 = (x2*x1)/2
		bi_mul1(x2, &x2len, x1, x1len);
		bi_rshift(x2, &x2len, ss);
		__bi_div_by_2(x2, &x2len);

		t = x1;
		x1 = x2;
		x2 = t;
		i = x1len;
		x1len = x2len;
		x2len = i;
	}

	bi_mul2(a, alen, x2, x2len, x1+shift, &x1len);
	for(i = 0; i < shift; i++)
	{
		x1[i] = 0;
	}
	x1len += shift;
	for(i = ss; i < x1len; i++)
	{
		r[i-ss] = x1[i];
	}
	*rlen = x1len - ss;
	bi_free(x1);

	while(1)
	{
		// Actually, this block runs just once.
		bi_inc(r, rlen);
		bi_mul2(r, *rlen, r, *rlen, x2, &x2len);
		i = __cmp_shift(x2, x2len, a, alen, shift);
		if(i > 0)
		{
			bi_dec(r, rlen);
			break;
		}
		else if(0 == i)
		{
			break;
		}
	}
	bi_free(x2);
}

void	bi_pow(const dig_t* a, len_t alen, len_t b, dig_t* c, len_t* clen)
{
	dig_t	*p1, *p2;
	len_t	p1len, p2len;

	if(UNLIKELY(alen <= 0))
	{
		*clen = 0;
		return;
	}
	c[0] = 1;
	*clen = 1;

	if(b <= 0)
	{
		return;
	}

	p1 = bi_malloc(alen*b + 1, __LINE__);
	p2 = bi_malloc(alen*b + 1, __LINE__);

	memcpy(p1, a, alen*sizeof(dig_t));
	p1len = alen;

	while(1)
	{
		dig_t	*t;

		if(b&1)
		{
			bi_mul1(c, clen, p1, p1len);
		}
		b >>= 1;
		if(!b)
		{
			break;
		}
		bi_mul2(p1, p1len, p1, p1len, p2, &p2len);
		t = p1;
		p1 = p2;
		p2 = t;
		p1len = p2len;
	}
	bi_free(p1);
	bi_free(p2);
}

void	bi_fac(len_t u, len_t v, dig_t** n, len_t *nlen, len_t *nzeros)
{
	if(v-u < 100)
	{
		len_t	i;
		// 2^127 - 1 --> 39 digits in decimal.
		dig_t	*a, *aa, b[40];
		len_t	alen = (40*(v-u) + LOG10_RADIX-1) / LOG10_RADIX, blen, aalen;

		if(alen < 1)
		{
			alen = 1;
		}

		a = bi_malloc(alen, __LINE__);
		aa = bi_malloc(alen, __LINE__);
		a[0] = 1;
		alen = 1;

		for(i = u+1; i <= v; i++)
		{
			len_t	x = i;

			for(blen = 0; x > 0; blen++)
			{
				b[blen] = x % RADIX;
				x /= RADIX;
			}

			bi_elementary_mul(a, alen, b, blen, aa, &aalen);

			{
				dig_t	*t = a;
				a = aa;
				aa = t;
			}
			alen = aalen;
		}
		bi_free(aa);

		*n = a;
		*nlen = alen;
		if(nzeros)
		{
			*nzeros = 0;
		}
		return;
	}
/*
	if(v-u >= 100000)
	{
		fprintf(stderr, "++++ %10d, %10d, %10d\n", u, v, v-u);
	}
*/
	{
		dig_t	*a, *b, *r;
		len_t	alen, blen, azlen, bzlen, rlen, as = 0, bs = 0;
		len_t	m = (u+v)/2;

		bi_fac(u, m, &a, &alen, &azlen);
		for(as = 0; a[as] == 0; as++)
		{
			;
		}
		bi_fac(m, v, &b, &blen, &bzlen);
		for(bs = 0; b[bs] == 0; bs++)
		{
			;
		}
		if(nzeros)
		{
			r = bi_malloc(alen-as + blen-bs, __LINE__);
			bi_mul2(a+as, alen-as, b+bs, blen-bs, r, &rlen);
		}
		else
		{
			len_t	d = azlen+as + bzlen+bs;

			r = bi_malloc(alen + blen + d, __LINE__);
			bi_mul2(a+as, alen-as, b+bs, blen-bs, r+d, &rlen);
			memset(r, 0, sizeof(dig_t)*d);
			rlen += d;
		}
		bi_free(a);
		bi_free(b);
		*n = r;
		*nlen= rlen;
		if(nzeros)
		{
			*nzeros = azlen + as + bzlen + bs;
		}
	}
/*
	if(v-u >= 100000)
	{
		fprintf(stderr, "---- %10d, %10d, %10d\n", u, v, v-u);
	}
*/
}

len_t	bi_b10_len(const dig_t* a, len_t alen)
{
	dig_t	msb;
	int		i;
	len_t	dlen;

	// skip leading zeros.
	alen--;
	while(alen >= 0 && 0 == a[alen])
	{
		alen--;
	}
	alen++;

	if(alen <= 0)
	{
		return 0;
	}

	msb = a[alen-1];
	for(i = LOG10_RADIX-1; msb < g_pow10[i]; i--)
	{
		;
	}
	dlen = i+1;
	dlen += LOG10_RADIX*(alen-1);

	return dlen;
}

static int	__g_did_init = 0;

int		bi_init(int quiet)
{
	int		i;
	
	if(__g_did_init)
	{
		return 1;
	}

	g_pow10[0] = 1;
	for(i = 1; i < LOG10_RADIX; i++)
	{
		g_pow10[i] = 10*g_pow10[i-1];
	}

#ifdef	PARAL_MULT
	{
		char  *str;
		int   procs_on_system = sysconf(_SC_NPROCESSORS_ONLN);

		str = getenv("BC_PARAL_CNT");
		if(str && 1 == sscanf(str, "%u", &__g_paral_cnt))
		{
			;
		}
		else
		{
			__g_paral_cnt = procs_on_system;
		}
		if(__g_paral_cnt < 1)
		{
			__g_paral_cnt = 1;
		}
		else if(__g_paral_cnt > procs_on_system)
		{
			__g_paral_cnt = procs_on_system;
		}
		if(!quiet && isatty(0) && isatty(1))
		{
			fprintf(stderr, "================================\n");
			if(str)
			{
				fprintf(stderr, " BC_PARAL_CNT = %s\n", str);
			}
			fprintf(stderr, " %d-threaded multiplication\n", __g_paral_cnt);
			fprintf(stderr, "================================\n");
		}
	}

	__g_bFinish = 0;

	if(__g_paral_cnt >= 2)
	{
		pthread_mutex_init(&__g_lock, NULL);
		event_init(&__g_event_put);
		event_init(&__g_event_get);

		for(i = 0; i < sizeof(__g_mi)/sizeof(__g_mi[0]); i++)
		{
			__g_mi[i].state = 0;
		}

		for(i = 0; i < __g_paral_cnt; i++)
		{
			pthread_create(&(__g_thr[i]), (pthread_attr_t*)0, __mul_thread_proc, NULL);
		}
	}
#endif

	__g_did_init = 1;
	return 1;
}

void	bi_deinit(void)
{
	if(!__g_did_init)
	{
		return;
	}

#ifdef	PARAL_MULT
	if(__g_paral_cnt >= 2)
	{
		int		i;

		__g_bFinish = 1;
		for(i = 0; i < __g_paral_cnt; i++)
		{
			event_inc(&__g_event_put);
		}
		for(i = 0; i < __g_paral_cnt; i++)
		{
			pthread_join(__g_thr[i], (void**)0);
		}

		event_deinit(&__g_event_get);
		event_deinit(&__g_event_put);
		pthread_mutex_destroy(&__g_lock);
	}
#endif

	__g_did_init = 0;
}



dig_t* bi_malloc(len_t n, int ln)
{
	if(n > 0)
	{
		dig_t* ptr;
		ptr = (dig_t*)malloc(sizeof(dig_t)*n);
		if(ptr)
		{
			return ptr;
		}
		fprintf(stderr, "Out of memory!");
		exit(-1);
	}
	return (dig_t*)0;
}

void   bi_free(dig_t* ptr)
{
	if(ptr)
	{
		free(ptr);
	}
}

