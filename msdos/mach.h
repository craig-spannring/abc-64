/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef MACH_h_78b1b3538b514f1f755f05b637f8a18a
#define MACH_h_78b1b3538b514f1f755f05b637f8a18a

#ifdef __cplusplus
extern "C" {
#endif
/* char=8 bits, signed */
/* maxshort=32767 (=2**15-1) */
/* maxint=32767 (=2**15-1) */
/* maxlong=2147483647 (=2**31-1) */
/* pointers=16 bits */
/* base=2 */
/* Significant base digits=53 */
/* Smallest x such that 1.0-base**x != 1.0=-53 */
/* Small x such that 1.0-x != 1.0=1.11022e-016 */
/* Smallest x such that 1.0+base**x != 1.0=-52 */
/* Smallest x such that 1.0+x != 1.0=2.22045e-016 */
/* Arithmetic chops but uses guard digits */
/* Number of bits used for exponent=11 */
/* Minimum normalised exponent=-1021 */
/* Minimum normalised positive number=2.22507e-308 */
/* The smallest numbers are not kept normalised */
/* Smallest unnormalised positive number=4.94066e-324 */
/* Maximum exponent=1024 */
/* Maximum number=1.79769e+308 */
/* Double arithmetic uses a hidden bit */

/* Numeric package constants */
#define Maxintlet 32767 /* Maximum short */
#define Maxint 32767 /* Maximum int */
typedef int digit;
typedef long twodigit;
/* ABCBASE must be a power of ten, ABCBASE**2 must fit in a twodigit */
/* and -2*ABCBASE as well as ABCBASE*2 must fit in a digit */
#define ABCBASE 10000
#define tenlogBASE 4 /*  = log10(ABCBASE) */
#define BIG 9007199254740991.0 /* Maximum integral double */
#define MAXNUMDIG 16 /* The number of decimal digits in BIG */
#define MINNUMDIG 6 /* Don't change: this is here for consistency */
#define Maxreal 1.797693e+308 /* Maximum double */
#define Maxexpo 1024 /* Maximum value such that 2**Maxexpo<=Maxreal */
#define Minexpo (-1021) /* Minimum value such that -2**Minexpo>=Minreal */
#define DBLBITS 53 /* The number of bits in the fraction of a double */
#define LONGBITS 31 /* The number of bits in a long */
#define TWOTO_DBLBITSMIN1 4503599627370496.0 /* 2**(DBLBITS-1) */
#define TWOTO_LONGBITS 2147483648.0 /* 2**LONGBITS */

/* Enable fair choice from object whose size exceeds */

/* the maximum allowed by the granularity of random(): */
#define RNDM_LIMIT 1125899906842624.0 /* safe limit for choice */

/* ABC's Small Integer Representation (compare bhdrs/b.h) */
/* These values must be so because of the canonical number representation */
#define MaxSmallInt (ABCBASE-1) /* Do not change! */
#define MinSmallInt (-ABCBASE) /* Do not change! */

#define Maxtrig BIG /* Max x for sin(x), cos(x), tan(x) */

#define FILLER_FIELD 
#define HEADER literal type; reftype refcnt; intlet len FILLER_FIELD
#define FILLER

#ifdef __cplusplus
}
#endif


#endif
