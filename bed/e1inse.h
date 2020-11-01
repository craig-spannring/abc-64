#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool soften(environ *ep, string *pstr, int alt_c);
    extern Visible bool mayinsert(node n, int ich, int s2, char c);
    extern Visible bool insguess(path *pp, char c, environ *ep);

#ifdef __cplusplus
}
#endif
