#ifndef B1MESS_h_5a4aa7a43fda0600018cdc2c5a99dd0f
#define B1MESS_h_5a4aa7a43fda0600018cdc2c5a99dd0f

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure putmess(int m);
	extern Visible Procedure putSmess(int m, cstring s);
	extern Visible Procedure putDSmess(int m, int d, cstring s);
	extern Visible Procedure initmess(void);
	extern Visible Procedure endmess(void);
	extern Visible Procedure put2Cmess(int m, char c1, char c2);
	
	extern Visible Procedure pre_init(void);
	extern Visible Procedure init(void);
	extern Visible Procedure checkfileargs(int argc, char **argv);

	extern Visible Procedure abc(int argc, char **argv);


#ifdef __cplusplus
}
#endif



#endif
