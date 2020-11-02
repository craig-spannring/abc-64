/**
 * @file
 * 
 */    
#ifndef E1QUE2_h_4dcf3070ad6342283a9c9f359f6435df
#define E1QUE2_h_4dcf3070ad6342283a9c9f359f6435df

#include "b.h"
#include "supr.h"
#include "queu.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool      app_queue(environ *ep, queue *pq);
    Visible bool      fix_move(environ *ep);
    Visible bool      ins_queue(environ *ep, queue *pq, queue *pq2);
    Visible bool      ins_string(environ *ep, string str, queue *pq, int alt_c);
    Visible bool      move_on(environ *ep);
    Visible int       joinstring(path *pp, string str, bool spflag, int alt_c, bool mayindent);
    Visible Procedure qshow(queue q, string where);

#ifdef __cplusplus
}
#endif


#endif
