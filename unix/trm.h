/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef TRM_h_b36e05a639a4c1d1dc8de08e1a0e9fdd
#define TRM_h_b36e05a639a4c1d1dc8de08e1a0e9fdd

#include "b.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

/*
 * Terminal capabilities.  These correspond to bits set by trmstart in its
 * parameter flags parameter.
 */

#define HAS_STANDOUT	1	/* Terminal has inverse video or underline */
#define CAN_SCROLL	2	/* Terminal can insert/delete lines */
#define CAN_OPTIMISE	4	/* Terminal can insert/delete characters */

/*
 * Error codes returned by trmstart.
 */

#define TE_OK		0	/* No errors */
#define TE_TWICE	1	/* Trmstart called again */
#define TE_NOTERM	2	/* $TERM not set or empty */
#define TE_BADTERM	3	/* $TERM not found in termcap database */
#define TE_DUMB		4	/* Terminal too dumb */
#define TE_NOTTY	5	/* Stdin not a tty or cannot open "/dev/tty" */
#define TE_NOMEM	6	/* Can't get enough memory */
#define TE_BADSCREEN	7	/* Bad $SCREEN */
#define TE_OTHER	8	/* This and higher are reserved errors */

/*
 * Possible modes; only standout is currently implemented.
 */

#define PLAIN		0	/* normal characters */
#define STANDOUT	1	/* in inverse video */
#define UNDERLINE	2	/* underlined */

    extern Visible int trmstart(int *plines, int *pcols, int *pflags);
    extern Visible Procedure trmend(void);
    extern Visible Procedure trmundefined(void);
    extern Visible Procedure trmsense(string sense, string format, int* py, int* px);
    extern Visible Procedure trmputdata(int yfirst, int ylast, int indent, cstring data, string mode);
    extern Visible Procedure trmscrollup(int yfirst, int ylast, int by);
    extern Visible Procedure trmsync(int y, int x);
    extern Visible Procedure trmbell(void);
    extern Visible Procedure trmshow(char *s);
    extern Visible int trminput(void);
    extern Visible int trmavail(void);
    extern Visible int trmsuspend(void);

    
#ifdef __cplusplus
}
#endif


#endif
