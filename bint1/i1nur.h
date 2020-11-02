/**
 * @file
 * 
 */    
#ifndef I1NUR_h_695a871be64a8ac277c1fc6897088d41
#define I1NUR_h_695a871be64a8ac277c1fc6897088d41

#include "b.h"
#include "bobj.h"
#include "i1num.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible rational mk_rat(integer x, integer y, int len, bool simplify);
    extern Visible rational rat_sum(rational u, rational v);
    extern Visible rational rat_diff(rational u, rational v);
    extern Visible rational rat_prod(rational u, rational v);
    extern Visible rational rat_quot(rational u, rational v);
    extern Visible rational rat_neg(rational u);
    extern Visible rational rat_power(rational a, integer n);
    extern Visible relation rat_comp(rational u, rational v);
    extern Visible rational rat_zero(void);
    extern Visible Procedure rat_init(void);
    extern Visible Procedure endrat(void);

#ifdef __cplusplus
}
#endif


#endif
