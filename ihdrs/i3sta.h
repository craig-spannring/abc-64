#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

Visible Procedure formula();
Visible Procedure proposition();

extern parsetree pc; /* 'Program counter', current parsetree node */
extern parsetree next; /* Next parsetree node (changed by jumps) */
extern bool report; /* 'Condition code register', outcome of last test */

#ifdef __cplusplus
extern "C" }
#endif
