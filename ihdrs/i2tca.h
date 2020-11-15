/**
 * @file
 * 
 */    
#ifndef I2TCA_h_f4c4d580578b60a0be69df9cd5b0e735
#define I2TCA_h_f4c4d580578b60a0be69df9cd5b0e735

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure type_check(parsetree v);
	extern Visible Procedure initstc(void);
	extern Visible Procedure put_types(void);
	extern Visible Procedure endstc(void);
	extern Visible Procedure rectypes(void);
	extern Visible value stc_code(value pname);
	extern Visible Procedure del_types(void);
	extern Visible Procedure adjust_types(bool no_change);
 

#ifdef __cplusplus
}
#endif




#endif
