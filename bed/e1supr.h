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
	Visible bool checkep(environ *ep);
	Visible bool ev_eq(environ *l, environ *r);
	Visible bool ev_eq(environ *l, environ *r);
	Visible bool nextnnitem(environ *ep);
	Visible bool prevnnitem(environ *ep);
	Visible int  focchar(environ *ep);
	Visible int focchar(environ *ep);
	Visible int  focindent(environ *ep);
	Visible int focindent(environ *ep);
	Visible int  focoffset(environ *ep);
	Visible int focoffset(environ *ep);
	Visible int  focwidth(environ *ep);
	Visible int focwidth(environ *ep);
	Visible int  lenitem(environ *ep);
	Visible int lenitem(environ *ep);
	Visible int  nodechar(nodeptr n);
	Visible int nodechar(nodeptr n);
	Visible Procedure firstnnitem(environ *ep);
	Visible Procedure fixit(environ *ep);
	Visible Procedure grow(environ *ep, bool deleting);
	Visible Procedure growsubset(environ *ep);
	Visible Procedure lastnnitem(environ *ep);
	Visible Procedure leftvhole(environ *ep);
	Visible Procedure ritevhole(environ *ep);
	Visible Procedure s_down(environ *ep);
	Visible Procedure s_downi(environ *ep, int i);
	Visible Procedure s_downrite(environ *ep);
	Visible Procedure shrink(environ *ep);
	Visible Procedure shrsubset(environ *ep);
	Visible Procedure s_left(environ *ep);
	Visible Procedure s_rite(environ *ep);
	Visible Procedure subgrow(environ *ep, bool ignorespaces, bool deleting);
	Visible Procedure subgrsubset(environ *ep, bool ignorespaces);
	Visible Procedure s_up(environ *ep);
	Visible void ecopy(environ *s, environ *d);
	Visible void erelease(environ* ep);

	
#ifdef __cplusplus
}
#endif


#endif
