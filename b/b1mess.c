/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/* B error message handling */

/* All error messages are collected in a file, both to save data space
   and to ease translation to other languages.	The English version
   of the database can be recreated from the program sources by scanning
   for the pattern "MESS".  This is a macro whose first argument is
   the message number and whose second number is the message string;
   this macro expands to only the message number which is passed to
   the error routines.	The error routines then dig the message from
   the error message file, or just print the number if the file can't be
   opened.  There is also a way to pass a message that is determined
   at runtime.
*/

#include "b1mess.h"
#include "b.h"
#include "bmem.h"
#include "bobj.h"
#include "i3scr.h"
#include "i3err.h"
#include "port.h"

/* While we are reading the Messages file, we build an index.
   probe[k] contains the first message number found in block k.
   blocks are BUFSIZ in size. */

#define FILESIZE 22454 /* Approximated current size of Messages file */
#define MAXPROBE (10 + FILESIZE/BUFSIZ) /* Allow some growth */

Hidden short probe[MAXPROBE];
Hidden int nprobes= 1;

char *messbuf; /* used for messages with arguments */
Hidden char buf[MESSBUFSIZE];

Visible cstring getmess(int nr) {
	int    last;
	int    c;
	char  *cp= NULL;
	bool   is_new;
	int    block;
	long   ftell(FILE *);
	
	static int                last_nr= 0;
	static FILE* const        NOT_OPENED = ((FILE*)(-1));
	static const char* const  NO_MESSFILE = "*** Cannot find or read messages file; using numbers\n";
	static FILE              *messfp= NOT_OPENED;

	if (nr <= 0) 
		return nr == -1 ? "%s" : nr == -2 ? "%s%s" : "";
	if (messfp == NOT_OPENED) {
		if (messfile)
			messfp= fopen(messfile, "r");
		else
			messfp= NULL;
		if (messfp == NULL) {
			flushout();
			putserr(NO_MESSFILE);
			flusherr();
		}
	}
	if (nr == last_nr) {
		cp= strchr(buf, '\t');
		if (cp != NULL)
		    return cp+1;
	}
	if (messfp) {
		for (block= nprobes-1; block > 0; --block) {
			if (probe[block] <= nr)
				break;
		}
		is_new= block == nprobes-1;
		fseek(messfp, (long)block*BUFSIZ, 0);
		last= 0;
		while (last < nr) {
			if (is_new) block= ftell(messfp) / BUFSIZ;
			cp= buf;
			while ((c= getc(messfp)) != EOF && c != '\n') {
				if (cp >= buf + MESSBUFSIZE - 2) break;
				if (c != '\\')
					*cp= c;
				else {
					c= getc(messfp);
					if (c == EOF || c == '\n') break;
					switch (c) {
					case 'n': *cp= '\n'; break;
					case 'r': *cp= '\r'; break;
					case 't': *cp= '\t'; break;
					case 'b': *cp= '\b'; break;
					default: *cp++= '\\'; *cp= c; break;
					}
				}
				cp++;
			}
			*cp= '\0';
			if (c == EOF) break;
			last= atoi(buf);
			if (last <= 0)
				continue;
			if (is_new && block >= nprobes && nprobes < MAXPROBE) {
				probe[block]= last;
				nprobes= block+1;
			}
		}
		if (last == nr) {
			cp= strchr(buf, '\t');
			if (cp != NULL) {
				last_nr= nr;
				return cp+1;
			}
		}
	}
	sprintf(buf, " (message %d) ", nr);
	last_nr= 0;
	return buf;
}

Visible Procedure initmess(void) {
	messbuf= (char*) getmem(MESSBUFSIZE);
}

Visible Procedure endmess(void) {
#ifdef MEMTRACE
	freemem((ptr) messbuf);
#endif
}

/***************************************************************************/

Visible Procedure putmess(int m)
{
	putserr(getmess(m));
	flusherr();
}

#ifndef KEYS

Visible Procedure putSmess(int m, cstring s)
{
	putsSerr(getmess(m), s);
	flusherr();
}

Visible Procedure putDSmess(int m, int d, cstring s)
{
	putsDSerr(getmess(m), d, s);
	flusherr();
}

Visible Procedure put2Cmess(int m, char c1, char c2)
{
	puts2Cerr(getmess(m), c1, c2);
	flusherr();
}

#endif /* !KEYS */
