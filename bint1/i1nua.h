/**
 * @file
 * 
 */    
#ifndef I1NUA_h_b3f3f13a4a499329c290b0f8efa67aae
#define I1NUA_h_b3f3f13a4a499329c290b0f8efa67aae

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool about2_to_integral(real ru, value v, real *rv);
    extern Visible int app_comp(real u, real v);
    extern Visible integer app_floor(real u);
    extern Visible Procedure app_print(FILE *fp, real v);
    extern Visible Procedure endapp(void);
    extern Visible Procedure initapp(void);
    extern Visible real app_diff(real u, real v);
    extern Visible real app_exp(real v);
    extern Visible real app_log(real v);
    extern Visible real app_neg(real u);
    extern Visible real app_power(real u, real v);
    extern Visible real app_prod(real u, real v);
    extern Visible real app_quot(real u, real v);
    extern Visible real app_sum(real u, real v);
    extern Visible real mk_approx(double frac, double expo);
    extern Visible value app_exactly(real u);
    extern Visible value app_frexp(value v);
    
#ifdef __cplusplus
}
#endif


#endif
