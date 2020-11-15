/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3SCR_h_ffa7e82621c3216643ace1d1a0e8e49b
#define I3SCR_h_ffa7e82621c3216643ace1d1a0e8e49b

#include "b.h"
#include "i3typ.h"

#ifdef __cplusplus
extern "C" {
#endif

/* screen */

	extern Visible bool  interactive;
	extern Visible bool  rd_interactive;
	extern Visible value iname;	/* input name */
	extern Visible bool  outeractive;
	extern Visible bool  at_nwl;	/*Yes if currently at the start of an output line*/
	extern Visible bool  Eof;
	extern Visible FILE *ifile;	 	/* input file */
	extern Visible FILE *sv_ifile;		/* copy of ifile for restoring after reading unit */
	extern Visible bool io_exit;
	
	extern Visible Procedure flushout(void);
	extern Visible Procedure newline(void);
	extern Visible Procedure oline(void);
	extern Visible Procedure writ(value v);
	extern Visible Procedure writnewline(void);
	extern Visible Procedure wri(FILE *fp, value v, bool coll, bool outer, bool perm);
	extern Visible Procedure printnum(FILE *fp, value v);
	extern Visible char q_answer(int m, char c1, char c2, char c3);
	extern Visible bool is_intended(int m);
	extern Visible Procedure read_eg(loc l, btype t);
	extern Visible Procedure read_raw(loc l);
	extern Visible bool read_ioraw(value *v); /* returns Yes if end of input */
	extern Visible char *get_line(void);
	extern Visible Procedure redirect(FILE *of);
	extern Visible Procedure vs_ifile(void);
	extern Visible Procedure re_screen(void);
	extern Visible Procedure init_scr(void);
	extern Visible Procedure end_scr(void);
	extern Visible Procedure re_outfile(void);

#ifdef __cplusplus
}
#endif


#endif
