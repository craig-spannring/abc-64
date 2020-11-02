/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3IN2_h_b32a402960b8ca952c1686cb8ded04bf
#define I3IN2_h_b32a402960b8ca952c1686cb8ded04bf

#ifdef __cplusplus
extern "C" {
#endif

/* Interpreter utilities */

value v_local(value name, value number);
value v_global(value name);
loc local_loc(basidf i);
loc global_loc(basidf i);
loc trim_loc(loc l, value N, char sign);
loc tbsel_loc(loc R, value K);
value pre_fun(value nd1, intlet pre, value nd2);
extern value resval;

value evalthread(parsetree start);

#define Changed_formal(v) (v == Vnil || !Is_indirect(v))

value locvalue(loc l, value **ll, bool err);

bool in_ranger(loc l, value *pv);

#ifdef __cplusplus
}
#endif


#endif
