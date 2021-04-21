/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

#include "b1file.h"

#include "b.h"
#include "b1memo.h"
#include "bfil.h"
#include "bmem.h"
#include "port.h"

Visible cstring permfile= PERMFILE;	/* saves links file name vs. abc name */
Visible cstring suggfile= SUGGFILE;	/* saves user suggestions */
Visible cstring posfile= POSFILE;	/* saves focus positions */
Visible cstring typesfile= TYPESFILE;	/* saves typecode's */
Visible cstring wsgroupfile= WSGROUPFILE; 
				/* saves links workspace name vs. abc name */

Visible cstring tempfile= TEMPFILE;	/* temporary file */
Visible cstring temp1file= TEMP1FILE;	/* another temporary file */

Visible Procedure free_path(const char* path) {
	if (path != NULL)
		freestr(path);
}

Visible Procedure endfile(void)
{
#ifdef MEMTRACE
	free_path(startdir);
	free_path(bwsdefault);
	free_path(messfile);
	free_path(helpfile);
	free_path(keysfile);
	free_path(buffile);
#endif
}

