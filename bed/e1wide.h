#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool narrow(environ *ep);
    Visible bool rnarrow(environ *ep);

    Visible bool widen(environ *ep, bool deleting);
    Visible bool extend(environ *ep);

#ifdef __cplusplus
}
#endif
