/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GETC_h_c06b651237197d844f2ff87b2934f37b
#define GETC_h_c06b651237197d844f2ff87b2934f37b

#ifdef __cplusplus
extern "C" {
#endif

extern Procedure initkeys();

typedef struct tabent {
	int code;
	int deflen;
	string def;
	string rep;
	string name;
} tabent;

extern struct tabent deftab[];
extern int ndefs; 		/* number of entries in deftab */
extern Procedure addkeydef();

#ifdef KEYS

#define MAXDEFS 200

#else

#define MAXDEFS 100
extern Procedure initgetc();
extern Procedure endgetc();

#endif

#ifdef __cplusplus
extern "C" }
#endif


#endif
