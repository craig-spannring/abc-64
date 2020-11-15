/**
 * @file
 * 
 */    
#ifndef I3LOC_h_7f7176efe725d91ee152a4c880b34b54
#define I3LOC_h_7f7176efe725d91ee152a4c880b34b54

#include "b.h"
#include "bint.h"


#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure bindlocation(loc l);
	extern Visible Procedure unbind(loc l);
	extern Visible Procedure put(value v, loc l);
	
	extern Visible value locvalue(loc l, value **ll, bool err);
	extern Visible Procedure l_del(loc l);
	extern Visible Procedure check_location(loc l);

#ifdef __cplusplus
}
#endif


#endif
