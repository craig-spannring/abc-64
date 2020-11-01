/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3SCR_h_ffa7e82621c3216643ace1d1a0e8e49b
#define I3SCR_h_ffa7e82621c3216643ace1d1a0e8e49b

#include "b.h"


#ifdef __cplusplus
extern "C" {
#endif

/* screen */

extern value iname;
extern bool outeractive;
extern bool at_nwl;
extern bool Eof;
extern FILE *ifile;
extern FILE *sv_ifile;
extern char *get_line(void);
extern char q_answer(int m, char c1, char c2, char c3);
extern char *getfmtbuf(string fmt, int n);


#ifdef __cplusplus
}
#endif


#endif
