/* bi.h: Arbitrary precision numbers in base 10^k header file. */
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

#ifndef		__BI_H__
#define		__BI_H__

#include	<stdint.h>

// Supports 32-bit, 64-bit only.



// FORCE_BASE values are for checking robustness of the algorithm.
// All cases have been tested. OK.
// Best let compilers decide.

//#define		FORCE_BASE	10
//#define		FORCE_BASE	100
//#define		FORCE_BASE	1000
//#define		FORCE_BASE	10000
//#define		FORCE_BASE	100000
//#define		FORCE_BASE	1000000
//#define		FORCE_BASE	10000000
//#define		FORCE_BASE	100000000

#if FORCE_BASE == 10			// Force base 10
		typedef		char		dig_t;
		#define		RADIX		10
		#define		LOG10_RADIX	1
		#define		ARI_INV_3	7	// For div 3N by 3
#elif FORCE_BASE == 100			// Force base 10^2
		typedef		char		dig_t;
		#define		RADIX		100
		#define		LOG10_RADIX	2
		#define		ARI_INV_3	67	// For div 3N by 3
#elif FORCE_BASE == 1000		// Force base 10^3
		typedef		int16_t		dig_t;
		#define		RADIX		1000
		#define		LOG10_RADIX	3
		#define		ARI_INV_3	667	// For div 3N by 3
#elif FORCE_BASE == 10000		// Force base 10^4
		typedef		int16_t		dig_t;
		#define		RADIX		10000
		#define		LOG10_RADIX	4
		#define		ARI_INV_3	6667	// For div 3N by 3
#elif FORCE_BASE == 100000		// Force base 10^5
		typedef		int32_t		dig_t;
		#define		RADIX		100000
		#define		LOG10_RADIX	5
		#define		ARI_INV_3	66667	// For div 3N by 3
#elif FORCE_BASE == 1000000		// Force base 10^6
		typedef		int32_t		dig_t;
		#define		RADIX		1000000
		#define		LOG10_RADIX	6
		#define		ARI_INV_3	666667	// For div 3N by 3
#elif FORCE_BASE == 10000000	// Force base 10^7
		typedef		int32_t		dig_t;
		#define		RADIX		10000000
		#define		LOG10_RADIX	7
		#define		ARI_INV_3	6666667	// For div 3N by 3
#elif FORCE_BASE == 100000000	// Force base 10^8
		typedef		int32_t		dig_t;
		#define		RADIX		100000000
		#define		LOG10_RADIX	8
		#define		ARI_INV_3	66666667	// For div 3N by 3
// Guess best.
#else
	#if	defined(__LP64__)		// Base 10^8 for 64-bit
		typedef		int32_t		dig_t;
		#define		RADIX		100000000
		#define		LOG10_RADIX	8
		#define		ARI_INV_3	66666667	// For div 3N by 3
	#else						// Base 10^4 for 32-bit
		typedef		int16_t		dig_t;
		#define		RADIX		10000
		#define		LOG10_RADIX	4
		#define		ARI_INV_3	6667	// For div 3N by 3
	#endif
#endif

#if	defined(__LP64__) || FORCE_BASE > 10000 	// For 64-bit
	typedef		int64_t		len_t;
	typedef		int64_t		ddig_t;
#else
	typedef		int32_t		len_t;
	typedef		int32_t		ddig_t;
#endif

#if	0	// For 128-bit machine in the future.
	typedef		int128_t		len_t;
	typedef		int64_t			dig_t;
	typedef		int128_t		ddig_t;
	#define		RADIX			10000000000000000
	#define		LOG10_RADIX		16
	#define		ARI_INV_3		6666666666666667
#endif

// must be sizeof(len_t) >= sizeof(ddig_t), sizeof(ddig_t) >= 2*sizeof(dig_t)

#ifdef	__cplusplus
extern "C"
{
#endif

int		bi_init(int quiet);
void	bi_deinit(void);

dig_t* bi_malloc(len_t n, int line_num);
void   bi_free(dig_t* ptr);

int		bi_from_string(dig_t* a, len_t* alen, const char* str, len_t len);
int		bi_from_chars(dig_t* a, len_t* alen, const char* str, len_t len);
len_t	bi_to_chars(const dig_t* a, len_t alen, char* str);
int		bi_cmp(const dig_t* a, len_t alen, const dig_t* b, len_t blen);

void	bi_inc(dig_t* a, len_t* alen);
void	bi_dec(dig_t* a, len_t* alen);

void	bi_add1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen);

void	bi_add2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen);

void	bi_add_shift(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	len_t s);

void	bi_sub1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen);

void	bi_sub2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen);

void	bi_sub_shift(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	len_t s);

void	bi_mul1_one_digit(
	dig_t* a, len_t* alen,
	dig_t b);
void	bi_mul2_one_digit(
	const dig_t* a, len_t alen,
	dig_t b,
	dig_t* c, len_t* clen);

void	bi_elementary_mul(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen);

void	bi_mul1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen);

void	bi_mul2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* c, len_t* clen);

void	bi_div1(
	dig_t* a, len_t* alen,
	const dig_t* b, len_t blen,
	dig_t* q, len_t* qlen);

void	bi_div2(
	const dig_t* a, len_t alen,
	const dig_t* b, len_t blen,
	dig_t* q, len_t* qlen,
	dig_t* r, len_t* rlen);

void	bi_pow(
	const dig_t* a, len_t alen,
	len_t b,
	dig_t* c, len_t* clen);

// Product of all integers in (u,v]
void	bi_fac(
	ddig_t u, ddig_t v,
	dig_t** n, len_t *nlen, len_t *nzeros);

void	bi_sqrt(
	const dig_t* a, len_t alen,
	len_t scale,
	dig_t* r, len_t* rlen);

len_t	bi_b10_len(const dig_t* a, len_t alen);

#ifdef	__cplusplus
}
#endif

#endif
