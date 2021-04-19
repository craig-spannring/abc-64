#include "b.h"
#include "supr.h"
#include "bedi.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool      eqlines(nodeptr n1, nodeptr n2);
    Visible bool      nextline(pathptr *pp);
    Visible int       colno(enviro *ep);
    Visible int       linelen(nodeptr n);
    Visible int       lineno(enviro *ep);
    Visible Procedure oneline(enviro *ep);

#ifdef __cplusplus
}
#endif
