/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3TYP_h_25c87fed60f45a51c0bb254a92f2c287
#define I3TYP_h_25c87fed60f45a51c0bb254a92f2c287

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Type matching */

typedef value btype;
btype valtype(value v);
btype loctype(loc l);
/* Procedure must_agree(); */


#ifdef __cplusplus
}
#endif


#endif
