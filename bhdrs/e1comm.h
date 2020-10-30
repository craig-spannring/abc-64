#ifndef E1COMM_h_489fa08f22bd1705e716ccc82d71cacd
#define E1COMM_h_489fa08f22bd1705e716ccc82d71cacd

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible Procedure abced_file(string filename, intlet errline, literal kind, bool creating, bool *changed);
    extern Visible Procedure initbed(void);
    extern Visible Procedure endbed(void);
    
#ifdef __cplusplus
}
#endif


#endif
