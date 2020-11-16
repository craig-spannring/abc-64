/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3STA_h_e191288aeba0df55cccdaf9d99ce93ec
#define I3STA_h_e191288aeba0df55cccdaf9d99ce93ec

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible parsetree pc; /* 'Program counter', current parsetree node */
	extern Visible parsetree next; /* Next parsetree node (changed by jumps) */
	extern Visible bool report; /* 'Condition code register', outcome of last test */
	extern Visible int call_level; /* While run() can be called recursively */

	extern Visible value pop(void);
	extern Visible Procedure push(value v);
	extern Visible Procedure ret(void);
	extern Visible Procedure call_refinement(value name, parsetree def, bool test);
	extern Visible Procedure formula(value nd1, value name, value nd2, value tor);
	extern Visible Procedure proposition(value nd1, value name, value nd2, value pred);
	extern Visible Procedure x_user_command(value name, parsetree actuals, value def);
	extern Visible Procedure endsta(void);


#ifdef __cplusplus
}
#endif


#endif
