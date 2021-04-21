/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GETC_h_c06b651237197d844f2ff87b2934f37b
#define GETC_h_c06b651237197d844f2ff87b2934f37b

#ifdef __cplusplus
extern "C" {
#endif

extern Procedure initkeys(void);

typedef struct tabent {
	int code;
	int deflen;
	cstring def;
	cstring rep;
	cstring name;
} tabent;

extern struct tabent deftab[];
extern int ndefs; 		/* number of entries in deftab */
extern Procedure addkeydef(int code, int deflen, string def, string rep, string name);

#ifdef KEYS

#define MAXDEFS 200

#else

#define MAXDEFS 100

#endif

#ifdef __cplusplus
}
#endif


#endif
