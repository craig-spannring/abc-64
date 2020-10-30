#ifndef B1MEMO_h_66f90d99bbdd71470fa0c1f4f4cb05da
#define B1MEMO_h_66f90d99bbdd71470fa0c1f4f4cb05da

#include "b.h"
#include "bmem.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Procedure regetmem(ptr *, unsigned syze);
    extern Procedure freemem(ptr p);
    extern Procedure bufpush(bufadm *bp, char c);
    extern Procedure bufcpy(bufadm *bp, char *s);
    extern Procedure bufreinit(bufadm *bp);
    extern Procedure bufinit(bufadm *bp);
    extern Procedure buffree(bufadm *bp);
    extern Procedure bufncpy(bufadm *bp, char *s, int len);

#ifdef __cplusplus
}
#endif

#endif
