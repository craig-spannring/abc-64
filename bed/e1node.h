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

    Visible bool      downi(pathptr *pp, int i);
    Visible bool      downrite(pathptr *pp);
    Visible bool      firstmarked(pathptr *pp, markbits x);
    Visible bool      left(pathptr *pp);
    Visible bool      rite(pathptr *pp);
    Visible bool      up(pathptr *pp);
    Visible int       nodewidth(nodeptr n);
    Visible int       pathlength(pathptr p);
    Visible nodeptr      newnode(int nch, int sym, nodeptr *children);
    Visible pathptr      newpath(pathptr pa, nodeptr n, int i);
    Visible Procedure markpath(pathptr *pp, markbits new_marks);
    Visible Procedure putintrim(value *pn, int head, int tail, string str);
    Visible Procedure setchild(nodeptr *pn, int i, nodeptr n);
    Visible Procedure top(pathptr *pp);
    Visible Procedure touchpath(pathptr *pp);
    Visible Procedure treereplace(pathptr *pp, nodeptr n);
    Visible Procedure unmkpath(pathptr *pp, int del);

#ifdef __cplusplus
}
#endif


#endif
