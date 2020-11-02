/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* B formula/predicate invocation */
#include "i3sou.h"
#include "b.h"
#include "bint.h"
#include "bobj.h"
#include "i0err.h"
#include "b0lan.h"
#include "i1nui.h"
#include "i1num.h"
#include "i2par.h"
#include "i3cen.h"
#include "i3err.h"
#include "i3sou.h"
#include "port.h"

Forward Hidden Procedure defprd(string repr, literal adic, intlet pre);

#define Other 0
#define Nume 1		/* e.g. number1 + number2 */
#define Adjust 5	/* e.g. v >< number2 */
#define Numpair 2	/* e.g. angle(x,y) has numeric pair */
#define Nonzero 3	/* e.g. 0 sin x undefined */
#define Textual 4	/* e.g. stripped t */

#define Xact 0
#define In 1
#define Not_in 2

/*
 * Table defining all predefined functions (but not propositions).
 */

struct funtab {
	string f_name; literal f_adic, f_kind;
	value	(*f_fun)();
	char /* bool */ f_extended;
} funtab[] = {
	{S_ABOUT,	Mfd, Nume, approximate},
	{S_PLUS,	Mfd, Nume, copy},
	{S_PLUS,	Dfd, Nume, sum},
	{S_MINUS,	Mfd, Nume, negated},
	{S_MINUS,	Dfd, Nume, diff},
	{S_NUMERATOR,	Mfd, Nume, numerator},
	{S_DENOMINATOR,	Mfd, Nume, denominator},

	{S_TIMES,	Dfd, Nume, prod},
	{S_OVER,	Dfd, Nume, quot},
	{S_POWER,	Dfd, Nume, vpower},

	{S_BEHEAD,	Dfd, Other, behead},
	{S_CURTAIL,	Dfd, Other, curtail},
	{S_JOIN,	Dfd, Other, concat},
	{S_REPEAT,	Dfd, Other, repeat},
	{S_LEFT_ADJUST,	Dfd, Adjust, adjleft},
	{S_CENTER,	Dfd, Adjust, centre},
	{S_RIGHT_ADJUST, Dfd, Adjust, adjright},

	{S_NUMBER,	Mfd, Other, size},
	{S_NUMBER,	Dfd, Other, size2},

	{F_pi,		Zfd, Other, vpi},
	{F_e,		Zfd, Other, e_natural},
	{F_now,		Zfd, Other, nowisthetime},
	
	{F_abs,    	Mfd, Nume, absval},
	{F_sign,   	Mfd, Nume, signum},
	{F_floor,  	Mfd, Nume, floor_f},
	{F_ceiling,	Mfd, Nume, ceil_f},
	{F_round,  	Mfd, Nume, round1},
	{F_round,  	Dfd, Nume, round2},
	{F_mod,    	Dfd, Nume, vmod},
	{F_root,   	Mfd, Nume, root1},
	{F_root,   	Dfd, Nume, root2},
	{F_random, 	Zfd, Nume, vrandom},
	
	{F_exactly,	Mfd, Nume, exactly},

	{F_sin,		Mfd, Nume, sin1},
	{F_cos, 	Mfd, Nume, cos1},
	{F_tan,		Mfd, Nume, tan1},
	{F_arctan,	Mfd, Nume, arctan1},
	{F_angle,	Mfd, Numpair, angle1},
	{F_radius,	Mfd, Numpair, radius},

	{F_sin,		Dfd, Nonzero, sin2},
	{F_cos, 	Dfd, Nonzero, cos2},
	{F_tan, 	Dfd, Nonzero, tan2},
	{F_arctan,	Dfd, Nume, arctan2},
	{F_angle,	Dfd, Numpair, angle2},
	
	{F_exp,		Mfd, Nume, vexp1},
	{F_log,		Mfd, Nume, vlog1},
	{F_log,		Dfd, Nume, vlog2},

	{F_stripped,	Mfd, Textual, stripped},
	{F_split,	Mfd, Textual, split},
	{F_upper,	Mfd, Textual, upper},
	{F_lower,	Mfd, Textual, lower},

	{F_keys,	Mfd, Other, keys},
#ifdef B_COMPAT
	{F_thof, 	Dfd, Other, th_of},
#endif
	{F_item, 	Dfd, Other, item},
	{F_min,  	Mfd, Other, min1},
	{F_min,  	Dfd, Other, min2},
	{F_max,  	Mfd, Other, max1},
	{F_max,  	Dfd, Other, max2},
	{F_choice, 	Mfd, Other, choice},
	{"",		 Dfd, Other, NULL} /*sentinel*/
};

Visible Procedure initfpr(void)
{
	struct funtab *fp; value r, f, pname;

	initstdenv();
	for (fp= funtab; *(fp->f_name) != '\0'; ++fp) {
		/* Define function */
		r= mk_text(fp->f_name);
		f= mk_fun(fp->f_adic, (intlet) (fp-funtab), NilTree, Yes);
		pname= permkey(r, fp->f_adic);
		def_std_howto(pname, f);
		release(f); release(r); release(pname);
	}

	defprd(P_exact, Mpd, Xact);
	defprd(P_in, Dpd, In);
	defprd(P_notin, Dpd, Not_in);
}

Hidden Procedure defprd(string repr, literal adic, intlet pre)
{
	value r= mk_text(repr), p= mk_prd(adic, pre, NilTree, Yes), pname;
	pname= permkey(r, adic);
	def_std_howto(pname, p);
	release(p); release(r); release(pname);
}

Visible Procedure endfpr(void)
{
	endstdenv();
}

Hidden bool is_funprd(value t, value *f, literal adicity, bool func)
{
	value *aa;
	bool rethow = (f != Pnil); /* get internal repr. howto */

	if (rethow)
		*f = Vnil;
	if (!Valid(t) || !Is_text(t))
		return No;
	if (!is_unit(t, adicity, rethow ? &aa : PPnil, Wnil))
		return No;
	if (still_ok) {
		if (!rethow)
			return Yes;
		if (func) {
			if (!Is_function(*aa))
				return No;
		}
		else {
			if (!Is_predicate(*aa))
				return No;
		}
		*f = *aa;
		return Yes;
	}
	else return No;
}

Visible bool is_zerfun(value t, value *f) {
	return is_funprd(t, f, Zfd, Yes);
}

Visible bool is_monfun(value t, value *f) {
	return is_funprd(t, f, Mfd, Yes);
}

Visible bool is_dyafun(value t, value *f) {
	return is_funprd(t, f, Dfd, Yes);
}

Visible bool is_zerprd(value t, value *p) {
	return is_funprd(t, p, Zpd, No);
}

Visible bool is_monprd(value t, value *p) {
	return is_funprd(t, p, Mpd, No);
}

Visible bool is_dyaprd(value t, value *p) {
	return is_funprd(t, p, Dpd, No);
}

#define Is_numpair(v) (Is_compound(v) && Nfields(v) == 2 && \
			Is_number(*Field(v, 0)) && Is_number(*Field(v, 1)))

Visible value pre_fun(value nd1, intlet pre, value nd2) {
	struct funtab *fp= &funtab[pre];
	literal adic= fp->f_adic, kind= fp->f_kind;
	value name= mk_text(fp->f_name);
	switch (adic) {
	case Dfd:
		if ((kind==Nume||kind==Numpair||kind==Nonzero) && !Is_number(nd1)) {
	interrV(MESS(3200, "in x %s y, x is not a number"), name);
			release(name);
			return Vnil;
		}
		else if ((kind==Nume||kind==Nonzero||kind==Adjust)
			 && !Is_number(nd2)) {
	interrV(MESS(3201, "in x %s y, y is not a number"), name);
			release(name);
			return Vnil;
		}
		else if (kind==Numpair && !Is_numpair(nd2)) {
	interrV(MESS(3202, "in x %s y, y is not a compound of two numbers"), name);
			release(name);
			return Vnil;
		} else if (kind==Nonzero && numcomp(nd1, zero)==0) {
	interrV(MESS(3203,"in c %s x, c is zero"), name);
			release(name);
			return Vnil;
		}
		break;
	case Mfd:
		switch (kind) {
		case Nume:
			if (!Is_number(nd2)) {
	interrV(MESS(3204, "in %s x, x is not a number"), name);
				release(name);
				return Vnil;
			}
			break;
		case Numpair:
			if (!Is_numpair(nd2)) {
	interrV(MESS(3205, "in %s y, y is not a compound of two numbers"), name);
				release(name);
				return Vnil;
			}
			break;
		case Textual:
			if (!Is_text(nd2)) {
	interrV(MESS(3206, "in %s t, t is not a text"), name);
				release(name);
				return Vnil;
			}
			break;
		}
		break;
	}
	release(name);
	
	switch (adic) {
	case Zfd: return((*fp->f_fun)());
	case Mfd:
		if (fp->f_kind == Numpair)
			return((*fp->f_fun)(*Field(nd2,0), *Field(nd2,1)));
		else
			return((*fp->f_fun)(nd2));
	case Dfd:
		if (fp->f_kind == Numpair)
			return((*fp->f_fun)(nd1, *Field(nd2,0), *Field(nd2,1)));
		else
			return((*fp->f_fun)(nd1, nd2));
	default: syserr(MESS(3207, "pre-defined fpr wrong"));
		 return Vnil;
		 /*NOTREACHED*/
	}
}

Visible bool pre_prop(value nd1, intlet pre, value nd2) {
	switch (pre) {
	case Xact:
		if (!Is_number(nd2)) {
		interr(MESS(3208, "in the test exact x, x is not a number"));
			return No;
		}
		return exact(nd2);
	case In:
		if (!Is_tlt(nd2)) {
interr(MESS(3209, "in the test e in t, t is not a text list or table"));
			return No;
		}
		if (Is_text(nd2) && (!character(nd1))) {
			interr(
MESS(3210, "in the test e in t, t is a text, but e is not a character")
			);
			return No;
		}
		return in(nd1, nd2);
	case Not_in:
		if (!Is_tlt(nd2)) {
			interr(
MESS(3211, "in the test e not.in t, t is not a text list or table"));
			return No;
		}
		if (Is_text(nd2) && (!character(nd1))) {
			interr(
MESS(3212, "in the test e not.in t, t is a text, but e isn't a character")
			);
			return No;
		}
		return !in(nd1, nd2);
	default:
		syserr(MESS(3213, "predicate not covered by proposition"));
		return No;
		/*NOTREACHED*/
	}
}

Visible value nowisthetime(void)
{
	value now;
	int year, month, day;
	int hour, minute, sec;
	long fraction, units;

	getdatetime(&year, &month, &day, &hour, &minute,
		    &sec, &fraction, &units);

	now = mk_compound(6);
	*Field(now, 0) = mk_integer(year);
	*Field(now, 1) = mk_integer(month);
	*Field(now, 2) = mk_integer(day);
	*Field(now, 3) = mk_integer(hour);
	*Field(now, 4) = mk_integer(minute);

	if (units == 0) {
		*Field(now, 5) = mk_integer(sec);
	}
	else {
		value v_sec =        mk_integer(sec);
		integer v_fraction = mk_int((double) fraction);
		integer v_units =    mk_int((double) units);
		value v =            mk_exact(v_fraction, v_units, 0);

		*Field(now, 5) =     sum(v_sec, v);
		release(v_sec);
		release((value) v_fraction);
		release((value) v_units);
		release(v);
	}
	return now;
}
