/**
 * @file
 * 
 */    
#ifndef I3INI_h_32de7e8e1c2bbb580a81c0e6ebecfc92
#define I3INI_h_32de7e8e1c2bbb580a81c0e6ebecfc92

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible bool been_interactive;
	extern Visible bool in_init;
	extern Visible bool use_bed;

	extern Visible Procedure checkfileargs(int argc, char **argv);
	extern Visible Procedure abc(int argc, char **argv);
	extern Visible Procedure pre_init(void);
	extern Visible Procedure init(void);
	extern Visible Procedure endall(void);
	extern Visible Procedure crashend(void) ;

#ifdef __cplusplus
}
#endif




#endif
