/**
 * @file
 * 
 */    
#ifndef E1MOVE_h_eebbbbde9b0d260e690a8f360aaab147
#define E1MOVE_h_eebbbbde9b0d260e690a8f360aaab147

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool previous(environ *ep);
    Visible bool nextarrow(environ *ep);
    Visible bool leftarrow(environ *ep);
    Visible bool ritearrow(environ *ep);
    Visible bool uparrow(environ *ep);
    Visible bool downarrow(environ *ep);
    Visible bool upline(environ *ep);
    Visible bool acceptcommand(environ *ep);
    Visible bool downline(environ *ep);

#ifdef __cplusplus
}
#endif


#endif
