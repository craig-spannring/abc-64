/**
 * @file
 * 
 */    
#ifndef I2TCE_h_a0fa9982a8638f4e28658afd31d24412
#define I2TCE_h_a0fa9982a8638f4e28658afd31d24412

#include "b.h"
#include "i2stc.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure adderrvar(polytype t);
	extern Visible Procedure add_var(polytype tvar);
	extern Visible Procedure badtyperr(polytype a, polytype b);
	extern Visible Procedure delreprtable(void);
	extern Visible Procedure enderrvars(void);
	extern Visible Procedure end_vars(void);
	extern Visible Procedure setreprtable(void);
	extern Visible Procedure starterrvars(void);
	extern Visible Procedure start_vars(void);
	extern Visible Procedure start_vars(void);
	extern Visible value conc(value v, value w);

#ifdef __cplusplus
}
#endif

#endif
