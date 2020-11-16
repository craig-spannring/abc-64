/**
 * @file
 * 
 */    
#ifndef I1OBJ_h_a767b469a93485bbb48855c6f634ec38
#define I1OBJ_h_a767b469a93485bbb48855c6f634ec38

#include "b.h"
#include "bint.h"
#include "bobj.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible bool comp_ok; 		/* Temporary, to catch type errors */

	extern Visible unsigned tltsyze(literal type, intlet len, int *nptrs);
	extern Visible Procedure rel_subvalues(value v);
	extern Visible relation compare(value v, value w);
	extern Visible double hash(value v);
	extern Visible value convert(value v, bool coll, bool outer);
	extern Visible value adjleft(value v, value w);
	extern Visible value adjright(value v, value w);
	extern Visible value centre(value v, value w) ;

#ifdef __cplusplus
}
#endif




#endif
