/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

#include "b.h"
#include "b1mess.h"
#include "bint.h"
#include "bmem.h"
#include "bobj.h"
#include "i2par.h"
#include "i3scr.h"
#include "i3sou.h"
#include "i4bio.h"
#include "i4inp.h"
#include "i4grp.h"
#include "i4lis.h"
#include "i4pack.h"
#include "i4out.h"
#include "i4rec.h"
#include "port.h"


Visible Procedure abcio(int type, char *tabname)
{
	sv_ifile= ifile= stdin;
	
	switch (type) {
		case abcioInput:
			abcinput(tabname);
			break;
		case abcioOutput:
			abcoutput(tabname);
			break;
		case abcioList:
			abclist(stdout);
			break;
 		case abcioPack:
 			abcpack(stdout);
 			break;
		case abcioWSrecover:
			if (!ws_recovered)
				rec_workspace();
			break;
		case abcioGRrecover:
			if (!gr_recovered)
				rec_wsgroup();
			break;
	}
}

Visible Procedure bioerr(int m) {
	putmess(m);
}

Visible Procedure bioerrV(int m, value v) {
	putSmess(m, strval(v));
}
