/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1987. */

/*
 * B editor -- Save focus position.
 */

#include "e1spos.h"

#include "b.h"

#ifdef SAVEPOS

#include "b1memo.h"
#include "bedi.h"
#include "bobj.h"
#include "bfil.h"
#include "e1line.h"
#include "node.h"
#include "supr.h"
#include "bmem.h"

/*
 * Keep a simple database of file name vs. line number.
 * The database is kept in most-recently-used-first order.
 */

typedef struct pc { char *fname; int line; struct pc *next; } poschain;
typedef poschain *pos;

#define PNULL ((pos) NULL)

Hidden pos poshead= PNULL;

Hidden bool poschanges;

Hidden pos new_pos(char *fname, int line) {
	pos the_new_pos= (pos) getmem((unsigned) sizeof(poschain));
	the_new_pos->fname= (char *) savestr(fname);
	the_new_pos->line= line;
	the_new_pos->next= PNULL;
	return the_new_pos;
}

Hidden Procedure free_pos(pos filpos) {
	freestr(filpos->fname);
	freemem((ptr) filpos);
}

Hidden int del_pos(char *fname) {
	pos filpos= poshead;
	pos prev= PNULL;
	int line= 1;
	
	while (filpos != PNULL) {
		if (strcmp(fname, filpos->fname) == 0) {
			line= filpos->line;
			if (prev)
				prev->next= filpos->next;
			else
				poshead= filpos->next;
			free_pos(filpos);
			poschanges= Yes;
			break;
		}
		prev= filpos;
		filpos= filpos->next;
	}
	return line;
}

Hidden Procedure sav_pos(char *fname, int line) {
	pos the_new_pos;
	
	VOID del_pos(fname);
	the_new_pos= new_pos(fname, line);
	the_new_pos->next= poshead;
	poshead= the_new_pos;
	poschanges= Yes;
}

Visible Procedure initpos(void) {
	FILE *file;
	char *buffer;
	char *fname;
	int   line;
	pos   tail;
	pos   newpos;
	
	poshead= tail= PNULL;
	poschanges= No;
	file= fopen(posfile, "r");
	if (!file)
		return;
	while ((buffer= f_getline(file)) != NULL) {
		fname= (char *) getmem((unsigned) (strlen(buffer) + 1));

		if (sscanf(buffer, "%s\t%d", fname, &line) == 2) {
			if (F_exists(fname)) {
				newpos= new_pos(fname, line);
				if (!tail)
					poshead= tail= newpos;
				else {
					tail->next= newpos;
					tail= newpos;
				}
			}
		}
		freemem((ptr) fname);
		freemem((ptr) buffer);
	}
	fclose(file);
}

Hidden Procedure wripos(void) {
	FILE *fp;
	pos filpos;
	
	if (!poschanges)
		return;
	poschanges= No;
	if (poshead == PNULL) {
		unlink(posfile);
		return;
	}
	fp= fopen(posfile, "w");
	if (!fp)
		return;
	filpos= poshead;
	while (filpos != PNULL) {
		fprintf(fp, "%s\t%d\n", filpos->fname, filpos->line);
		filpos= filpos->next;
	}
	fclose(fp);
}

Visible Procedure endpos(void) {
	pos prev;

	wripos();
	while (poshead != PNULL) {
		prev= poshead;
		poshead= poshead->next;
		free_pos(prev);
	}
}

/* getpos() is called from editor */

Visible int getpos(char *fname) {
	pos filpos= poshead;
	
	while (filpos != PNULL) {
		if (strcmp(fname, filpos->fname) == 0)
			return filpos->line;
		filpos= filpos->next;
	}
	return 0; /* editor expects 0 as default */
}

/* savpos() is called from editor */

Visible bool savpos(char *fname, enviro *ep) {
	sav_pos(fname, lineno(ep) + 1);
  return 1;
}

/* delpos() is called from interpreter */

Visible Procedure delpos(char *fname) {
	VOID del_pos(fname);
}

/* movpos() is called from interpreter */

Visible Procedure movpos(char *ofname, char *nfname) {
	int n_line= del_pos(ofname);
	sav_pos(nfname, n_line);
}
	
#endif /* SAVEPOS */
