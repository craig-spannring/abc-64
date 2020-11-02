/**
 * @file
 * 
 */    
#ifndef I3COM_h_9bf068a796da74195d816c1940bae143
#define I3COM_h_9bf068a796da74195d816c1940bae143

#include "b.h"
#include "bmem.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool      f_edit(value fname, intlet errline, literal kind, bool creating);
    Visible bool      cmdline(literal kind, bufadm *bp, int indent);
    Visible Procedure idelpos(value fname);
    Visible Procedure imovpos(value ofname, value nfname);

#ifdef __cplusplus
}
#endif


#endif
