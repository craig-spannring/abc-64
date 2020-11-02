#ifndef E1EDOC_h_38b87c74514dca70059f2229421de86c
#define E1EDOC_h_38b87c74514dca70059f2229421de86c


#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool      dofile(environ *ep, string filename, int linenumber, literal kind, bool creating, bool *changed);
    extern Visible bool      editdocument(environ *ep, bool bad_file);
    extern Visible bool      savequeue(value v, string filename);
    extern Visible bool      suspendabc(void);
    extern Visible Procedure clrenv(environ *ep);
    extern Visible Procedure dbmess(environ *ep);
    extern Visible Procedure dumpev(environ *ep, string m);
    extern Visible Procedure higher(environ *ep);

#ifdef __cplusplus
}
#endif


#endif
