/**
 * @file
 * 
 */    
#ifndef E1SPOS_h_f1292d2572f8d3ccdcebc17934ef317c
#define E1SPOS_h_f1292d2572f8d3ccdcebc17934ef317c

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

Visible Procedure initpos(void);
Visible Procedure endpos(void);
Visible int getpos(char *fname);
Visible bool savpos(char *fname, environ *ep);
Visible Procedure delpos(char *fname);
Visible Procedure movpos(char *ofname, char *nfname);

#ifdef __cplusplus
}
#endif


#endif
