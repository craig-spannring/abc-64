#include "b.h"
#include "supr.h"
#include "bedi.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool      eqlines(node n1, node n2);
    Visible bool      nextline(path *pp);
    Visible int       colno(environ *ep);
    Visible int       linelen(node n);
    Visible int       lineno(environ *ep);
    Visible Procedure oneline(environ *ep);

#ifdef __cplusplus
}
#endif
