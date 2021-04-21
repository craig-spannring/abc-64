#ifndef E1ERRO_h_1822d89a528ba85600d5465a2e5417e2
#define E1ERRO_h_1822d89a528ba85600d5465a2e5417e2


#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible Procedure asserr(conststring file, int line);
    extern Visible Procedure debug(string fmt, ...);
    extern Visible Procedure debug(string fmt, ...); 
    extern Visible Procedure ederrC(int m, char c);
    extern Visible Procedure ederr(int m);
    extern Visible Procedure ederrS(int m, string s);
    extern Visible Procedure edmessage(conststring s);
    extern Visible Procedure end_erro(void);
    extern Visible Procedure enderro(void);
    extern Visible Procedure init_erro(void);
    extern Visible Procedure stsline(int totlines, int topline, int scrlines, value copybuffer, bool recording);

#ifdef __cplusplus
}
#endif

#endif
