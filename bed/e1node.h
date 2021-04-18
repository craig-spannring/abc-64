/**
 * @file
 *
 */
#ifndef E1NODE_h_44b07127bc6670a2c2307dec9a325182
#define E1NODE_h_44b07127bc6670a2c2307dec9a325182

#include "b.h"
#include "bedi.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool      downi(path *pp, int i);
    Visible bool      downrite(path *pp);
    Visible bool      firstmarked(path *pp, markbits x);
    Visible bool      left(path *pp);
    Visible bool      rite(path *pp);
    Visible bool      up(path *pp);
    Visible int       nodewidth(nodeptr n);
    Visible int       pathlength(path p);
    Visible nodeptr      newnode(int nch, int sym, nodeptr *children);
    Visible path      newpath(path pa, nodeptr n, int i);
    Visible Procedure markpath(path *pp, markbits new);
    Visible Procedure putintrim(value *pn, int head, int tail, string str);
    Visible Procedure setchild(nodeptr *pn, int i, nodeptr n);
    Visible Procedure top(path *pp);
    Visible Procedure touchpath(path *pp);
    Visible Procedure treereplace(path *pp, nodeptr n);
    Visible Procedure unmkpath(path *pp, int del);

#ifdef __cplusplus
}
#endif


#endif
