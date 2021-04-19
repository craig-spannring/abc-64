#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool insguess(pathptr *pp, char c, enviro *ep);
    extern Visible bool mayinsert(nodeptr n, int ich, int s2, char c);
    extern Visible bool resuggest(enviro *ep, string *pstr, int alt_c);
    extern Visible bool soften(enviro *ep, string *pstr, int alt_c);

#ifdef __cplusplus
}
#endif
