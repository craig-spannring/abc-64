/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GRAM_h_64b4d3cfdb1487119a98b4694402681d
#define GRAM_h_64b4d3cfdb1487119a98b4694402681d

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Routines defined in "gram.c".
 */

cstring *noderepr(nodeptr);
nodeptr gram(int sym);
// nodeptr suggestion();
// nodeptr variable();
cstring symname(int sym);
bool allows_colon(int sym);

/*
 * Macros for oft-used functions.
 */

#define Fwidth(str) ((str) ? fwidth(str) : 0)

#define Fw_zero(str) (!(str) || strchr("\b\t", (str)[0]))
#define Fw_positive(str) ((str) && (str)[0] >= ' ')
#define Fw_negative(str) ((str) && (str)[0] == '\n')

#define MAXNBUILTIN 50	/* should be calculated by boot/mktable */

extern Visible int fwidth(cstring str);

#ifdef __cplusplus
}
#endif


#endif
