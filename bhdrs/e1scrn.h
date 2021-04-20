/**
 * @file
 * 
 */    
#ifndef E1SCRN_h_3891157d22418fc82c64970b5caa437c
#define E1SCRN_h_3891157d22418fc82c64970b5caa437c

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible Procedure actupdate(value copybuffer, bool recording, bool lasttime);
    Visible Procedure virtupdate(enviro *oldep, enviro *newep, int highest);
    Visible Procedure initterm(void);
    Visible Procedure endterm(void);
    Visible Procedure endshow(void);
    Visible bool      backtranslate(int *py, int *px);
    Visible Procedure setindent(int x);
    Visible Procedure cmdprompt(conststring prompt);

#ifdef __cplusplus
}
#endif


#endif
