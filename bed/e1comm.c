/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Editor command processor.
 */

#include "e1comm.h"
#include "b.h"
#include "bedi.h"
#include "bcom.h"
#include "e1edoc.h"
#include "e1edit.h"
#include "e1deco.h"
#include "e1gram.h"
#include "e1node.h"
#include "e1save.h"
#include "e1scrn.h"
#include "e1spos.h"
#include "e1sugg.h"
#include "e1supr.h"
#include "i3err.h"
#include "node.h"
#include "supr.h"       /* for environ */
#include "tabl.h"
#include "port.h"
#include "b1grab.h"

#ifdef GFX
#include "bgfx.h"
#endif

Visible int doctype;
extern bool canceled;

Visible environ *tobesaved;
Visible string savewhere;

environ top_env, *top_ep;

Visible Procedure initbed(void) {
	top_ep= &top_env;

	savewhere = (string)NULL;
	tobesaved = (environ*)NULL;
	clrenv(top_ep);
#ifdef SAVEBUF
	top_ep->copybuffer = editqueue((string) buffile);
	if (top_ep->copybuffer)
		top_ep->copyflag = Yes;
#endif /* SAVEBUF */
}

Visible Procedure endbed(void) {
	environ *ep = tobesaved;

	tobesaved = (environ*)NULL;
		/* To avoid loops if saving is cancelled. */
	if (savewhere && ep) {
		if (ep->generation > 0) {
			save(ep->focus, savewhere);
#ifdef USERSUGG
			writesugg(ep->focus);
#endif /* USERSUGG */
		}
#ifdef SAVEBUF
		if (ep->copyflag)
			savequeue(ep->copybuffer, (string) buffile);
		else
			savequeue(Vnil, (string) buffile);
#endif /* SAVEBUF */
#ifdef SAVEPOS
		savpos(savewhere, ep);
#endif /* SAVEPOS */
	}
#ifdef SAVEBUF
	if (top_ep->copyflag)
		savequeue(top_ep->copybuffer, (string) buffile);
	else
		savequeue(Vnil, (string) buffile);
#endif /* SAVEBUF */
	Erelease(*top_ep);
}

Visible Procedure abced_file(string filename, intlet errline, literal kind, bool creating, bool *changed)
{
	environ *ep= top_ep;

#ifdef GFX
	if (gfx_mode != TEXT_MODE)
		exit_gfx();
#endif
	setindent(0);
	doctype= D_perm;
	dofile(ep, filename, errline, kind, creating, changed);
	endshow();
	top(&ep->focus);
	ep->mode = WHOLE;
	deltext(ep);
	if (!ep->copyflag) {
		release(ep->copybuffer);
		ep->copybuffer = Vnil;
	}
	if (canceled) {
		int_signal();
		canceled= No;
	}
}

Visible char *ed_line(literal kind, int indent) {
	char *buf= (char *) NULL;
	environ *ep= top_ep;

	if (kind == R_cmd)
		setroot(Imm_cmd);
	else if (kind == R_expr)
		setroot(Expression);
	else
		setroot(Raw_input);
	delfocus(&ep->focus);
	if (kind == R_cmd) {
		cmdprompt(CMDPROMPT);
		doctype= D_immcmd;
	}
	else if (kind == R_expr || kind == R_raw || kind == R_ioraw)
		setindent(indent);
	else
		setindent(0);
	if (kind != R_cmd) {
		doctype= D_input;
	}
	editdocument(ep, No);
	endshow();
	top(&ep->focus);
	ep->mode = WHOLE;
	if (!canceled)
		buf= senddoc(ep->focus);
	deltext(ep);

	if (canceled) {
		int_signal();
		canceled= No;
	}

	return buf;
}


