/**
 * @file
 * 
 */    
#ifndef E1GOTO_h_0f6e52dc93efd32faeb0ab187d8d6145
#define E1GOTO_h_0f6e52dc93efd32faeb0ab187d8d6145

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible Procedure gotofix(enviro *ep, int y, int x);
    extern Visible bool      gotoyx(enviro *ep, int y, int x);
    extern Visible bool      gotocursor(enviro *ep);
    extern Visible bool      gotomouse(enviro *ep);

#ifdef __cplusplus
}
#endif


#endif
