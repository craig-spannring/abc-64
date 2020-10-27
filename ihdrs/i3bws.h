/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3BWS_h_17ce7ba390db9b6e8f0c801b3a3a63ee
#define I3BWS_h_17ce7ba390db9b6e8f0c801b3a3a63ee

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

extern char *bwsdir;
extern value ws_group;
extern bool groupchanges;
extern value curwskey;
extern value lastwskey;
extern value cur_ws;
#ifdef WSP_DIRNAME
value abc_wsname();
#endif
extern char *cur_dir; /* absolute path to current workspace */

#ifdef __cplusplus
extern "C" }
#endif


#endif
