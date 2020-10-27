/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3STA_h_e191288aeba0df55cccdaf9d99ce93ec
#define I3STA_h_e191288aeba0df55cccdaf9d99ce93ec

#ifdef __cplusplus
extern "C" {
#endif

Visible Procedure formula();
Visible Procedure proposition();

extern parsetree pc; /* 'Program counter', current parsetree node */
extern parsetree next; /* Next parsetree node (changed by jumps) */
extern bool report; /* 'Condition code register', outcome of last test */

#ifdef __cplusplus
extern "C" }
#endif


#endif
