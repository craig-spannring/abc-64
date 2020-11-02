/**
 * @file
 * 
 */    
#ifndef E1GRAM_h_6f34d6c61c60053692c07c29fec8b1e1
#define E1GRAM_h_6f34d6c61c60053692c07c29fec8b1e1

#include "b.h"
#include "bedi.h"
#include "tabl.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible bool issublist(int sym);
    Visible bool samelevel(int sym, int sym1);
    Visible bool allowed(path p, int sym);
    Visible int  nametosym(string str);
    Visible bool isinclass(int sym, struct classinfo *ci);
    
#ifdef __cplusplus
}
#endif


#endif
