/**
 * @file
 * 
 */    
#ifndef E1QUE1_h_72c83f3ac053a3fc6ee7a151d385b55e
#define E1QUE1_h_72c83f3ac053a3fc6ee7a151d385b55e

#include "b.h"
#include "bedi.h"
#include "queu.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool       fitnode(pathptr *pp, nodeptr n);
    Visible Procedure  joinqueues(queueptr *pq, queueptr q);
    Visible Procedure  preptoqueue(nodeptr n, queueptr *pq);
    Visible Procedure  addtoqueue(queueptr *pq, nodeptr n);
    Visible Procedure  stringtoqueue(cstring str, queueptr *pq);
    Visible nodeptr       queuebehead(queueptr *pq);
    Visible Procedure  splitnode(nodeptr n, queueptr *pq);
    Visible bool       resttoqueue(pathptr *pp, queueptr *pq);
    Visible Procedure  nosuggtoqueue(enviro *ep, queueptr *pq);
    Visible bool       issuggestion(enviro *ep);
    Visible bool       fitnode(pathptr *pp, nodeptr n);
    Visible int        fitstring(pathptr *pp, cstring str, int alt_c);
    Visible Procedure  fixfocus(enviro *ep, int len);
    Visible bool       spacefix(enviro *ep);
    Visible Procedure  subsettoqueue(nodeptr n, int s1, int s2, queueptr *pq);
    Visible string     querepr(value qv);

#ifdef __cplusplus
}
#endif


#endif
