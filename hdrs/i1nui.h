#ifndef I1NUI_h_4ca8cbab82ae2c43c5d7ff6efad3d640
#define I1NUI_h_4ca8cbab82ae2c43c5d7ff6efad3d640


#include "b.h"
#include "bobj.h"
#include "i1num.h"


#ifdef __cplusplus
extern "C" {
#endif

    extern Visible relation int_comp(integer v, integer w);
    extern Visible integer int_neg(integer u);

    extern Visible integer mk_int(double u);
    extern Visible integer int1mul(integer v, digit n1);
    extern Visible integer int_tento(int n);
    extern Visible integer int_mod(integer v, integer w);
    
    extern Visible digit int_ldiv(integer v1, integer w1, integer *pquot, integer *prem);



#ifdef __cplusplus
}
#endif


#endif
