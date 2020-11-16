/**
 * @file
 * 
 */    
#ifndef I1TRA_h_51c46664334c487f05a56bad2049af9c
#define I1TRA_h_51c46664334c487f05a56bad2049af9c

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible value mkchar(char c);
	extern Visible value stripped(value t);
	extern Visible value split(value t);
	extern Visible value upper(value t);
	extern Visible value lower(value t);
	extern Visible Procedure ins_range(value lwb, value upb, value *pl);
	extern Visible value choice(value train);
	
#ifdef __cplusplus
}
#endif


#endif
