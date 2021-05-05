#ifndef I3ERR_h_a1e1cf2b6484814b53131a39dfacff21
#define I3ERR_h_a1e1cf2b6484814b53131a39dfacff21

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure bye(int ex);
	extern Visible Procedure immexit(int status);
	extern Visible Procedure putserr(cstring s);
	extern Visible Procedure flusherr(void);
	extern Visible Procedure syserr(int);
	extern Visible Procedure memExhausted(void);
	extern Visible Procedure pprerrV(int m, value v);
	extern Visible Procedure pprerr(int m);
	extern Visible Procedure parerrV(int m, value v);
	extern Visible Procedure parerr(int m);
	extern Visible Procedure fixerrV(int m, value v);
	extern Visible Procedure fixerr(int m);
	extern Visible Procedure interr(int m);
	extern Visible Procedure int_signal(void);
	extern Visible Procedure putsSerr(cstring fmt, cstring s);
	extern Visible Procedure putsDSerr(cstring fmt, int d, cstring s);
	extern Visible Procedure puts2Cerr(cstring fmt, char c1, char c2);
	extern Visible Procedure putsCerr(cstring fmt, char c);
	extern Visible Procedure interrV(int m, value v);
	extern Visible Procedure initfmt(void);
	extern Visible Procedure initerr(void);
	extern Visible Procedure re_errfile(void);
	extern Visible Procedure checkerr(void);
	extern Visible Procedure typerrV(int m, value v);
	extern Visible Procedure fpe_signal(void);
	extern Visible char *getfmtbuf(cstring fmt, int n);
    
#ifdef __cplusplus
}
#endif

#endif
