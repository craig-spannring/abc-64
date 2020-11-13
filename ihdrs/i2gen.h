/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I2GEN_h_41bfdaf891b1223a184ca60fb0cc4a88
#define I2GEN_h_41bfdaf891b1223a184ca60fb0cc4a88

#include <stdint.h>

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Is_node(t) ((t) != NilTree && Is_parsetree(t))

extern intptr_t nextvarnumber; /* Counts local targets (including formals) */
extern value locals, globals, mysteries, refinements;
extern string gentab[];

struct state {
	parsetree h_last;
	parsetree *h_wanthere;
	parsetree h_bpchain;
};

#define f_expr(p) fix(p, 'v') /* "evaluate" */
#define f_targ(p) fix(p, 'l') /* "locate" */

    extern Visible value copystddef();
    extern Visible bool modify_tag();
    extern Visible bool is_name();

    extern Visible Procedure fix(parsetree *pt, char flag);


#ifdef __cplusplus
}
#endif


#endif
