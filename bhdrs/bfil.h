/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BFIL_h_6f305cb662512c611b442c7a09e0f9fa
#define BFIL_h_6f305cb662512c611b442c7a09e0f9fa

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

#ifdef KEYS
#define NEWKEYSFILE     "abc.key"
#endif

#define PERMFILE	"perm.abc"
#define SUGGFILE	"suggest.abc"
#define POSFILE		"position.abc"
#define TYPESFILE	"types.abc"
#define WSGROUPFILE	"wsgroup.abc"

#define TEMPFILE	"temp.abc"
#define TEMP1FILE	"temp1.abc"

#define DEFAULT_WS	"first" /* default name of startup workspace */
#define CENTRAL_WS      "abc"   /* default name of central workspace */

extern cstring permfile;
extern string suggfile;
extern string posfile;
extern string typesfile;
extern string wsgroupfile;

extern string tempfile;
extern string temp1file;

/* extern Procedure freepath(); */

char *f_getline(FILE *file);		/* return line from file including \n */

#ifdef __cplusplus
}
#endif


#endif
