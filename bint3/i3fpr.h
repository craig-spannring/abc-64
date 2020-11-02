/**
 * @file
 * 
 */    
#ifndef I3FPR_h_b619c12d567596ffb6483c6b991aa079
#define I3FPR_h_b619c12d567596ffb6483c6b991aa079

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible Procedure initfpr(void);
    extern Visible Procedure endfpr(void);
    extern Visible bool is_zerfun(value t, value *f);
    extern Visible bool is_monfun(value t, value *f);
    extern Visible bool is_dyafun(value t, value *f);
    extern Visible bool is_zerprd(value t, value *p);
    extern Visible bool is_monprd(value t, value *p);
    extern Visible bool is_dyaprd(value t, value *p);
    extern Visible value pre_fun(value nd1, intlet pre, value nd2);
    extern Visible bool pre_prop(value nd1, intlet pre, value nd2);
    extern Visible value nowisthetime(void);

#ifdef __cplusplus
}
#endif


#endif
