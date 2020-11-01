/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef ETEX_h_e5648d1a30f5fd6c9fb38384801b6918
#define ETEX_h_e5648d1a30f5fd6c9fb38384801b6918

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

extern int e_length(value v);
extern value mk_etext(string m);
extern char e_ncharval(int n, value v);
extern string e_strval(value v);
extern string e_sstrval(value v);
/* extern Procedure e_fstrval(); */
extern value e_icurtail(value v, int k);
extern value e_ibehead(value v, int k);
extern value e_concat(value s, value t);
/* extern Procedure e_concto(); */

#ifdef __cplusplus
}
#endif


#endif
