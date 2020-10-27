/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3IN2_h_b32a402960b8ca952c1686cb8ded04bf
#define I3IN2_h_b32a402960b8ca952c1686cb8ded04bf

#ifdef __cplusplus
extern "C" {
#endif

/* Interpreter utilities */

value v_local();
value v_global();
loc local_loc();
loc global_loc();
loc trim_loc();
loc tbsel_loc();
value pre_fun();
extern value resval;

value evalthread();

#define Changed_formal(v) (v == Vnil || !Is_indirect(v))

value locvalue();

#ifdef __cplusplus
}
#endif


#endif
