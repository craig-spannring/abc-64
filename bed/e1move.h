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

    Visible bool previous(enviro *ep);
    Visible bool nextarrow(enviro *ep);
    Visible bool leftarrow(enviro *ep);
    Visible bool ritearrow(enviro *ep);
    Visible bool uparrow(enviro *ep);
    Visible bool downarrow(enviro *ep);
    Visible bool upline(enviro *ep);
    Visible bool acceptcommand(enviro *ep);
    Visible bool downline(enviro *ep);

#ifdef __cplusplus
}
#endif


#endif
