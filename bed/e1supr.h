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
    

	
	Visible bool allspaces(cstring str);
	Visible bool checkep(enviro *ep);
	Visible bool ev_eq(enviro *l, enviro *r);
	Visible bool ev_eq(enviro *l, enviro *r);
	Visible bool nextnnitem(enviro *ep);
	Visible bool prevnnitem(enviro *ep);
	Visible int  focchar(enviro *ep);
	Visible int focchar(enviro *ep);
	Visible int  focindent(enviro *ep);
	Visible int focindent(enviro *ep);
	Visible int  focoffset(enviro *ep);
	Visible int focoffset(enviro *ep);
	Visible int  focwidth(enviro *ep);
	Visible int focwidth(enviro *ep);
	Visible int  lenitem(enviro *ep);
	Visible int lenitem(enviro *ep);
	Visible int  nodechar(nodeptr n);
	Visible int nodechar(nodeptr n);
	Visible Procedure firstnnitem(enviro *ep);
	Visible Procedure fixit(enviro *ep);
	Visible Procedure grow(enviro *ep, bool deleting);
	Visible Procedure growsubset(enviro *ep);
	Visible Procedure lastnnitem(enviro *ep);
	Visible Procedure leftvhole(enviro *ep);
	Visible Procedure ritevhole(enviro *ep);
	Visible Procedure s_down(enviro *ep);
	Visible Procedure s_downi(enviro *ep, int i);
	Visible Procedure s_downrite(enviro *ep);
	Visible Procedure shrink(enviro *ep);
	Visible Procedure shrsubset(enviro *ep);
	Visible Procedure s_left(enviro *ep);
	Visible Procedure s_rite(enviro *ep);
	Visible Procedure subgrow(enviro *ep, bool ignorespaces, bool deleting);
	Visible Procedure subgrsubset(enviro *ep, bool ignorespaces);
	Visible Procedure s_up(enviro *ep);
	Visible void ecopy(enviro *s, enviro *d);
	Visible void erelease(enviro* ep);

	
#ifdef __cplusplus
}
#endif


#endif
