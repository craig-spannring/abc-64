/**
 * @file
 * 
 */    
#ifndef E1INS2_h_d28639ff6529ce6b72aff2629adf2d91
#define E1INS2_h_d28639ff6529ce6b72aff2629adf2d91

#include "b.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool ins_char(enviro *ep, int c, int alt_c);
    extern Visible bool ins_newline(enviro *ep, bool reading_file);

#ifdef __cplusplus
}
#endif


#endif
