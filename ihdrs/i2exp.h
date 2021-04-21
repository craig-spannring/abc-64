/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I2EXP_h_be6d4bd6abb880812f0a598b32e92477
#define I2EXP_h_be6d4bd6abb880812f0a598b32e92477

#include "b.h"
#include "i2par.h"

#ifdef __cplusplus
extern "C" {
#endif

/* General definitions for parsing expressions */

/* Avoid conflict with extra reserved word: */
#define comp b_comp

	typedef struct {							
			parsetree *stack;
			parsetree *sp;
			parsetree *top;
			int nextend;
			char level;		/* PARSER or FIXER */
			char /* bool */ prop;	/* Yes while fixing left expr dya pred */
			intlet nfield;		/* fieldnr unparsed node during fixing */
	} expadm;
	
#define Stack(adm)	(adm->stack)
#define Sp(adm)		(adm->sp)
#define Top(adm)	(adm->top)
#define Nextend(adm)	(adm->nextend)
#define Level(adm)	(adm->level)
#define Prop(adm)	(adm->prop)
#define Nfld(adm)	(adm->nfield)

#define N_EXP_STACK	15
#define N_LTA_STACK	100

#define Pop(adm)	*--Sp(adm)

#define PARSER 'p'
#define FIXER  'f'

#define Bottom "$"

#define Dya_opr(v) (Valid(v) && Is_compound(v))

/************************************************************************/

	struct prio {
			cstring  fun;
			char         adic;
			int          L;
			int          H;
	};

#define P_mon '1'
#define P_dya '2'

#define dprio(i) pprio(i, P_dya)
#define mprio(i) pprio(i, P_mon)

	struct prio * pprio(value f, char adic);
	
	extern Visible bool tag_operator(txptr q, value *v);
	extern Visible Procedure initexp(expadm *adm, int n, char level);
	
	extern Visible Procedure selection(txptr q, parsetree *v);

	extern Visible Procedure endstack(expadm *adm);
	extern Visible Procedure push_item(expadm *adm, parsetree v);
	extern Visible Procedure do_dya(expadm *adm, value v);
	extern Visible Procedure reduce(expadm *adm);

	extern Visible Procedure trim_target(txptr q, parsetree *v);

#ifdef __cplusplus
}
#endif


#endif
