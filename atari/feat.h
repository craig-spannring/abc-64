/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef FEAT_h_66f0dc77c4866f0719b6b6916e1685bd
#define FEAT_h_66f0dc77c4866f0719b6b6916e1685bd

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

#define EXT_RANGE	/* extend range of approximate arithmetic */
#define CLEAR_MEM	/* remove internal adm. before editing a howto */
#define SAVE_PERM	/* write perm env after each edit */

#define MAXHIST 21      /* One more than the number of UNDO's allowed. */

typedef literal reftype; /* type used for reference counts */
#define Maxrefcnt 255

#define SAVEBUF		/* Save Copy Buffer on file between edit sessions */
#define USERSUGG	/* Give suggestions for user-defined commands */
#define SAVEPOS		/* Save focus position between edit sessions */
#define RECORDING	/* [record] and [playback] commands */
#define SCROLLBAR	/* Show scroll bar if unit > screen */
#define SHOWBUF		/* Shows contents of copy buffer if locked */
#define HELPFUL		/* Print help blurb on ESC-? or ? */
#define GOTOCURSOR	/* enable [goto] operation */
#define CK_WS_WRITABLE  /* give warning if workspace is read-only */
#define TYPE_CHECK	/* do static type checking */

#ifdef __cplusplus
extern "C" }
#endif


#endif
