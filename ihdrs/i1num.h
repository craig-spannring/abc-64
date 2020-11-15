/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I1NUM_h_9c1d8afe2422b08d3311f4b1691bbedb
#define I1NUM_h_9c1d8afe2422b08d3311f4b1691bbedb

#include "b1grab.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* Full numeric package: private definitions                            */
/*                                                                      */
/* A number is modelled as one of zero, unbounded integer,              */
/*        unbounded rational or approximate.                            */
/*     Zero has a 'length' field of zero, and nothing else.             */
/*     A length field of +n means the number is an n digit integer,     */
/*        (with digits to some large base).                             */
/*     A length of -1 means there follow two floating point numbers,    */
/*        one the fraction (zero or .5 <= frac <= 1), one the exponent  */
/*        with respect to base 2 (should be an integral value).         */
/*        (This is so when EXT_RANGE is defined.  Otherwise, there is   */
/*        only one field, frac, which is not normalized.  This saves    */
/*        code and data space on e.g. the IBM PC, where the natural     */
/*        range of double's is sufficient (~1E307).)                    */
/*     A length of -2 means there follow two values, pointers to two    */
/*        unbounded integers, ie a rational number.                     */
/*     A length of -n, n>2, means it is a rational with a print width   */
/*        of n-2.                                                       */
/*                                                                      */
/************************************************************************/

/*************** Definitions exported for integers *****************/

/* typedef int digit; or short; calculated in mkconfig -> config.h */

typedef struct integer_ {
	HEADER;
	digit	dig[1];
} *integer;

#define FreezeSmallInt(v, vv) \
	(IsSmallInt(v) && (Freeze1(v, vv), Freeze2(v, vv)))
#define Freeze1(v, vv) ((vv).type= Num, (vv).refcnt= Maxrefcnt)
#define Freeze2(v, vv) \
	((vv).len= (v) != 0, (vv).dig[0]= SmallIntVal(v), (v)= &(vv))

integer int_gadd(integer v, integer w, intlet factor);
integer int_canon(integer v);
integer int_sum(integer v, integer w);
integer int_prod(integer v, integer w);
integer int_diff(integer v, integer w);
integer int_quot(integer v, integer w);

#define int_0 ((integer) MkSmallInt(0))
#define int_1 ((integer) MkSmallInt(1))
#define int_2 ((integer) MkSmallInt(2))
#define int_5 ((integer) MkSmallInt(5))
#define int_10 ((integer) MkSmallInt(10))
#define int_min1 ((integer) MkSmallInt(-1))

#define Integral(v) (IsSmallInt(v) || Length(v)>=0)
#define Modulo(a,b) (((a)%(b)+(b))%(b))
#define Digit(v,n) ((v)->dig[n])
#define Msd(v) (IsSmallInt(v) ? SmallIntVal(v) : Digit(v,Length(v)-1))
#define Lsd(v) (IsSmallInt(v) ? SmallIntVal(v) : Digit(v,0))

#define Odd(x) ((x)&1)
#define Even(x) (!Odd(x))

/* Provisional definitions */

#define Copy(x) copy((value)(x))
#define Release(x) release((value)(x))

/***************** Definitions exported for rationals *****************/

typedef struct {
	HEADER;
	integer	num, den;
} *rational;


#define Numerator(a) ((a)->num)
#define Denominator(a) ((a)->den)
#define Rational(a) (!IsSmallInt(a) && Length(a)<-1)
#define Roundsize(a) (-2-Length(a))

rational mk_rat(integer x, integer y, int len, bool simplify);
  rational rat_sum(rational u, rational v);
rational rat_diff(rational u, rational v);
rational rat_neg(rational u);
rational rat_prod(rational u, rational v);
rational rat_quot(rational u, rational v);
rational rat_power(rational a, integer n);
rational rat_zero(void);

extern rational rat_half;

value tento(int n);
value mk_exact(integer p, integer q, int len);

/***************** Definitions exported for approximate numbers *************/

typedef struct real_ {
	HEADER;
	double	frac;
#ifdef EXT_RANGE
	double	expo;
#endif /* EXT_RANGE */
} *real;

#define Frac(v) ((v)->frac)
#ifdef EXT_RANGE
#define Expo(v) ((v)->expo)
#else
#define Expo(v) 0.0
#endif

#define Approximate(v) (!IsSmallInt(v) && Length(v)==-1)
#define Exact(v) (!Approximate(v))

extern real app_0;

real mk_approx(double frac, double expo);

real app_sum(real u, real v);
real app_diff(real u, real v);
real app_prod(real u, real v);
real app_quot(real u, real v);
real app_neg(real u);

real app_exp(real v);
real app_log(real v);
real app_power(real u, real v);

value app_frexp(value);
integer app_floor(real);
value app_exactly(real);

value prod2n(value v, value n, bool simplify);
value prod10n(value v, int n, bool simplify);
rational ratsumhalf(rational u);

value grab_num(int len);
value regrab_num(value v, int len);
value grab_rat(int len);

#ifdef __cplusplus
}
#endif


#endif
