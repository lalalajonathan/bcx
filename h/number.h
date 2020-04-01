/* number.h: Arbitrary precision numbers header file. */
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

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "lib/bi.h"

//typedef enum {PLUS, MINUS} sign;

typedef struct bc_struct *bc_num;

typedef struct bc_struct
    {
      int     n_sign; /* negative, 0, positive */
      len_t   n_len;	/* The number of digits before the decimal point. */
      len_t   n_scale;	/* The number of digits after the decimal point. */
      int   n_refs;     /* The number of pointers to this number. */
      bc_num n_next;	/* Linked list for available list. */
      /*dig_t *n_ptr;*/	/* The pointer to the actual storage.
			   If NULL, n_value points to the inside of
			   another number (bc_multiply...) and should
			   not be "freed." */
      dig_t *n_value;	/* The number. Not zero char terminated.
			   May not point to the same place as n_ptr as
			   in the case of leading zeros generated. */

      len_t n_dec_scale;  /* scale in decimal */
    } bc_struct;


/* The base used in storing the numbers in n_value above.
   Currently this MUST be 10. */

//#define BASE 10

/*  Some useful macros and constants. */

#define CH_VAL(c)     (c - '0')
#define BCD_CHAR(d)   (d + '0')

#ifdef MIN
#undef MIN
#undef MAX
#endif
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))
#define ODD(a)        ((a)&1)

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef LONG_MAX
#define LONG_MAX 0x7fffffff
#endif


/* Global numbers. */
extern bc_num _zero_;
extern bc_num _one_;
extern bc_num _two_;


/* Function Prototypes */

void bc_init_numbers (void);

bc_num bc_new_num (len_t len, len_t dec_scale);

bc_num  bc_dup_num(bc_num num);
len_t bc_dec_len(bc_num num);

void bc_free_num (bc_num *num);

bc_num bc_copy_num (bc_num num);

void bc_init_num (bc_num *num);

//void bc_str2num (bc_num *num, char *str, len_t scale);

//char *bc_num2str (bc_num num);

void bc_int2num (bc_num *num, len_t val);

int bc_num2long (bc_num num, len_t* ret);

int bc_compare (bc_num n1, bc_num n2);

char bc_is_zero (bc_num num);

//char bc_is_near_zero (bc_num num, int scale);

char bc_is_neg (bc_num num);

void bc_add (bc_num n1, bc_num n2, bc_num *result, len_t dec_scale_min);

void bc_sub (bc_num n1, bc_num n2, bc_num *result, len_t dec_scale_min);

void bc_clear_extra_fraction(bc_num num);

void bc_multiply (bc_num n1, bc_num n2, bc_num *prod, len_t dec_scale);

int bc_divide (bc_num n1, bc_num n2, bc_num *quot, len_t dec_scale);

int bc_modulo (bc_num num1, bc_num num2, bc_num *result, len_t dec_scale);

int bc_divmod (bc_num num1, bc_num num2, bc_num *quot,
			   bc_num *rem, len_t dec_scale);

int bc_raisemod (bc_num base, bc_num expo, bc_num mod,
			     bc_num *result, len_t dec_scale);

void bc_raise (bc_num num1, bc_num num2, bc_num *result,
			   len_t dec_scale);

int bc_sqrt (bc_num *num, len_t dec_scale);

void bc_out_num (bc_num num, int o_base, void (* out_char)(int),
			     int leading_zero);

int   bc_dec_num2str(dig_t d, char *str, int leading_zero);
void bc_out_long (long val, int size, int space, void (*out_char)(int));

int bc_factorial(bc_num *n);
int bc_permutation(bc_num *n, bc_num *r);
int bc_combination(bc_num *n, bc_num *r);

#endif
