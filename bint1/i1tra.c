/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1987. */

/* Functions defined on train values. */

/* This file should go into a train directory, that should receive the
 * lin-btr independent part of these modules (especially tlt.c and
 * obj.c contain common parts).
 */

#include "i1tra.h"

#include "b.h"
#include "bobj.h"
#include "i0err.h"
#include "i1num.h"
#include "i3err.h"

#define CHOICE_TLT	MESS(1600, "in choice t, t is not a text list or table")
#define CHOICE_EMPTY	MESS(1601, "in choice t, t is empty")

/* make a B text out of a C char */

Visible value mkchar(char c) {
	char buf[2];
	buf[0] = c;
	buf[1] = '\0';
	return mk_text(buf);
}

/* report: t item j ?=? ' ' */
Hidden bool is_space(value t, value i) {
	value ti;
	char c;
	
	ti = item(t, i);
	c = charval(ti);
	release(ti);
	return c == ' ';
}

Hidden Procedure incr(value *pn) {
	value n1;
	
	n1 = sum(*pn, one);
	release(*pn);
	*pn = n1;
}

Visible value stripped(value t) {
	value a, b, i, j, k;
	
	i = one;
	j = size(t);
	while (numcomp(i, j) <= 0 && is_space(t, i)) {
		incr(&i);
	}
	while (numcomp(j, i) > 0 && is_space(t, j)) {
		k = diff(j, one);
		release(j);
		j = k;
	}
	if (numcomp(i, j) <= 0) {
		a = behead(t, i);
		k = diff(j, i);
		incr(&k);
		b = curtail(a, k);
		release(k); release(a);
	}
	else {
		b = mk_text("");
	}
	release(i); release(j);
	return b;
}

Visible value split(value t) {
	value a, b, i, j, ij, r, ri, sizt;
	
	r = mk_elt();
	ri = one;
	i = one;
	sizt = size(t);
	while (numcomp(i, sizt) <= 0) {
		while (numcomp(i, sizt) <= 0 && is_space(t, i)) {
			incr(&i);
		}
		if (numcomp(i, sizt) > 0) {
			break;
		}
		j = one;
		ij = sum(i, j);
		while (numcomp(ij, sizt) <= 0 && !is_space(t, ij)) {
			incr(&j);
			incr(&ij);
		}
		a = behead(t, i);
		b = curtail(a, j);
		replace(b, &r, ri);
		incr(&ri);
		release(i); i = ij; /* PUT i+j IN i */
		release(j); release(a); release(b);
	}
	release(i); release(sizt);
	return r;
}

Hidden value uplower(value t, int (*islowupper) (char), int (*touplower) (/* ??? */))
{
	value i, sizt, r, ti, c;
	char s[2];
	
	s[1] = '\0';
	r = mk_text("");
	i = one;
	sizt = size(t);
	while (numcomp(i, sizt) <= 0) {
		ti = item(t, i);
		s[0] = charval(ti);
		if ((*islowupper)(s[0])) {
			release(ti);
			s[0] = (*touplower)(s[0]);
			ti = mk_text(s);
		}
		c = concat(r, ti);
		release(r); release(ti);
		r = c;
		incr(&i);
	}
	release(i); release(sizt);
	return r;
}

/* terrible BSD patch: turn macroos into Functions */
#ifdef isupper
int F_isupper(char c) { return isupper(c); }
#else
#define F_isupper isupper
extern int isupper();
#endif
#ifdef islower
int F_islower(char c) { return islower(c); }
#else
#define F_islower islower
extern int islower();
#endif
#ifdef toupper
int F_toupper(c) char c; { return toupper(c); }
#else
#define F_toupper toupper
extern int toupper(int);
#endif
#ifdef tolower
int F_tolower(c) char c; { return tolower(c); }
#else
#define F_tolower tolower
extern int tolower(int);
#endif

Visible value upper(value t) { return uplower(t, F_islower, F_toupper);}
Visible value lower(value t) { return uplower(t, F_isupper, F_tolower);}

/* for RangeElem's */

Hidden Procedure insCrange(value lwb, value upb, value *pl) {
	value w; char lwbchar= charval(lwb), upbchar= charval(upb);
	if (lwbchar > upbchar) return;
	uniql(pl);
	do {
		w= mkchar(lwbchar);
		insert(w, pl);
		release(w);
	} while (++lwbchar <= upbchar);
}

Hidden Procedure insIrange(value lwb, value upb, value *pl) {
	value w= copy(lwb);
	uniql(pl);
	do {
		if (compare(lwb, upb) > 0) break;
		insert(lwb, pl);
		w= lwb;
		lwb= sum(lwb, one);
		release(w);
	} while (still_ok);
	release(lwb);
}

Visible Procedure ins_range(value lwb, value upb, value *pl) {
	if (Is_text(lwb))
		insCrange(lwb, upb, pl);
	else 
		insIrange(lwb, upb, pl);
}

/* choice = train item (random * (1+floor(#train))), is tricky:
 * random() only contains a limited number of bits.
 * For very large trains, certain items would therefore never be chosen
 * when the standard definition above is used.
 * Therefore, if #train is greater than a safe rndm_limit below which
 * all bits in a number are random, we divide #train over rndm_limit
 * sized chunks, and choose among one of these chunks. The last chunk
 * may contain less than rndm_limit elements, each of which gets the same
 * chance to be choosen as the elements in any other chunk. Hence the
 * while in choice() below.
 */

extern value rndm_limit;
	/* below this limit each number has a fair chance */

Hidden value numchoice(value m) {
	value p;
	value q;
	value r;
	value chunk;
	
	/* choose a number between 1 and limit*ceiling(m/limit) */
	if (numcomp(m, rndm_limit) <= 0) {
		/* standard def: 1 + floor(random*m) */
		r= vrandom();
		p= prod(r, m);
		release(r);
		r= floor_f(p);
		incr(&r);
		release(p);
	}
	else {
		/* choose chunk= choice{0..ceiling(m/limit)-1}
		 * and return element r= limit*chunk + choice{1..limit}
		 */
		q= quot(m, rndm_limit);
		p= ceil_f(q);
		release(q);
		q= numchoice(p);
		release(p);
		chunk= diff(q, one);
		release(q);
		p= prod(rndm_limit, chunk);
		q= numchoice(rndm_limit);
		r= sum(p, q);
		release(p); release(q); release(chunk);
	}
	return r;
}

Visible value choice(value train) {
	value nn;
	value n;
	
	nn= Vnil;
	if (!Is_tlt(train)) interr(CHOICE_TLT);
	else if (empty(train)) interr(CHOICE_EMPTY);
	else {
		nn= size(train);
		n= numchoice(nn);
		while (numcomp(n, nn) > 0) {
			/* in non-existing part of upper chunk */
			release(n);
			n= numchoice(nn);
		}
		release(nn);
		nn= item(train, n);
		release(n);
	}
	return nn;
}
