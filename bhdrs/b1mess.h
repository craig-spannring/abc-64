#ifndef B1MESS_h_5a4aa7a43fda0600018cdc2c5a99dd0f
#define B1MESS_h_5a4aa7a43fda0600018cdc2c5a99dd0f

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible Procedure putmess(int m);
    Visible Procedure putSmess(int m, string s);
    Visible Procedure putDSmess(int m, int d, string s);
    Visible Procedure initmess(void);
    Visible Procedure endmess(void);
    Visible Procedure put2Cmess(int m, char c1, char c2);
    
#ifdef __cplusplus
}
#endif



#endif
