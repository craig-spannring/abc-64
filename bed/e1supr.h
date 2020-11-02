/**
 * @file
 * 
 */    
#ifndef E1SUPR_h_2115d5d2980180e9da9293d6c42f4cc1
#define E1SUPR_h_2115d5d2980180e9da9293d6c42f4cc1

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    Visible bool allspaces(string str);
    Visible bool nextnnitem(environ *ep);
    Visible bool prevnnitem(environ *ep);
    Visible int  focchar(environ *ep);
    Visible int  focindent(environ *ep);
    Visible int  focoffset(environ *ep);
    Visible int  focwidth(environ *ep);
    Visible int  lenitem(environ *ep);
    Visible int  nodechar(node n);
    Visible void ecopy(environ *s, environ *d);
    Visible void erelease(environ* ep);
    Visible bool checkep(environ *ep);
    Visible bool ev_eq(environ *l, environ *r);

#ifdef __cplusplus
}
#endif


#endif
