/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#include "b.h"

#ifndef COMMON_OS_h_eb22fe55fccd269cb781f66cdffd0eb1
#define COMMON_OS_h_eb22fe55fccd269cb781f66cdffd0eb1


#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

extern Visible Porting long filemodtime(char *filename);
extern Visible Porting Procedure freepath(char *path);
extern Visible Porting const char *curdir(void);

#ifdef __cplusplus
}
#endif


#endif
