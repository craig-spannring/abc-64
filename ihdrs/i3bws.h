/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3BWS_h_17ce7ba390db9b6e8f0c801b3a3a63ee
#define I3BWS_h_17ce7ba390db9b6e8f0c801b3a3a63ee

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

	extern Visible char *bwsdir;
	extern Visible value ws_group;		/* index workspaces */
	extern Visible bool groupchanges;		/* if Yes index has changed */
	extern Visible value curwskey;		/* special index key for cur_ws */
	extern Visible value lastwskey;		/* special index key for last_ws */
	extern Visible value cur_ws;		/* the current workspace */
	extern Visible char *cur_dir;               /* keeps track of the current directory */
	
#ifdef WSP_DIRNAME
	extern Visible value abc_wsname();
#endif
	extern Visible Procedure goto_ws(void);
	extern Visible Procedure lst_wss(void);
	extern Visible Procedure initbws(void);
	extern Visible Procedure endbws(void);
	extern Visible Procedure initworkspace(void);
	extern Visible Procedure endworkspace(void);
	extern Visible bool ckws_writable(int m);
	
#ifdef __cplusplus
}
#endif


#endif
