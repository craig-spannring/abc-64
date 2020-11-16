/**
 * @file
 * 
 */    
#ifndef I4FIL_h_a86c6348f0ba69c2370fb2bbd5491008
#define I4FIL_h_a86c6348f0ba69c2370fb2bbd5491008

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible value get_names(char *path, bool (*isabc) (char *path, char *name));
	extern Visible bool abcfile(char *path, char *name);
	extern Visible bool abcworkspace(char *path, char *name);
	extern Visible bool targetfile(value fname);
	extern Visible bool unitfile(value fname);
	extern Visible char *base_fname(value fname);
	extern Visible bool typeclash(value pname, value fname);

#ifdef __cplusplus
}
#endif




#endif
