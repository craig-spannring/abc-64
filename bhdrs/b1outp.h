#ifndef B1OUTP_h_e9069c01a2369a8f1b8ae87c2aed2ccf
#define B1OUTP_h_e9069c01a2369a8f1b8ae87c2aed2ccf

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif


    extern Visible int       getwincol(void);
    extern Visible int       getwinwidth(void);
    extern Visible Procedure c_flush(void);
    extern Visible Procedure c_putdata(string data);
    extern Visible Procedure c_putnewline(void);
    extern Visible Procedure c_putstr(string s);
    extern Visible Procedure doflush(FILE *file);
    extern Visible Procedure init_interpreter_output(int height, int width);
    extern Visible Procedure putchr(FILE* file, char c);
    extern Visible Procedure putnewline(FILE* file);
    extern Visible Procedure putstr(FILE *file, string s);
    extern Visible Procedure re_interpreter_output(void);
    
#ifdef __cplusplus
}
#endif



#endif
