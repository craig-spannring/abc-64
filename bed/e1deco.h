#ifndef E1DECO_h_f9fb71726168519d6a1622d8b6c750f3
#define E1DECO_h_f9fb71726168519d6a1622d8b6c750f3


#include "b.h"
#include "bedi.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible bool      delbody(enviro *ep);
	extern Visible Procedure delfocus(pathptr *pp);
	extern Visible bool      copyinout(enviro *ep);
	extern Visible value     copyout(enviro *ep);
	extern Visible bool      ishole(enviro *ep);
	extern Visible bool      delsublist(enviro *ep);
	extern Visible bool      deltext(enviro *ep);


#ifdef __cplusplus
}
#endif


#endif
