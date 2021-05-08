/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */
#include "e1etex.h"

#include "b.h"
#include "bedi.h"
#include "bobj.h"
#include "etex.h"
#include "b1memo.h"
#include "bmem.h"
#include "b1grab.h"

Visible int e_length(value v) {
	return Length(v);
}

Visible value mk_etext(cstring m) {
	value v; intlet len= strlen(m);
	v= grab(Etex, len);
	strcpy(StrPtrField(v), m);
	return v;
}

Visible char e_ncharval(int n, value v) {
	return *(StrPtrField(v)+n-1);
}

Visible string e_strval(value v) {
	return StrPtrField(v);
}


Visible string e_sstrval(value v) {
	return (string) savestr(StrPtrField(v));
}

Visible Procedure e_fstrval(string s) {
	freestr(s);
}


Visible value e_icurtail(value v, int k) {
	value w= grab(Etex, k);
	strncpy(StrPtrField(w), StrPtrField(v), k);
	*(StrPtrField(w) + k)= '\0';
	return w;
}


Visible value e_ibehead(value v, int k) {
	value w= grab(Etex, Length(v) - (k - 1));
	strcpy(StrPtrField(w), StrPtrField(v) + k - 1);
	return w;
}



Visible value e_concat(value s, value t) {
	value v= grab(Etex, Length(s) + Length(t));
	strcpy(StrPtrField(v), StrPtrField(s));
	strcpy(StrPtrField(v) + Length(s), StrPtrField(t));
	return v;
}

Visible Procedure e_concto(value *s, value t) {
	value v= *s;
	*s= e_concat(*s, t);
	release(v);
}
