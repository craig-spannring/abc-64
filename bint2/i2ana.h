/**
 * @file
 * 
 */    
#ifndef I2ANA_h_4d2a1a7dc3c72828fbe997672d56672d
#define I2ANA_h_4d2a1a7dc3c72828fbe997672d56672d

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible conststring gentab[];
	extern Visible intptr_t nextvarnumber; /* Counts local targets (including formals) */
	extern Visible value locals;
	extern Visible value globals;
	extern Visible value mysteries;
	extern Visible value refinements;
	
	extern Visible value *setup(parsetree t);
	extern Visible Procedure cleanup(void);
	extern Visible Procedure analyze(parsetree t, value *targs);
	extern Visible Procedure analyze(parsetree t, value *targs);

#ifdef __cplusplus
}
#endif




#endif
