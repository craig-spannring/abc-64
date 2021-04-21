#ifndef I3FIL_h_f756b8848b6a14b0d179b7a9f926d0ce
#define I3FIL_h_f756b8848b6a14b0d179b7a9f926d0ce


#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure f_rename(value fname, value nfname);
	extern Visible Procedure f_delete(const char *file);
	extern Visible unsigned f_size(FILE *file);
	extern Visible Procedure f_close(FILE *usrfile);
	extern Visible bool f_interactive(FILE *file);
	extern Visible char *f_getline(FILE *file);
	extern Visible value new_fname(value name, literal type);
	extern Visible value mkabcname(char *name);

#ifdef __cplusplus
}
#endif


#endif
