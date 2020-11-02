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

    extern Visible Procedure gotofix(environ *ep, int y, int x);
    extern Visible bool      gotoyx(environ *ep, int y, int x);
    extern Visible bool      gotocursor(environ *ep);
    extern Visible bool      gotomouse(environ *ep);

#ifdef __cplusplus
}
#endif


#endif
