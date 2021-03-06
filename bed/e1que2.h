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

    Visible bool      app_queue(enviro *ep, queueptr *pq);
    Visible bool      fix_move(enviro *ep);
    Visible bool      ins_queue(enviro *ep, queueptr *pq, queueptr *pq2);
    Visible bool      ins_string(enviro *ep, string str, queueptr *pq, int alt_c);
    Visible bool      move_on(enviro *ep);
    Visible int       joinstring(pathptr *pp, cstring str, bool spflag, int alt_c, bool mayindent);
    Visible Procedure qshow(queueptr q, cstring where);

#ifdef __cplusplus
}
#endif


#endif
