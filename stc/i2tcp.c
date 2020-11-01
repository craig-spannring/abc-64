/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* polytype representation */

#include "i2tcp.h"

#include "b.h"
#include "bobj.h"
#include "i2stc.h"
#include "b1grab.h"

/* A polytype is a compound with two fields.
 * The first field is a B text, and holds the typekind.
 * If the typekind is 'Variable', the second field is 
 *   a B text, holding the identifier of the variable;
 * otherwise, the second field is a compound of sub(poly)types,
 *   indexed from 0 to one less then the number of subtypes.
 */

#define Kin	0
#define Sub	1
#define Id	Sub
#define Asc	0
#define Key	1

#define Kind(u)		((typekind) *Field((value) (u), Kin))
#define Psubtypes(u)	(Field((value) (u), Sub))
#define Ident(u)	(*Field((value) (u), Id))

typekind var_kind;
typekind num_kind;
typekind tex_kind;
typekind lis_kind;
typekind tab_kind;
typekind com_kind;
typekind t_n_kind;
typekind l_t_kind;
typekind tlt_kind;
typekind err_kind;
typekind ext_kind;

polytype num_type;
polytype tex_type;
polytype err_type;
polytype t_n_type;

/* Making, setting and accessing (the fields of) polytypes */

Visible polytype mkt_polytype(typekind k, intlet nsub) {
	value u;
	
	u = mk_compound(2);
	*Field(u, Kin)= copy((value) k);
	*Field(u, Sub)= mk_compound(nsub);
	return (polytype) u;
}

Visible Procedure putsubtype(polytype sub, polytype u, intlet isub) {
	*Field(*Psubtypes(u), isub)= (value) sub;
}

typekind kind(polytype u) {
	return Kind(u);
}

intlet nsubtypes(polytype u) {
	return Nfields(*Psubtypes(u));
}

polytype subtype(polytype u, intlet i) {
	return (polytype) *Field(*Psubtypes(u), i);
}

polytype asctype(polytype u) {
	return subtype(u, Asc);
}

polytype keytype(polytype u) {
	return subtype(u, Key);
}

value ident(polytype u) {
	return Ident(u);
}

/* making new polytypes */

polytype mkt_number(void) {
	return p_copy(num_type);
}

polytype mkt_text(void) {
	return p_copy(tex_type);
}

polytype mkt_tn(void) {
	return p_copy(t_n_type);
}

polytype mkt_error(void) {
	return p_copy(err_type);
}

polytype mkt_list(polytype s) {
	polytype u;
	
	u = mkt_polytype(lis_kind, 1);
	putsubtype(s, u, Asc);
	return u;
}

polytype mkt_table(polytype k, polytype a) {
	polytype u;
	
	u = mkt_polytype(tab_kind, 2);
	putsubtype(a, u, Asc);
	putsubtype(k, u, Key);
	return u;
}

polytype mkt_lt(polytype s) {
	polytype u;
	
	u = mkt_polytype(l_t_kind, 1);
	putsubtype(s, u, Asc);
	return u;
}

polytype mkt_tlt(polytype s) {
	polytype u;
	
	u = mkt_polytype(tlt_kind, 1);
	putsubtype(s, u, Asc);
	return u;
}

polytype mkt_compound(intlet nsub) {
	return mkt_polytype(com_kind, nsub);
}

polytype mkt_var(value id) {
	polytype u;
	
	u = mk_compound(2);
	*Field(u, Kin)= copy((value) var_kind);
	*Field(u, Id)= id;
	return u;
}

Hidden value nnewvar;

polytype mkt_newvar(void) {
	value v;
	v = sum(nnewvar, one);
	release(nnewvar);
	nnewvar = v;
	return mkt_var(convert(nnewvar, No, No));
}

Hidden value n_external;  /* external variable types used by how-to's */

Visible Procedure new_externals(void) {
	n_external= zero;
}

Visible polytype mkt_ext(void) {
	polytype u;
	value v;
	
	v = sum(n_external, one);
	release(n_external);
	n_external = v;
	
	u= mk_compound(2);
	*Field(u, Kin)= copy((value) ext_kind);
	*Field(u, Id)= convert(n_external, No, No);
	
	return u;
}

polytype p_copy(polytype u) {
	return (polytype) copy((polytype) u);
}

Visible Procedure p_release(polytype u) {
	release((polytype) u);
}

/* predicates */

bool are_same_types(polytype u, polytype v) {
	if (compare((value) Kind(u), (value) Kind(v)) != 0)
		return No;
	else if (t_is_var(Kind(u)))
		return (compare(Ident(u), Ident(v)) == 0);
	else
		return (
			(nsubtypes(u) == nsubtypes(v))
			&&
			(compare(*Psubtypes(u), *Psubtypes(v)) == 0)
		);
}

bool have_same_structure(polytype u, polytype v) {
	return(
		(compare((value) Kind(u), (value) Kind(v)) == 0)
		&&
		nsubtypes(u) == nsubtypes(v)
	);
}

bool t_is_number(typekind knd) {
	return (compare((value) knd, (value) num_kind) == 0 ? Yes : No);
}

bool t_is_text(typekind knd) {
	return (compare((value) knd, (value) tex_kind) == 0 ? Yes : No);
}

bool t_is_tn(typekind knd) {
	return (compare((value) knd, (value) t_n_kind) == 0 ? Yes : No);
}

bool t_is_error(typekind knd) {
	return (compare((value) knd, (value) err_kind) == 0 ? Yes : No);
}

bool t_is_list(typekind knd) {
	return (compare((value) knd, (value) lis_kind) == 0 ? Yes : No);
}

bool t_is_table(typekind knd) {
	return (compare((value) knd, (value) tab_kind) == 0 ? Yes : No);
}

bool t_is_lt(typekind knd) {
	return (compare((value) knd, (value) l_t_kind) == 0 ? Yes : No);
}

bool t_is_tlt(typekind knd) {
	return (compare((value) knd, (value) tlt_kind) == 0 ? Yes : No);
}

bool t_is_compound(typekind knd) {
	return (compare((value) knd, (value) com_kind) == 0 ? Yes : No);
}

bool t_is_var(typekind knd) {
	return (compare((value) knd, (value) var_kind) == 0 ? Yes : No);
}

bool t_is_ext(typekind knd) {
	return (compare((value) knd, (value) ext_kind) == 0 ? Yes : No);
}

bool has_number(typekind knd) {
	if (compare(knd, num_kind) == 0 || compare(knd, t_n_kind) == 0)
		return Yes;
	else
		return No;
}

bool has_text(typekind knd) {
	if (compare(knd, tex_kind) == 0 || compare(knd, t_n_kind) == 0)
		return Yes;
	else
		return No;
}

bool has_lt(typekind knd) {
	if (compare(knd, l_t_kind) == 0 || compare(knd, tlt_kind) == 0)
		return Yes;
	else
		return No;
}

/* The table "ptype_of" maps the identifiers of the variables (B texts)
 * to polytypes.
 */
 
value ptype_of;

Visible Procedure repl_type_of(polytype u, polytype p) {
	replace((value) p, &ptype_of, Ident(u));
}

bool table_has_type_of(polytype u) {
	return in_keys(Ident(u), ptype_of);
}

#define	Table_type_of(u) ((polytype) *adrassoc(ptype_of, Ident(u)))

Visible polytype bottomtype(polytype u) {
	while (t_is_var(Kind(u)) && table_has_type_of(u)) {
		u = Table_type_of(u);
	}
	return u;
}

polytype bottomvar(polytype u) {
	polytype b;

	if (!t_is_var(Kind(u)))
		return u;
	/* Kind(u) == Variable */
	while (table_has_type_of(u)) {
		b = Table_type_of(u);
		if (t_is_var(Kind(b)))
			u = b;
		else
			break;
	}
	/* Kind(u) == Variable &&
	   !(table_has_type_of(u) && Kind(Table_type_of(u)) == Variable) */
	return u;
}

Visible Procedure usetypetable(value t) {
	ptype_of = t;
}

Visible Procedure deltypetable(void) {
	release(ptype_of);
}

/* init */

Visible Procedure initpol(void) {
	num_kind = mk_text("Number");
	num_type = mkt_polytype(num_kind, 0);
	tex_kind = mk_text("Text");
	tex_type = mkt_polytype(tex_kind, 0);
	t_n_kind = mk_text("TN");
	t_n_type = mkt_polytype(t_n_kind, 0);
	err_kind = mk_text("Error");
	err_type = mkt_polytype(err_kind, 0);
	
	lis_kind = mk_text("List");
	tab_kind = mk_text("Table");
	com_kind = mk_text("Compound");
	l_t_kind = mk_text("LT");
	tlt_kind = mk_text("TLT");
	var_kind = mk_text("Variable");
	ext_kind = mk_text("External");
	
	nnewvar = zero;
}

Visible Procedure endpol(void) {
#ifdef MEMTRACE
	release((value) num_kind);
	release((value) num_type);
	release((value) tex_kind);
	release((value) tex_type);
	release((value) t_n_kind);
	release((value) t_n_type);
	release((value) err_kind);
	release((value) err_type);
	release((value) lis_kind);
	release((value) tab_kind);
	release((value) com_kind);
	release((value) l_t_kind);
	release((value) tlt_kind);
	release((value) var_kind);
#endif
}
