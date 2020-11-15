/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* Functions defined on numeric values. */

#include <errno.h> /* For EDOM and ERANGE */

#include "b.h"
#include "bobj.h"
#include "i0err.h"
#include "i1nua.h"
#include "i1nui.h"
#include "i1num.h"
#include "i3err.h"

/*
 * The visible routines here implement predefined B arithmetic operators,
 * taking one or two numeric values as operands, and returning a numeric
 * value.
 * No type checking of operands is done: this must be done by the caller.
 */

typedef value (*valfun)();
typedef rational (*ratfun)();
typedef real (*appfun)();
typedef double (*mathfun)();

/*
 * For the arithmetic functions (+, -, *, /) the same action is needed:
 * 1) if both operands are Integral, use function from int_* submodule;
 * 2) if both are Exact, use function from rat_* submodule (after possibly
 *    converting one of them from Integral to Rational);
 * 3) otherwise, make both approximate and use function from app_*
 *    submodule.
 * The functions performing the appropriate action for each of the submodules
 * are passed as parameters.
 * Division is a slight exception, since i/j can be a rational.
 * See `quot' below.
 */

Hidden value dyop(value u, value v, valfun int_fun, ratfun rat_fun, appfun app_fun)
{
	if (Integral(u) && Integral(v))	/* Use integral operation */
		return (*int_fun)((integer)u, (integer)v);

	if (Exact(u) && Exact(v)) {
		rational u1, v1, a;

		/* Use rational operation */

		u1 = Integral(u) ? mk_rat((integer)u, int_1, 0, Yes) :
				(rational) Copy(u);
		v1 = Integral(v) ? mk_rat((integer)v, int_1, 0, Yes) :
				(rational) Copy(v);
		a = (*rat_fun)(u1, v1);
		Release(u1);
		Release(v1);

		if (Denominator(a) == int_1 && Roundsize(a) == 0) {
			integer b = (integer) Copy(Numerator(a));
			Release(a);
			return (value) b;
		}

		return (value) a;
	}

	/* Use approximate operation */

	{
		real u1, v1, a;
		u1 = Approximate(u) ? (real) Copy(u) : (real) approximate(u);
		v1 = Approximate(v) ? (real) Copy(v) : (real) approximate(v);
		a = (*app_fun)(u1, v1);
		Release(u1);
		Release(v1);

		return (value) a;
	}
}


Visible value sum(value u, value v) {
	if (IsSmallInt(u) && IsSmallInt(v))
		return (value) mk_int(
			(double)SmallIntVal(u) + (double)SmallIntVal(v));
	return dyop(u, v, (value (*)())int_sum, rat_sum, app_sum);
}

Visible value diff(value u, value v) {
	if (IsSmallInt(u) && IsSmallInt(v))
		return (value) mk_int(
			(double)SmallIntVal(u) - (double)SmallIntVal(v));
	return dyop(u, v, (value (*)())int_diff, rat_diff, app_diff);
}

Visible value prod(value u, value v) {
	if (IsSmallInt(u) && IsSmallInt(v))
		return (value) mk_int(
			(double)SmallIntVal(u) * (double)SmallIntVal(v));
	return dyop(u, v, (value (*)())int_prod, rat_prod, app_prod);
}


/*
 * We cannot use int_quot (which performs integer division with truncation).
 * Here is the routine we need.
 */

Hidden value xxx_quot(integer u, integer v) {

	if (v == int_0) {
		interr(ZERO_DIVIDE);
		return (value) Copy(u);
	}

	return mk_exact(u, v, 0);
}

Visible value quot(value u, value v) {
	return dyop(u, v, xxx_quot, rat_quot, app_quot);
}


/*
 * Unary minus and abs follow the same principle but with only one operand.
 */

Visible value negated(value u) {
	if (IsSmallInt(u)) return mk_integer(-SmallIntVal(u));
	if (Integral(u))
		return (value) int_neg((integer)u);
	if (Rational(u))
		return (value) rat_neg((rational)u);
	return (value) app_neg((real)u);
}


Visible value absval(value u) {
	if (Integral(u)) {
		if (Msd((integer)u) < 0)
			return (value) int_neg((integer)u);
	} else if (Rational(u)) {
		if (Msd(Numerator((rational)u)) < 0)
			return (value) rat_neg((rational)u);
	} else if (Approximate(u) && Frac((real)u) < 0)
		return (value) app_neg((real)u);

	return Copy(u);
}


/*
 * The remaining operators follow less similar paths and some of
 * them contain quite subtle code.
 */

Visible value vmod(value u, value v) {
	value q, f, d, p;

	if (v == (value)int_0 ||
      (Rational(v) && Numerator((rational)v) == int_0) ||
      (Approximate(v) && Frac((real)v) == 0)) {
		interr(MESS(600, "in x mod y, y is zero"));
		return Copy(u);
	}

	if (Integral(u) && Integral(v))
		return (value) int_mod((integer)u, (integer)v);

	/* Compute `(u/v-floor(u/v))*v', which prevents loss of precision;
	   don't use `u-v*floor(u/v)', as in the formal definition of `mod'. */

	q = quot(u, v);
	f = floor_f(q);
	d = diff(q, f);
	release(q);
	release(f);
	p = prod(d, v);
	release(d);

	return p;
}


/*
 * u**v has the most special cases of all the predefined arithmetic functions.
 */

Visible value vpower(value u, value v) {
	real ru, rv, rw;
	if (Exact(u) && (Integral(v) ||
			/* Next check catches for integers disguised as rationals: */
                   (Rational(v) && Denominator((rational)v) == int_1))) {
		rational a;
		integer b = Integral(v) ? (integer)v : Numerator((rational)v);
			/* Now b is really an integer. */

		u = Integral(u) ? (value) mk_rat((integer)u, int_1, 0, Yes) :
				Copy(u);
		a = rat_power((rational)u, b);
		Release(u);
		if (Denominator(a) == int_1) { /* Make integral result */
			b = (integer) Copy(Numerator(a));
			Release(a);
			return (value)b;
		}
		return (value)a;
	}

	if (Exact(v)) {
		integer vn, vd;
		int s;
		ru = (real) approximate(u);
		if (v == (value) int_2) {
			/* speed up common formula u**2 */
			rw= app_prod(ru, ru);
			Release(ru);
			return (value) rw;
		}
		if (about2_to_integral(ru, v, &rv)) {
			/* to speed up reading the value of an approximate
			 * from a file, the exponent part is stored as
			 * ~2**expo; 
			 * we want to return the value (0.5, expo+1) to 
			 * prevent loss of precision, but the normal way
			 * via app_power() isn't good enough;
			 */
			Release(ru);
			return (value) rv;
		}
		s = (Frac(ru) > 0) - (Frac(ru) < 0);

		if (s < 0) rv = app_neg(ru), Release(ru), ru = rv;
		if (Integral(v)) {
			vn = (integer)v;
			vd = int_1;
		} else {
			vd = Denominator((rational)v);
			if (s < 0 && Even(Lsd(vd)))
				interr(NEG_EVEN);
			vn = Numerator((rational)v);
		}
		if (vn == int_0) {
			Release(ru);
			return one;
		}
		if (s == 0 && Msd(vn) < 0) {
			interr(NEG_POWER);
			return (value) ru;
		}
		if (s < 0 && Even(Lsd(vn)))
			s = 1;
		rv = (real) approximate(v);
		rw = app_power(ru, rv);
		Release(ru), Release(rv);
		if (s < 0) ru = app_neg(rw), Release(rw), rw = ru;
		return (value) rw;
	}

	/* Everything else: we now know u or v is approximate */

	ru = (real) approximate(u);
	if (Frac(ru) < 0) {
		interr(NEG_EXACT);
		return (value) ru;
	}
	rv = (real) approximate(v);
	if (Frac(ru) == 0 && Frac(rv) < 0) {
		interr(NEG_POWER);
		Release(rv);
		return (value) ru;
	}
	rw = app_power(ru, rv);
	Release(ru), Release(rv);
	return (value) rw;
}


/*
 * floor: for approximate numbers app_floor() is used;
 * for integers it is a no-op; other exact numbers effectively calculate
 * u - (u mod 1).
 */

Visible value floor_f(value u) {
	integer quo, rem, v;
	digit div;

	if (Integral(u)) return Copy(u);
	if (Approximate(u)) return (value) app_floor((real)u);

	/* It is a rational number */

	div = int_ldiv(Numerator((rational)u), Denominator((rational)u),
		&quo, &rem);
	if (div < 0 && rem != int_0) { /* Correction for negative noninteger */
		v = int_diff(quo, int_1);
		Release(quo);
		quo = v;
	}
	Release(rem);
	return (value) quo;
}


/*
 * ceiling x is defined as -floor(-x);
 * and that's how it's implemented, except for integers.
 */

Visible value ceil_f(value u) {
	value v;
	if (Integral(u)) return Copy(u);
	u = negated(u);
	v = floor_f(u);
	release(u);
	u = negated(v);
	release(v);
	return u;
}


/*
 * round u is defined as floor(u+0.5), which is what is done here,
 * except for integers which are left unchanged;
 * for rationals the sum u+0.5 isn't normalized; there is no harm in
 * that because of the division in floor_f()
 */

Visible value round1(value u) {
	value v, w; bool neg = No;

	if (Integral(u)) return Copy(u);

	if (numcomp(u, zero) < 0) {
		neg = Yes;
		u = negated(u);
	}
	
	if (Approximate(u)) {
		value wh = approximate((value) rat_half);
		v = (value) app_sum((real) u, (real) wh);
		release(wh);
	}
	else v = (value) ratsumhalf((rational) u);

	w = floor_f(v);
	release(v);
	
	if (neg) {
		release(u);
		w = negated(v=w);
		release(v);
	}

	return w;
}


/*
 * u round v is defined as 10**-u * round(v*10**u).
 * A complication is that u round v is always printed with exactly u digits
 * after the decimal point, even if this involves trailing zeros,
 * or if v is an integer.
 * Consequently, the result is always kept as a rational, even if it can be
 * simplified to an integer, and the size field of the rational number
 * (which is made negative to distinguish it from integers, and < -1 to
 * distinguish it from approximate numbers) is used to store the number of
 * significant digits.
 * Thus a size of -2 means a normal rational number, and a size < -2
 * means a rounded number to be printed with (-2 - length) digits
 * after the decimal point.  This last expression can be retrieved using
 * the macro Roundsize(v) which should only be applied to Rational
 * numbers.
 *
 * prod10n() is a routine with does a fast multiplication with a ten power
 * and does not simplify a rational result sometimes.
 */

Visible value round2(value n, value v) {
	value w;
	int i;

	if (!Integral(n)) {
		interr(MESS(601, "in n round x, n is not an integer"));
		i = 0;
	} else
		i = propintlet(intval(n));

	w = Approximate(v) ? exactly(v) : copy(v);

	v = prod10n(w, i, No);
		/* v will be rounded, so it isn't simplified if a rational */
	release(w);

	v = round1(w = v);
	release(w);

	v = prod10n(w = v, -i, Yes);
	release(w);

	if (i > 0) {	/* Set number of digits to be printed */
		if (propintlet(-2 - i) < -2) {
			if (Rational(v))
				Length(v) = -2 - i;
			else if (Integral(v)) {
				w = v;
				v = mk_exact((integer) w, int_1, i);
				release(w);
			}
		}
	}

	return v;
}


/*
 * sign u inspects the sign of either u, u's numerator or u's fractional part.
 */

Visible value signum(value u) {
	int s;

	if (Exact(u)) {
		if (Rational(u))
			u = (value) Numerator((rational)u);
		s = u==(value)int_0 ? 0 : Msd((integer)u) < 0 ? -1 : 1;
	} else
		s = Frac((real)u) > 0 ? 1 : Frac((real)u) < 0 ? -1 : 0;

	return MkSmallInt(s);
}


/*
 * ~u makes an approximate number of any numerical value.
 */

Visible value approximate(value u) {
	if (Approximate(u))
		return Copy(u);
	else if (IsSmallInt(u))
		return (value) mk_approx((double) SmallIntVal(u), 0.0);
	else
		return app_frexp(u);
}


/*
 * exact(v) returns whether a number isn'y approximate
 */

Visible bool exact(value v) {
	return (bool) Exact(v);
}

/*
 * numerator v returns the numerator of v, whenever v is an exact number.
 * For integers, that is v itself.
 */

Visible value numerator(value v) {
	if (!Exact(v)) {
		interr(MESS(602, "in */n, n is an approximate number"));
		return zero;
	}

	if (Integral(v)) return Copy(v);

	return Copy(Numerator((rational)v));
}


/*
 * The denominator of v, whenever v is an exact number.
 * For integers, that is 1.
 */

Visible value denominator(value v) {
	if (!Exact(v)) {
		interr(MESS(603, "in /*n, n is an approximate number"));
		return zero;
	}

	if (Integral(v)) return one;

	return Copy(Denominator((rational)v));
}


/*
 * u root v is defined as v**(1/u), where u is usually but need not be
 * an integer.
 */

Visible value root2(value u, value v) {
	if (u == (value)int_0 ||
      (Rational(u) && Numerator((rational)u) == int_0) ||
      (Approximate(u) && Frac((real)u) == 0)) {
		interr(MESS(604, "in n root x, n is zero"));
		v = Copy(v);
	} else {
		u = quot((value)int_1, u);
		v = vpower(v, u);
		release(u);
	}

	return v;
}

/* root x is computed more exactly than n root x, by doing
   one iteration step extra.  This ~guarantees root(n**2) = n. */

Visible value root1(value v) {
	value r, v_over_r, theirsum, result;
	if (numcomp(v, zero) < 0) {
		interr(MESS(605, "in root x, x is negative"));
		return Copy(v);
	}
	r = root2((value)int_2, v);
	if (Approximate(r) && Frac((real)r) == 0.0) return (value)r;
	v_over_r = quot(v, r);
	theirsum = sum(r, v_over_r), release(r), release(v_over_r);
	result = quot(theirsum, (value)int_2), release(theirsum);
	return result;
}

/* The rest of the mathematical functions */

Visible value vpi(void) {
	return (value) mk_approx(3.141592653589793238463, 0.0);
}
Visible value e_natural(void) {
	return (value) mk_approx(2.718281828459045235360, 0.0);
}
Hidden real over_two_pi(value v) {
	real two_pi = mk_approx(6.283185307179586476926, 0.0);
	real w = (real) approximate(v);
	real res = app_quot(w, two_pi);
	Release(two_pi); Release(w);
	return res;
}
Hidden value trig(value u, value v, mathfun ffun, bool zeroflag)
{
	real w;
	double expo, frac, x, result;
	
	
	if (u != Vnil) { /* dyadic version */
		real f = over_two_pi(u);
		real rv = (real) approximate(v);
		w = app_quot(rv, f);	/* check on f<>0 (= u<>0) in i3fpr.c */
		Release(f); Release(rv);
	}
	else {
		w = (real) approximate(v);
	}
	expo = Expo(w); frac = Frac(w);
	if (expo <= Minexpo/2) {
		if (zeroflag) return (value) w; /* sin small x = x, etc. */
		frac = 0, expo = 0;
	}
	Release(w);
	if (expo > Maxexpo) errno = EDOM;
	else {
		x = ldexp(frac, (int)expo);
		if (x >= Maxtrig || x <= -Maxtrig) errno = EDOM;
		else {
			errno = 0;
			result = (*ffun)(x);
		}
	}
	if (errno != 0) {
		if (errno == ERANGE)
			interr(MESS(606, "result of math function too large"));
		else if (errno == EDOM)
			interr(MESS(607, "argument to math function too large"));
		else interr(MESS(608, "math library error"));
		return Copy(app_0);
	}
	return (value) mk_approx(result, 0.0);
}

Visible value sin1(value v) { return trig(Vnil, v, sin, Yes); }
Visible value cos1(value v) { return trig(Vnil, v, cos, No); }
Visible value tan1(value v) { return trig(Vnil, v, tan, Yes); }
Visible value sin2(value u, value v) { return trig(u, v, sin, Yes); }
Visible value cos2(value u, value v) { return trig(u, v, cos, No); }
Visible value tan2(value u, value v) { return trig(u, v, tan, Yes); }

Visible value arctan1(value v) {
	real w = (real) approximate(v);
	double expo = Expo(w), frac = Frac(w);
	if (expo <= Minexpo + 2) return (value) w; /* atan of small x = x */
	Release(w);
	if (expo > Maxexpo) expo = Maxexpo;
	return (value) mk_approx(atan(ldexp(frac, (int)expo)), 0.0);
}

Visible value arctan2(value u, value v) {
	real av = (real) arctan1(v);
	real f = over_two_pi(u);
	real r = app_prod(av, f);
	Release(av); Release(f);
	return (value) r;
}

Hidden double atn2(double x, double y) {
	if (x == 0.0 && y == 0.0)
		return 0.0;
	else
		return atan2(x, y);
}

Visible value angle1(value u, value v) {
	real ru = (real) approximate(u), rv = (real) approximate(v);
	double uexpo = Expo(ru), ufrac = Frac(ru);
	double vexpo = Expo(rv), vfrac = Frac(rv);
	Release(ru), Release(rv);
	if (uexpo > Maxexpo) uexpo = Maxexpo;
	if (vexpo > Maxexpo) vexpo = Maxexpo;
	return (value) mk_approx(
		atn2(
			vexpo < Minexpo ? 0.0 : ldexp(vfrac, (int)vexpo),
			uexpo < Minexpo ? 0.0 : ldexp(ufrac, (int)uexpo)),
		0.0);
}

Visible value angle2(value c, value u, value v) {
	real av = (real) angle1(u, v);
	real f = over_two_pi(c);
	real r = app_prod(av, f);
	Release(av); Release(f);
	return (value) r;
}

Visible value radius(value u, value v) {
	real x = (real) approximate(u);
	real y = (real) approximate(v);
	real x2 = app_prod(x, x);
	real y2 = app_prod(y, y);
	real x2y2 = app_sum(x2, y2);
	value rad = root1((value) x2y2);
	Release(x); Release(y);
	Release(x2); Release(y2); Release(x2y2);
	return rad;
}

Visible value vexp1(value v) {
	real w = (real) approximate(v);
	real x = app_exp(w);
	Release(w);
	return (value) x;
}

Visible value vlog1(value v) {
	real w, x;
	if (numcomp(v, zero) <= 0) {
		interr(MESS(609, "in log x, x <= 0"));
		return copy(zero);
	}
	w = (real) approximate(v);
	x = app_log(w);
	Release(w);
	return (value) x;
}

Visible value vlog2(value u, value v) {
	value w;
	if (numcomp(u, zero) <= 0) {
		interr(MESS(610, "in b log x, b <= 0"));
		return copy(zero);
	}
	if (numcomp(v, zero) <= 0) {
		interr(MESS(611, "in b log x, x <= 0"));
		return copy(zero);
	}
	u = vlog1(u);
	v = vlog1(v);
	w = quot(v, u);
	release(u), release(v);
	return w;
}

/* exactly() converts a approximate number to an exact number */

Visible value exactly(value v) {
	if (exact(v))
		return Copy(v);
	else
		return app_exactly((real) v);
}
