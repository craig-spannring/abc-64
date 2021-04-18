#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool insguess(path *pp, char c, environ *ep);
    extern Visible bool mayinsert(nodeptr n, int ich, int s2, char c);
    extern Visible bool resuggest(environ *ep, string *pstr, int alt_c);
    extern Visible bool soften(environ *ep, string *pstr, int alt_c);

#ifdef __cplusplus
}
#endif
