/**
 * @file
 * Access and update lists and tables
 */    
#ifndef I1LTA_h_bac10475d29f72164fbeb1c1e864a845
#define I1LTA_h_bac10475d29f72164fbeb1c1e864a845

#include "b.h"
#include "i1btr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible Procedure cpynptrs(btreeptr *to, btreeptr *from, int n);
    Visible Procedure movnitms(itemptr to, itemptr from, intlet n, intlet iw);
    Visible Procedure cpynitms(itemptr to, itemptr from, intlet n, intlet it);


#ifdef __cplusplus
}
#endif
#endif
