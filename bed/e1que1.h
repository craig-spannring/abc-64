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

    Visible bool       fitnode(path *pp, node n);
    Visible Procedure  joinqueues(queue *pq, queue q);
    Visible Procedure  preptoqueue(node n, queue *pq);
    Visible Procedure  addtoqueue(queue *pq, node n);
    Visible Procedure  stringtoqueue(string str, queue *pq);
    Visible node       queuebehead(queue *pq);
    Visible Procedure  splitnode(node n, queue *pq);
    Visible bool       resttoqueue(path *pp, queue *pq);
    Visible Procedure  nosuggtoqueue(environ *ep, queue *pq);
    Visible bool       issuggestion(environ *ep);
    Visible bool       fitnode(path *pp, node n);
    Visible int        fitstring(path *pp, string str, int alt_c);
    Visible Procedure  fixfocus(environ *ep, int len);
    Visible bool       spacefix(environ *ep);
    Visible Procedure  subsettoqueue(node n, int s1, int s2, queue *pq);
    Visible string     querepr(value qv);

#ifdef __cplusplus
}
#endif


#endif
