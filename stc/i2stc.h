/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I2STC_h_99befec24fc6975d74e08999fe195f4f
#define I2STC_h_99befec24fc6975d74e08999fe195f4f

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************/

/* polytype representation */

typedef value typekind;
typedef value polytype;

/* accessing, NOT giving new values */

typekind kind(polytype u); 	/* polytype u */
intlet nsubtypes(polytype u); 	/* polytype u */
polytype subtype(polytype u, intlet i); 	/* polytype u, intlet i */
polytype asctype(polytype u); 	/* polytype u */
polytype keytype(polytype u); 	/* polytype u */
value ident(polytype u); 		/* polytype u */

/* MaKe Types, where subtypes are "eaten" */

polytype mkt_polytype(typekind k, intlet nsub); /* typekind k; intlet nsub */
				/* visible only in bunif.c */
/* Procedure putsubtype(); */	/* polytype sub, *pcomp; intlet isub */
				/* to be used after mkt_polytype or
				 * mkt_compound */

polytype mkt_number(void);
polytype mkt_text(void);
polytype mkt_tn(void);
polytype mkt_error(void);
polytype mkt_list(polytype s); 	/* polytype s */
polytype mkt_table(polytype k, polytype a);	/* polytype k, a */
polytype mkt_lt(polytype s); 	/* polytype s */
polytype mkt_tlt(polytype s); 	/* polytype s */
polytype mkt_compound(intlet nsub);	/* intlet nsub */
polytype mkt_var(value id); 	/* value id */
polytype mkt_newvar(void);
polytype mkt_ext(void);

polytype p_copy(polytype u); 	/* polytype u */
/* Procedure p_release(); */		/* polytype u */

/* predicates */

bool are_same_types(polytype u, polytype v); 	/* polytype u, v */
bool have_same_structure(polytype u, polytype v);/* polytype u, v */

bool t_is_number(typekind knd);	/* typekind k */
bool t_is_text(typekind knd);	/* typekind k */
bool t_is_tn(typekind knd);		/* typekind k */
bool t_is_error(typekind knd);	/* typekind k */
bool t_is_list(typekind knd); 	/* typekind k */
bool t_is_table(typekind knd);	/* typekind k */
bool t_is_lt(typekind knd); 	/* typekind k */
bool t_is_tlt(typekind knd);	/* typekind k */
bool t_is_compound(typekind knd);	/* typekind k */
bool t_is_var(typekind knd);	/* typekind k */
bool t_is_ext(typekind knd);	/* typekind k */
bool has_number(typekind knd); 	/* typekind k */
bool has_text(typekind knd); 	/* typekind k */
bool has_lt(typekind knd);	 	/* typekind k */

/* typetable */

/* Procedure repl_type_of(); */ /* polytype u, tu */
bool table_has_type_of(polytype u);	/* polytype u */
polytype bottomtype(polytype u); 		/* polytype u */
polytype bottomvar(polytype u); 		/* polytype u */

/* Procedure usetypetable(); */		/* value t */
/* Procedure deltypetable(); */

/* init */

/* Procedure initpol(); */ 	/* */

/*************************************************************************/

/* unification of polytypes */

/* Procedure unify(); */ 	/* polytype a, b, &u; bool &bad */

bool contains(polytype u, polytype a); 	/* polytype u, a */
bool equal_vars(polytype s, polytype a); 	/* polytype s, a */

/*************************************************************************/

/* type unification errors */

/* Procedure start_vars(); */ 		/* */
/* Procedure add_var(); */		/* polytype tvar */
/* Procedure end_vars(); */		/* */

/* Procedure setreprtable(); */ 	/* */
/* Procedure delreprtable(); */		/* */

/* Procedure badtyperr(); */		/* polytype a, b */
/* Procedure cyctyperr(); */		/* polytype a */

value conc(value v, value w);

#ifdef __cplusplus
}
#endif


#endif
