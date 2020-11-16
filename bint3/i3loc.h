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

	extern Visible value locvalue(loc l, value **ll, bool err);
	extern Visible Procedure uniquify(loc l);
	extern Visible Procedure check_location(loc l);
	extern Visible loc trim_loc(loc l, value N, char sign);
	extern Visible loc tbsel_loc(loc R, value K);
	extern Visible loc local_loc(basidf i);
	extern Visible loc global_loc(basidf i);
	extern Visible Procedure put(value v, loc l);
	extern Visible Procedure put_with_check(value v, loc l);
	extern Visible Procedure l_del(loc l);
	extern Visible Procedure l_delete(loc l);
	extern Visible Procedure l_insert(value v, loc l);
	extern Visible Procedure l_remove(value v, loc l);
	extern Visible Procedure bindlocation(loc l);
	extern Visible Procedure unbind(loc l);
	
#ifdef __cplusplus
}
#endif


#endif
