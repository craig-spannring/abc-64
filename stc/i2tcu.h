/**
 * @file
 * 
 */    
#ifndef I2TCU_h_9a42891b3bd42876f4ba4979922e3036
#define I2TCU_h_9a42891b3bd42876f4ba4979922e3036

#include "b.h"
#include "bint.h"
#include "i2stc.h"

#ifdef __cplusplus
extern "C" {
#endif

	Visible bool equal_vars(polytype s, polytype a);
	Visible Procedure unify(polytype a, polytype b, polytype *pu);
	Visible bool contains(polytype u, polytype a);
 
#ifdef __cplusplus
}
#endif




#endif
