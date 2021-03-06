/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* Type matching */
#include "i3typ.h"

#include "b.h"
#include "bint.h"
#include "bobj.h"
#include "i3env.h"
#include "i3err.h"
#include "i3typ.h"
#include "b1grab.h"

#define Tnil ((btype) Vnil)

/* All the routines in this file are temporary */
/* Thus length() has been put here too */

Visible int length(value v) {
	value s= size(v);
	int len= intval(s);
	release(s);
	return len;
}

Visible btype loctype(loc l) {
	value *ll;
	if (Is_simploc(l)) {
		simploc *sl= Simploc(l);
		if (!in_env(sl->e->tab, sl->i, &ll)) return Tnil;
		return valtype(*ll);
	} else if (Is_tbseloc(l)) {
		tbseloc *tl= Tbseloc(l);
		btype tt= loctype(tl->R), ass;
		if (tt == Tnil) return Tnil;
		if (!empty(tt)) ass= item(tt, one);
		else ass= Tnil;
		release(tt);
		return ass;
	} else if (Is_trimloc(l)) {
		return mk_text("");
	} else if (Is_compound(l)) {
		btype ct= mk_compound(Nfields(l)); intlet k, len= Nfields(l);
		k_Overfields { *Field(ct, k)= loctype(*Field(l, k)); }
		return ct;
	} else {
		syserr(MESS(4200, "loctype asked of non-location"));
		return Tnil;
	}
}

Visible btype valtype(value v) {
	if (Is_number(v)) return mk_integer(0);
	else if (Is_text(v)) return mk_text("");
	else if (Is_compound(v)) {
		btype ct= mk_compound(Nfields(v)); intlet k, len= Nfields(v);
		k_Overfields { *Field(ct, k)= valtype(*Field(v, k)); }
		return ct;
	} else if (Is_ELT(v)) {
		return mk_elt();
	} else if (Is_list(v)) {
		btype tt= mk_elt(), vt, ve;
		if (!empty(v)) {
			insert(vt= valtype(ve= min1(v)), &tt);
			release(vt); release(ve);
		}
		return tt;
	} else if (Is_table(v)) {
		btype tt= mk_elt(), vk, va;
		if (!empty(v)) {
			vk= valtype(*key(v, 0));
			va= valtype(*assoc(v, 0));
			replace(va, &tt, vk);
			release(vk); release(va);
		}
		return tt;
	} else {
		syserr(MESS(4201, "valtype called with unknown type"));
		return Tnil;
	}
}

Visible Procedure must_agree(btype t, btype u, int m) {
	intlet k, len;
	value vt, vu;
	if (t == Tnil || u == Tnil || t == u) return;
	if (Is_number(t) && Is_number(u)) return;
	if (Is_text(t) && Is_text(u)) return;
	if (Is_ELT(u) && (Is_ELT(t) || Is_list(t) || Is_table(t))) return;
	if (Is_ELT(t) && (             Is_list(u) || Is_table(u))) return;
	if (Is_compound(t) && Is_compound(u)) {
		if ((len= Nfields(t)) != Nfields(u)) interr(m);
		else k_Overfields { must_agree(*Field(t,k), *Field(u,k), m); }
	} else {
		if (Is_list(t) && Is_list(u)) {
			if (!empty(t) && !empty(u)) {
				must_agree(vt= min1(t), vu= min1(u), m);
				release(vt); release(vu);
			}
		} else if (Is_table(t) && Is_table(u)) {
			if (!empty(t) && !empty(u)) {
				must_agree(*key(t, 0), *key(u, 0), m);
				must_agree(*assoc(t, 0), *assoc(u, 0), m);
			}
		} else interr(m);
	}
}
