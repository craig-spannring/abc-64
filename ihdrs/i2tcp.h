/**
 * @file
 * 
 */    
#ifndef I2TCP_h_8babb25e0326957da0c87a9f4efc3182
#define I2TCP_h_8babb25e0326957da0c87a9f4efc3182


#include "b.h"
#include "i2stc.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure putsubtype(polytype sub, polytype u, intlet isub);
	extern Visible polytype mkt_polytype(typekind k, intlet nsub);
	extern Visible Procedure putsubtype(polytype sub, polytype u, intlet isub);
	extern Visible Procedure new_externals(void);
	extern Visible polytype mkt_ext(void);
	extern Visible Procedure p_release(polytype u);
	extern Visible Procedure repl_type_of(polytype u, polytype p);
	extern Visible polytype bottomtype(polytype u);
	extern Visible Procedure usetypetable(value t);
	extern Visible Procedure deltypetable(void);
	extern Visible Procedure initpol(void);
	extern Visible Procedure endpol(void);

#ifdef __cplusplus
}
#endif


#endif
