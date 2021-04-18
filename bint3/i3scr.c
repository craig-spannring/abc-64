/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* B input/output handling */

#include "i3scr.h"

#include "b.h"
#include "b1memo.h"
#include "b1mess.h"
#include "b1outp.h"
#include "bcom.h"
#include "bint.h"
#include "bmem.h"
#include "bobj.h"
#include "bcom.h"
#include "e1getc.h"
#include "i1nua.h"
#include "i1tex.h"
#include "i2nod.h"
#include "i2gen.h"
#include "i2par.h"
#include "i2syn.h"
#include "i3com.h"
#include "i3loc.h"
#include "i3typ.h"
#include "i3env.h"
#include "i3fil.h"
#include "i3in2.h"
#include "i3scr.h"
#include "i3err.h"
#include "b1grab.h"

Visible bool interactive;
Visible bool rd_interactive;
Visible value iname= Vnil;	/* input name */

Hidden FILE *outfile;           /* may be reset in re_outfile() */
Visible bool outeractive;

Visible bool at_nwl= Yes;	/*Yes if currently at the start of an output line*/
Hidden bool last_was_text= No;	/*Yes if last value written was a text*/

Visible bool Eof;
Visible FILE *ifile;	 	/* input file */
Visible FILE *sv_ifile;		/* copy of ifile for restoring after reading unit */

Forward Hidden Procedure dowri(value v, int flags);
Forward Hidden bool fileline(FILE *fp, bufadm *bp);
Forward Hidden Procedure q_mess(int m, char c1, char c2);

Hidden int intsize(value v) {
	value s= size(v); int len=0;
	if (large(s)) interr(MESS(3800, "value too big to output"));
	else len= intval(s);
	release(s);
	return len;
}

/******************************* Output *******************************/

Visible Procedure flushout(void) {
	doflush(outfile);
}

Visible Procedure newline(void) {
	putchr(outfile, '\n');
	flushout();
	at_nwl= Yes;
}

Visible Procedure oline(void) {
	if (!at_nwl) newline();
}

/************ interpreter execution output *******************************/

Visible Procedure writ(value v) {
	wri(outfile, v, No, Yes, No);
}

Visible Procedure writnewline(void) {
	newline();
	pollinterrupt();
}

Hidden char *outbuf= (char*)NULL;
Hidden char *p_outbuf, *q_outbuf;

Hidden Procedure initoutbuf(void) {
	if (outbuf == NULL) {
		int lenbuf = getwinwidth() * 5;
		/* interrupt checking is done at least after 5 full lines */
		outbuf = (char *) getmem((unsigned) lenbuf+1);
		q_outbuf = outbuf + lenbuf;
	}
	p_outbuf= outbuf;
}

Hidden Procedure writoutbuf(void) {
	if (still_ok) {
		*p_outbuf= '\0';
		c_putstr(outbuf);
		c_flush();
		pollinterrupt();
	}
	p_outbuf= outbuf;
}

Hidden Procedure push_ch(char c) {
	*p_outbuf++= c;
	if (p_outbuf == q_outbuf) {
		writoutbuf();
	}
}

/****************************************************************************/

Hidden FILE *ofile; 

Hidden Procedure put_ch(char c) {
	putc(c, ofile);
}

/****************************************************************************/


/* states bits, see below */

#define PERM  1
#define OUTER 2
#define COLL  4

Hidden Procedure (*outproc)(char c);

#define Push_sp(perm) {if (!perm) (*outproc)(' ');}

Visible Procedure wri(FILE *fp, value v, bool coll, bool outer, bool perm)
{
	int flags = 0;

	if (perm) flags |= PERM;
	if (outer) flags |= OUTER;
	if (coll) flags |= COLL;

	if (fp == CONSOLE) {
		initoutbuf();
		ofile = CONSOLE;
		outproc = push_ch;
	}
	else {
		ofile = fp;
		outproc = put_ch;
	}
	
	dowri(v, flags);

	if (fp == CONSOLE) {
		writoutbuf();
	}
	else {
		VOID fflush(fp);
	}

	at_nwl= No;
}

Hidden bool lwt;

/*
 * printnum(f, v) writes a number v on file f in such a way that it
 * can be read back identically.
 */

Visible Procedure printnum(FILE *fp, value v) {
	if (Approximate(v)) {
		app_print(fp, (real) v);
		return;
	}
	if (Rational(v) && Denominator((rational)v) != int_1) {
		int i = Roundsize(v);
		fputs(convnum((value)Numerator((rational)v)), fp);
		if (i > 0) {
			/* The assumption here is that in u/v, the Roundsize
			   of the result is the sum of that of the operands. */
			putc('.', fp);
			do putc('0', fp); while (--i > 0);
		}
		putc('/', fp);
		v = (value) Denominator((rational)v);
	}
	fputs(convnum(v), fp);
}

Hidden Procedure dowri(value v, int flags)
{
	int perm;

	if (!still_ok) return;
	perm= flags&PERM;
	if ((flags&OUTER) && !at_nwl &&
	    (!Is_text(v) || !last_was_text) &&
	    (!Is_compound(v) || (flags&COLL) == 0)) {
		(*outproc)(' ');
	}
	lwt= No;
	if (Is_number(v)) {
		if (perm) printnum(ofile, v);
		else {
			string cp= convnum(v);
			while (*cp && !Interrupted()) (*outproc)(*cp++);
		}
	}
	else if (Is_text(v)) {
		convtext(outproc, v, flags&OUTER ? '\0' : '"');
		lwt= (flags&OUTER);
	}
	else if (Is_compound(v)) {
		intlet k, len= Nfields(v);

		if ((flags&COLL) == 0) (*outproc)('(');
		for (k=0; k<len && !Interrupted(); k++) {
			dowri(*Field(v, k), perm);
			if (!Lastfield(k)) {
				(*outproc)(',');
				Push_sp(perm);
			}
		}
		if ((flags&COLL) == 0) (*outproc)(')');
	}
	else if (Is_list(v) || Is_ELT(v)) {
		(*outproc)('{');
#ifndef RANGEPRINT
		if (perm && is_rangelist(v)) {
			value vm;
			dowri(vm=min1(v), perm);
			release(vm);
			(*outproc)('.'); (*outproc)('.');
			dowri(vm=max1(v), perm);
			release(vm);
		}
		else {
			value i, s, vi;
			relation c;
			
			i= copy(one); s= size(v);
			while((c= numcomp(i, s)) <= 0 && !Interrupted()) {
				vi= item(v, i);
				dowri(vi, perm);
				if (c < 0) {
					(*outproc)(';');
					(*outproc)(' ');
				}
				release(vi);
				i= sum(vi=i, one);
				release(vi);
			}
			release(i); release(s);
		}
#else /* RANGEPRINT */
		if (is_rangelist(v)) {
			value vm;
			dowri(vm=min1(v), perm);
			release(vm);
			(*outproc)('.'); (*outproc)('.');
			dowri(vm=max1(v), perm);
			release(vm);
		}
		else if (!perm) {
			value i, s, vi, lwb, upb;
			bool first= Yes;
			i= copy(one); s= size(v);
			while (numcomp(i, s) <= 0 && !Interrupted()) {
				vi= item(v, i);
				if (first) {
					lwb= copy(vi);
					upb= copy(vi);
					first= No;
				}
				else if (is_increment(vi, upb)) {
					release(upb);
					upb= copy(vi);
				}
				else {
					dowri_vals(lwb, upb);
					(*outproc)(';');
					(*outproc)(' ');
					release(lwb); release(upb);
					lwb= copy(vi); upb= copy(vi);
				}
				release(vi);
				i= sum(vi=i, one);
				release(vi);
			}
			if (!first) {
				dowri_vals(lwb, upb);
				release(lwb); release(upb);
			}
			release(i); release(s);
		}
		else {
			value ve; int k, len= intsize(v);
			for (k=0; k<len && !Interrupted(); k++) {
				dowri(ve= thof(k+1, v), perm);
				release(ve);
				if (k < len - 1) {
					(*outproc)(';');
					Push_sp(perm);
				}
			}
		}
#endif
		(*outproc)('}');
	}
	else if (Is_table(v)) {
		int k, len= intsize(v);
		(*outproc)('{');
		for (k=0; k<len && !Interrupted(); k++) {
			(*outproc)('[');
			dowri(*key(v, k), COLL | perm);
			(*outproc)(']');
			(*outproc)(':');
			Push_sp(perm);
			dowri(*assoc(v, k), perm);
			if (k < len - 1) {
				(*outproc)(';');
				Push_sp(perm);
			}
		}
		(*outproc)('}');
	}
	else {
		if (testing_on) {
			(*outproc)('?');
			(*outproc)(Type(v));
			(*outproc)('?');
		}
		else syserr(MESS(3801, "writing value of unknown type"));
	}
	last_was_text= lwt;
	if (interrupted && ofile != CONSOLE)
	        clearerr(ofile); /* needed for MSDOS */
}

#ifdef RANGEPRINT
Hidden Procedure dowri_vals(l, u)
     value l, u;
{
	if (!still_ok) return;
	if (compare(l, u) == 0)
		dowri(l, 0);
	else if (is_increment(u, l)) {
		dowri(l, 0);
		(*outproc)(';');
		(*outproc)(' ');
		dowri(u, 0);
	}
	else {
		dowri(l, 0);
		(*outproc)('.'); (*outproc)('.');
		dowri(u, 0);
	}
}
#endif /* RANGEPRINT */

/***************************** Input ****************************************/

/* Read a line; EOF only allowed if not interactive, in which case eof set */
/* Returns the line input                                                  */

#define Mixed_stdin_file (!rd_interactive && sv_ifile == stdin)

Hidden bufadm i_buf, o_buf;
extern bool i_looked_ahead;

Hidden char *read_line(/*literal*/ interp_to_ed_cmd kind, bool should_prompt, bool *eof)
{
	bufadm *bp= (kind == R_cmd && ifile == sv_ifile) ? &i_buf : &o_buf;
	FILE *fp= (kind == R_cmd || kind == R_ioraw) ? ifile : stdin;
	
	bufreinit(bp);
	*eof= No;
	
	if ((kind == R_expr || kind == R_raw)
	    && Mixed_stdin_file && i_looked_ahead)
	{
		/* e.g. "abc <mixed_commands_and_input_for_READs_on_file" */
		/* ilev looked_ahead for command following suite */
		/* and ate a line meant for a READ command */
		bufcpy(bp, i_buf.buf);
		i_looked_ahead= No;
	}
	else if (!should_prompt) {
		if (!fileline(fp, bp))
			*eof= Yes;
	}
	else if (cmdline(kind, bp, outfile == CONSOLE ? getwincol() : 0)) {
		if (outeractive) at_nwl= Yes;
	}
	return bp->buf;
}

#define LINESIZE 200

Hidden bool fileline(FILE *fp, bufadm *bp) {
	char line[LINESIZE];
	char *pline;

	for (;;) {
		pline= fgets(line, LINESIZE, fp);
		if (pline == NULL) {
			bufcpy(bp, "\n");
			if (*(bp->buf) == '\n')
				return No;
			clearerr(fp);
			return Yes;
		}
		bufcpy(bp, line);
		if (strchr(line, '\n') != NULL)
			return Yes;
	}
}

Hidden Procedure init_read(void) {
	bufinit(&i_buf);
	bufinit(&o_buf);
	bufcpy(&o_buf, "\n");
	tx= (txptr) o_buf.buf;
}

#ifdef MEMTRACE
Hidden Procedure end_read() {
	buffree(&i_buf);
	buffree(&o_buf);
}
#endif

/****************************************************************************/

#define ANSWER		MESS(3802, "*** Please answer with '%c' or '%c'\n")
#define JUST_YES_OR_NO	MESS(3803, "*** Just '%c' or '%c', please\n")
#define LAST_CHANCE	MESS(3804, "*** This is your last chance. Take it. I really don't know what you want.\n    So answer the question\n")
#define NO_THEN		MESS(3805, "*** Well, I shall assume that your refusal to answer the question means '%c'!\n")

/* Rather over-fancy routine to ask the user a question */
/* Will anybody discover that you're only given 4 chances? */

Visible char q_answer(int m, char c1, char c2, char c3) {
	char   answer;
	intlet attempt;
	txptr  tp;
	bool   eof;
	
	if (!interactive)
		return c1;
	if (outeractive)
		oline();
	for (attempt= 1; attempt<=4; attempt++){
		if (attempt == 1 || attempt == 3)
			q_mess(m, c1, c2);
		tp= (txptr) read_line(R_answer, Yes, &eof);
		if (interrupted) {
			interrupted= No;
			if (c3 == '\0') {
				still_ok= Yes;
				q_mess(NO_THEN, c2, c1);
				break;
			}
			else {
				return c3;
			}
		}
		skipsp(&tp);
		answer= Char(tp);
		if (answer == c1)
			return c1;
		if (answer == c2)
			return c2;
		if (outeractive)
			oline();
		if (attempt == 1)
			q_mess(ANSWER, c1, c2);
		else if (attempt == 2)
			q_mess(JUST_YES_OR_NO, c1, c2);
		else if (attempt == 3)
			q_mess(LAST_CHANCE, c1, c2);
		else 
			q_mess(NO_THEN, c2, c1);
	} /* end for */
	return c2;
}

Hidden Procedure q_mess(int m, char c1, char c2) {
	put2Cmess(m, c1, c2);
	flusherr();
}

Visible bool is_intended(int m) {
	char c1, c2;

#ifdef FRENCH
	c1= 'o'; c2= 'n';
#else /* ENGLISH */
	c1= 'y'; c2= 'n';
#endif
	return q_answer(m, c1, c2, (char)'\0') == c1 ? Yes : No;
}

#define EG_EOF		MESS(3806, "End of input encountered during READ command")
#define RAW_EOF		MESS(3807, "End of input encountered during READ t RAW")
#define EG_INCOMP	MESS(3808, "type of expression does not agree with that of EG sample")
#define TRY_AGAIN	MESS(3809, "*** Please try again\n")

/* Read_eg uses evaluation but it shouldn't.
   Wait for a more general mechanism. */

Visible Procedure read_eg(loc l, btype t) {
	context c; parsetree code;
	parsetree r= NilTree; value rv= Vnil; btype rt= Vnil;
	envtab svprmnvtab= Vnil;
	txptr fcol_save= first_col, tx_save= tx;
	do {
		still_ok= Yes;
		sv_context(&c);
		if (cntxt != In_read) {
			release(read_context.howtoname);
			sv_context(&read_context);
		}
		svprmnvtab= prmnvtab == Vnil ? Vnil : prmnv->tab;
		/* save scratch-pad copy because of following setprmnv() */
		setprmnv();
		cntxt= In_read;
		first_col= tx= (txptr) read_line(R_expr, rd_interactive, &Eof);
		if (still_ok && Eof) interr(EG_EOF);
		if (!rd_interactive) {
			if (sv_ifile == stdin)
				f_lino++;
			else
				i_lino++;
		}
		rt= Vnil;
		if (still_ok) {
			findceol();
			r= expr(ceol);
			if (still_ok) fix_nodes(&r, &code);
			rv= evalthread(code); release(r);
			if (still_ok) rt= valtype(rv);
		}
		if (svprmnvtab != Vnil) {
			prmnvtab= prmnv->tab;
			prmnv->tab= svprmnvtab;
		}
		if (still_ok) must_agree(t, rt, EG_INCOMP);
		set_context(&c);
		release(rt);
		if (!still_ok && rd_interactive && !interrupted)
			putmess(TRY_AGAIN);
	} while (!interrupted && !still_ok && rd_interactive);
	if (still_ok) put(rv, l);
	first_col= fcol_save;
	tx= tx_save;
	release(rv);
}

Visible Procedure read_raw(loc l) {
	value r; bool eof;
	txptr text= (txptr) read_line(R_raw, rd_interactive, &eof);
	if (still_ok && eof)
		interr(RAW_EOF);
	if (!rd_interactive) {
		if (sv_ifile == stdin)
			f_lino++;
		else
			i_lino++;
	}
	if (still_ok) {
		txptr rp= text;
		while (*rp != '\n') rp++;
		*rp= '\0';
		r= mk_text(text);
		put(r, l);
		release(r);
	}
}

Visible bool io_exit;

Visible bool read_ioraw(value *v) { /* returns Yes if end of input */
	txptr text, rp;
	bool eof;
	
	*v= Vnil;
	io_exit= No;
	text= (txptr) read_line(R_ioraw, rd_interactive, &eof);
	if (eof || interrupted || !still_ok)
		return Yes;
	rp= text;
	while (*rp != '\n')
		rp++;
	*rp= '\0';
	if (strlen(text) > 0 || !io_exit)
		*v= mk_text(text);
	return io_exit;
}

Visible char *get_line(void) {
	bool should_prompt=
		interactive && ifile == sv_ifile;
	return read_line(R_cmd, should_prompt, &Eof);
}

/******************************* Files ******************************/

Visible Procedure redirect(FILE *of) {
	static bool woa= No, wnwl= No;	/*was outeractive, was at_nwl */
	ofile= of;
	if (of == stdout) {
		outeractive= woa;
		at_nwl= wnwl;
	} else {
		woa= outeractive; outeractive= No;
		wnwl= at_nwl; at_nwl= Yes;
	}
}

Visible Procedure vs_ifile(void) {
	ifile= sv_ifile;
}

Visible Procedure re_screen(void) {
	sv_ifile= ifile;
	interactive= f_interactive(ifile);
	Eof= No;
}

/* initscr is a reserved name of CURSES */
Visible Procedure init_scr(void) {
	outeractive= f_interactive(stdout);
	outfile=(stdout); /* sp 20010221 */
	rd_interactive= f_interactive(stdin);
	init_read();
}

Visible Procedure end_scr(void) {
#ifdef MEMTRACE
	end_read();
	if (outbuf != NULL) freemem((ptr) outbuf);
	    /* note: getmem() can't be done in init_scr(),
             * because we have to know the window size first */
#endif
}

extern bool vtrmactive;

/* interpeter output to console (via vtrm) if stdout tty and vtrmactive */

Visible Procedure re_outfile(void) {
	if (outeractive && vtrmactive)
	  outfile = CONSOLE;
}
