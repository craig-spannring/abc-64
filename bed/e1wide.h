#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool narrow(enviro *ep);
    Visible bool rnarrow(enviro *ep);

    Visible bool widen(enviro *ep, bool deleting);
    Visible bool extend(enviro *ep);

#ifdef __cplusplus
}
#endif
