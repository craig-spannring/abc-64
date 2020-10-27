/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3ENV_h_02cf7d0750a6067fa65376d1ea4bb742
#define I3ENV_h_02cf7d0750a6067fa65376d1ea4bb742

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

value* envassoc();

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


#ifdef __cplusplus
}
#endif


#endif
