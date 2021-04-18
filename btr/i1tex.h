/**
 * @file
 * 
 */    
#ifndef I1TEX_h_daedbdf1acf7a50585385c4d94e68710
#define I1TEX_h_daedbdf1acf7a50585385c4d94e68710

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible char      charval(value v);
    Visible char      ncharval(int n, value v);
    Visible bool      character(value v);
    Visible value     mk_text(conststring s);
    Visible string    strval(value v);
    Visible Procedure endstrval(void);
    Visible string    sstrval(value v);
    Visible Procedure fstrval(string s);
    Visible value     curtail(value t, value after);
    Visible value     behead(value t, value before);
    Visible value     concat(value tleft, value tright);
    Visible Procedure concato(value *v, value t);
    Visible value     repeat(value t, value n);
    Visible Procedure convtext(void (*outproc) (char ch), value v, char quote);

#ifdef __cplusplus
}
#endif


#endif
