/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef PORT_h_7dd2435b707d0c07dd49505bed35122d
#define PORT_h_7dd2435b707d0c07dd49505bed35122d

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

/* externals of which the definitions are in a port directory */

Visible bool ed_file(char *editor, char *fname, int line);            /* edit.c */

Visible Procedure initfile(void);      /* file.c */
Visible char *makepath(const char *path1, const char *path2);
Visible int Chdir(char *path);

extern char *startdir;
extern char *bwsdefault;
extern char *messfile;
extern char *helpfile;
extern char *keysfile;
extern char *buffile;

#define BWSNAME		"abc"
#define MESSFILE	"abc.msg"
#define KEYSFILE	"abc.key"
#define HELPFILE	"abc.hlp"
#define BUFFILE		"copybuf.abc"
#define FORMAT_KEYSFILE "abc%s.key"    /* abc$TERM.key */

Visible cstring reprchar(int c);              /* keys.c */
#ifndef CANLOOKAHEAD
extern char intrchar;
#endif
Visible Procedure addspeckeys(void);
/* extern struct tabent deftab[];  in getc.h */

extern char *OPTbwsdir;                /* main.c */
extern char *OPTworkspace;
extern char *OPTcentral;
extern char *OPTeditor;
extern bool OPTslowterminal;

extern int abc_todo;
#define abcProper       1             /* run ABC normally */
#define abcioInput      2             /* run abc -i (input a table) */
#define abcioOutput     3             /* run abc -o (output a table) */
#define abcioList       4             /* run abc -l (list how-to's) */
#define abcioPack	7	      /* run abc -p (pack workspace) */
#define abcUnpack	8	      /* run abc -u (unpack workspace) */
#define abcioWSrecover  5             /* run abc -r (recover a workspace) */
#define abcioGRrecover  6             /* run abc -x (recover ws parent) */

Visible int getseed(void);                 /* os.c */
Visible Procedure getdatetime(int *year, int *month, int *day,
			      int *hour, int *minute, int *sec,
			      long *fraction, long *units);
Visible bool is_path(char*);
Visible bool is_abspath(char*);
Visible bool is_directory(char *dir, char *name);

extern bool intrptd;                 /* sig.c */
Visible Procedure initsig(void);

Visible Procedure abc_usage(void);       /* usage.c */

#ifdef __cplusplus
}
#endif


#endif
