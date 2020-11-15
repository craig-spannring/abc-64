/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GRAM_h_64b4d3cfdb1487119a98b4694402681d
#define GRAM_h_64b4d3cfdb1487119a98b4694402681d

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Routines defined in "gram.c".
 */

string *noderepr(node);
node gram(int sym);
// node suggestion();
// node variable();
string symname(int sym);
bool allows_colon(int sym);

/*
 * Macros for oft-used functions.
 */

#define Fwidth(str) ((str) ? fwidth(str) : 0)

#define Fw_zero(str) (!(str) || strchr("\b\t", (str)[0]))
#define Fw_positive(str) ((str) && (str)[0] >= ' ')
#define Fw_negative(str) ((str) && (str)[0] == '\n')

#define MAXNBUILTIN 50	/* should be calculated by boot/mktable */

extern Visible int fwidth(string str);

#ifdef __cplusplus
}
#endif


#endif
