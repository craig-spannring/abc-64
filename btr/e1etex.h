/**
 * @file
 * 
 */    
#ifndef E1ETEX_h_d906fe518ef0b9745cef87dfe31a37b9
#define E1ETEX_h_d906fe518ef0b9745cef87dfe31a37b9

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	Visible value e_concat(value s, value t);
	Visible int e_length(value v);
	Visible value mk_etext(cstring m);
	Visible char e_ncharval(int n, value v);
	Visible string e_strval(value v);
	Visible string e_sstrval(value v);
	Visible Procedure e_fstrval(string s);
	Visible value e_icurtail(value v, int k);
	Visible value e_ibehead(value v, int k);
	Visible value e_concat(value s, value t);
	Visible Procedure e_concto(value *s, value t);


#ifdef __cplusplus
}
#endif




#endif
