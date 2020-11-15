/**
 * @file
 * 
 */    
#ifndef E1OUTP_h_3b4766302b10ba3e97bcb6ff8613e9f1
#define E1OUTP_h_3b4766302b10ba3e97bcb6ff8613e9f1

#include "b.h"
#include "supr.h"
#include "cell.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible int focy; /* Where the cursor must go */
	extern Visible int focx;
	
	extern Visible Procedure savefocus(environ *ep);
	extern Visible Procedure setfocus(cell *tops);
	extern Visible Procedure startactupdate(bool nofocus);
	extern Visible Procedure endactupdate(void);
	extern Visible Procedure outline(cell *p, int lineno) ;

#ifdef __cplusplus
}
#endif




#endif
