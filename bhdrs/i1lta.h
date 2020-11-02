/**
 * @file
 * Access and update lists and tables
 */    
#ifndef I1LTA_h_bac10475d29f72164fbeb1c1e864a845
#define I1LTA_h_bac10475d29f72164fbeb1c1e864a845

#include "b.h"
#include "bobj.h"
#include "i1btr.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
            btreeptr s_ptr;
            int s_lim;
    } finger[Maxheight], *fingertip;

    Visible bool      deleteitem(value *pt, value k) ;
    Visible bool      in_keys(value k, value t);
    Visible bool      is_rangelist(value v);
    Visible bool      uniq_assoc(value t, value k);
    Visible fingertip unzip(btreeptr p, int at, fingertip s);
    Visible int       l2size(value e, value v);
    Visible intlet    uflow(intlet n, intlet l, char *cbuf, btreeptr *pbuf, intlet it);
    Visible int       movnptrs(btreeptr *to, btreeptr *from, int n);
    Visible Procedure cpynitms(itemptr to, itemptr from, intlet n, intlet it);
    Visible Procedure cpynptrs(btreeptr *to, btreeptr *from, int n);
    Visible Procedure insert(value v, value *pl);
    Visible Procedure movnitms(itemptr to, itemptr from, intlet n, intlet iw);
    Visible Procedure replace(value a, value *pt, value k);
    Visible Procedure vremove(value v, value *pl);
    Visible relation  comp_text(value u, value v);
    Visible relation  comp_tlt(value u, value v);
    Visible value*    adrassoc(value t, value k);
    Visible value     associate(value t, value k);
    Visible value*    assoc(value v, intlet k);
    Visible value     keys(value t);
    Visible value*    key(value v, intlet k);
    Visible value     l2max(value e, value v);
    Visible value     l2min(value e, value v);
    Visible value     mk_range(value v1, value v2);
    Visible value     thof(int k, value v);
    

#ifdef __cplusplus
}
#endif
#endif
