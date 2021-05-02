#ifndef E1DECO_h_f9fb71726168519d6a1622d8b6c750f3
#define E1DECO_h_f9fb71726168519d6a1622d8b6c750f3


#include "b.h"
#include "bedi.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * Delete the focus under the assumption that it contains some text.
	 */
	extern Visible bool      delbody(enviro *ep);
	
	extern Visible Procedure delfocus(pathptr *pp);
	extern Visible bool      copyinout(enviro *ep);

	/// Copy the focus to the copy buffer.
	extern Visible value     copyout(enviro *ep);
	
	extern Visible bool      ishole(enviro *ep);
	extern Visible bool      delsublist(enviro *ep);
	
	/**
	 * Delete command -- delete the text in the focus, or delete the hole
	 * if it is only a hole.
	 */
	extern Visible bool      deltext(enviro *ep);


#ifdef __cplusplus
}
#endif


#endif
