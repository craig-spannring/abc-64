/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* Environments */

#include "b.h"
#include "b1outp.h"
#include "bint.h"
#include "bobj.h"
#include "i1lta.h"
#include "i3err.h"
#include "i3env.h" 	/* for curline, curlino  */
#include "b1grab.h"

Visible envtab prmnvtab;
Visible envchain prmnvchain;
Visible env prmnv;

/* context: */
/* The bound tags for the current environment are stored in *bndtgs */
/* A new bound tag list is created on evaluating a refined test or expression */

Visible env curnv;
Visible value *bndtgs;
Hidden value bndtglist;
Visible literal cntxt, resexp;
Visible value howtoname= Vnil;
Visible intlet lino;
Visible intlet f_lino;
Visible intlet i_lino;

Visible context read_context;

Visible Procedure sv_context(context *sc) {
	sc->curnv= curnv;
	sc->bndtgs= bndtgs;
	sc->cntxt= cntxt;
	sc->resexp= resexp;
	sc->howtoname= copy(howtoname);
	sc->cur_line= curline;
	sc->cur_lino= curlino;
}

Visible Procedure set_context(context *sc) {
	curnv= sc->curnv;
	bndtgs= sc->bndtgs;
	cntxt= sc->cntxt;
	resexp= sc->resexp;
	sethowtoname(sc->howtoname);
	curline= sc->cur_line;
	curlino= sc->cur_lino;
}

Visible Procedure sethowtoname(value v)
{
	release(howtoname);
	howtoname = v;
}

Visible Procedure initprmnv(void)
{
	prmnv= &prmnvchain;
	prmnv->tab= Vnil;
	prmnv->inv_env= Enil;
}

Visible Procedure initenv(void) {
	/* The following invariant must be maintained:
	   EITHER:
	      the original permanent-environment table resides in prmnv->tab
	      and prmnvtab == Vnil
	   OR:
	      the original permanent-environment table resides in prmnvtab
	      and prmnv->tab contains a scratch-pad copy.
	*/
	prmnv->tab= mk_elt(); prmnvtab= Vnil;
	prmnv->inv_env= Enil;
	bndtglist= mk_elt();
}

Visible Procedure endenv(void) {
	release(prmnv->tab); prmnv->tab= Vnil;
	release(bndtglist); bndtglist= Vnil;
	sethowtoname(Vnil);
}

Visible Procedure re_env(void) {
	setprmnv(); bndtgs= &bndtglist;
}

Visible Procedure setprmnv(void) {
	/* the current and permanent environment are reset
	   to the original permanent environment */
	if (prmnvtab != Vnil) {
		prmnv->tab= prmnvtab;
		prmnvtab= Vnil;
	}
	curnv= prmnv;
}

Visible Procedure e_replace(value v, value* t, value k) {
	if (Is_compound(*t)) {
		int n= SmallIntVal(k);
		uniql(t);
		if (*Field(*t, n) != Vnil) release(*Field(*t, n));
		*Field(*t, n)= copy(v);
	}
	else if (!Is_table(*t)) syserr(MESS(3000, "replacing in non-environment"));
	else replace(v, t, k);
}

Visible Procedure e_delete(value *t, value k) {
	if (Is_compound(*t) && IsSmallInt(k)) {
		int n= SmallIntVal(k);
		if (*Field(*t, n) != Vnil) {
			uniql(t); release(*Field(*t, n));
			*Field(*t, n)= Vnil;
		}
	}
	else if (!Is_table(*t)) syserr(MESS(3001, "deleting from non-environment"));
	else if (in_keys(k, *t)) deleteitem(t, k);
}

Visible value* envassoc(value t, value ke) {
	if (Is_compound(t) && IsSmallInt(ke)) {
		int n= SmallIntVal(ke);
		if (*Field(t, n) == Vnil) return Pnil;
		return Field(t, n);
	}
	if (!Is_table(t)) syserr(MESS(3002, "selection on non-environment"));
	return adrassoc(t, ke);
}

Visible bool in_env(value tab, value ke, value **aa) {
	/* IF ke in keys tab:
		PUT tab[ke] IN aa
		SUCCEED
	   FAIL
	*/
	*aa= envassoc(tab, ke);
	return (*aa != Pnil);
}

Visible Procedure extbnd_tags(value btl, envtab et) {
	/* Copy bound targets to the invoking environment */
	/* FOR tag IN btl: \ btl is the bound tag list
	       IF tag in keys et: \ et is the environment we're just leaving
	           PUT et[tag] IN curnv[tag] \ curnv is the invoking environment
	*/
	value *aa, tag;
	int len= length(btl), k;
	for (k= 1; k <= len; k++) {
		tag= thof(k, btl);
		if (in_env(et, tag, &aa)) {
			e_replace(*aa, &(curnv->tab), tag);
			if (*bndtgs != Vnil) insert(tag, bndtgs);
		}
		release(tag);
	}
}

Visible Procedure lst_ttgs(void) {
	int k, len;
	value v;

	len= length(prmnv->tab);
	for (k= 0; k < len; k++) {
		v= *key(prmnv->tab, k);
		if (Valid(v) && Is_text(v)) {
			c_putstr(strval(v));
			c_putstr(" ");
		}
	}
	if (len > 0)
		c_putnewline();
}
