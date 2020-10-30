#ifndef I3ERR_h_a1e1cf2b6484814b53131a39dfacff21
#define I3ERR_h_a1e1cf2b6484814b53131a39dfacff21

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible Procedure bye(int ex);
    Visible Procedure immexit(int status);
    Visible Procedure putserr(string s);
    Visible Procedure flusherr(void);
    Visible Procedure syserr(int);
    Visible Procedure memexh(void);
    Visible Procedure pprerrV(int m, value v);
    Visible Procedure pprerr(int m);
    Visible Procedure parerrV(int m, value v);
    Visible Procedure parerr(int m);
    Visible Procedure fixerrV(int m, value v);
    Visible Procedure fixerr(int m);
    Visible Procedure interr(int m);
    Visible Procedure int_signal(void);
    Visible Procedure putsSerr(string fmt, string s);
    Visible Procedure putsDSerr(string fmt, int d, string s);
    Visible Procedure puts2Cerr(string fmt, char c1, char c2);
    Visible Procedure putsCerr(string fmt, char c);
    Visible Procedure interrV(int m, value v);
    Visible Procedure initfmt(void);
    Visible Procedure initerr(void);
    Visible Procedure re_errfile(void);
    Visible Procedure checkerr(void);
    Visible Procedure typerrV(int m, value v);

#ifdef __cplusplus
}
#endif

#endif
