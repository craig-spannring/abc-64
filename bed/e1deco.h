#ifndef E1DECO_h_f9fb71726168519d6a1622d8b6c750f3
#define E1DECO_h_f9fb71726168519d6a1622d8b6c750f3


#include "b.h"
#include "bedi.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool delbody(environ *ep);
    extern Visible Procedure delfocus(path *pp);
    extern Visible bool copyinout(environ *ep);
    extern Visible value copyout(environ *ep);
    extern Visible bool ishole(environ *ep);
    
#ifdef __cplusplus
}
#endif


#endif
