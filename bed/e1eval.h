#ifndef E1EVAL_h_65cd8b2a39894fa8cf100ffb661c1e99
#define E1EVAL_h_65cd8b2a39894fa8cf100ffb661c1e99

#include "b.h"
#include "bedi.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible Procedure evalcoord(nodeptr n, int jch, int *py, int *px, int *plevel); 
    extern Visible int fwidth(cstring str);
    extern Visible int evalwidth(nodeptr n);

#ifdef __cplusplus
}
#endif


#endif
