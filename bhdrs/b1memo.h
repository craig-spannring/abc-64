#ifndef B1MEMO_h_66f90d99bbdd71470fa0c1f4f4cb05da
#define B1MEMO_h_66f90d99bbdd71470fa0c1f4f4cb05da

#include "b.h"
#include "bmem.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Procedure regetmem(ptr *, unsigned syze);
extern Procedure freemem();
extern Procedure bufpush();
extern Procedure bufcpy();
extern Procedure bufreinit();
extern Procedure bufinit();
extern Procedure buffree();
extern Procedure bufncpy();

#ifdef __cplusplus
}
#endif

#endif
