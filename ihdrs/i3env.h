/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3ENV_h_02cf7d0750a6067fa65376d1ea4bb742
#define I3ENV_h_02cf7d0750a6067fa65376d1ea4bb742

#include "b.h"
#include "bint.h"


#ifdef __cplusplus
extern "C" {
#endif

/* environments and context */

	typedef struct {
			value howtoname;
			env curnv;
			value r_names, *bndtgs;
			literal cntxt, resexp;
			parsetree cur_line;
			value cur_lino;
	} context;

#define Enil ((env) NULL)

/* contexts: */
#define In_command 'c'
#define In_read '?'
#define In_unit 'u'
#define In_edval 'e'
#define In_tarval 't'
#define In_prmnv 'p'
#define In_wsgroup 'w'

/* results */
#define Ret 'V'
#define Rep '+'
#define Voi ' '

	extern value* envassoc(value, value);

	extern env curnv; extern value *bndtgs;
	extern literal cntxt, resexp; extern value howtoname;
	extern value errtname;
	extern intlet lino;
	extern intlet f_lino;
	extern intlet i_lino;

	extern context read_context;

	extern envtab prmnvtab;
	extern envchain prmnvchain;
	extern env prmnv;

	extern parsetree curline;
	extern value curlino;

	extern Visible bool in_env(value tab, value ke, value **aa);
	extern Visible Procedure sethowtoname(value v);
	extern Visible Procedure e_replace(value v, value* t, value k);
	extern Visible Procedure e_delete(value *t, value k);

#ifdef __cplusplus
}
#endif


#endif
