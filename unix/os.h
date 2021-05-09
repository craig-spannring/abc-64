/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef OS_h_dc1c50628df97e44ec85840991ed328d
#define OS_h_dc1c50628df97e44ec85840991ed328d

#ifdef __cplusplus
extern "C" {
#ifdef GARBAGE_help_emacs_with_indentation
}
#endif
#endif
/* This file was generated and edited by the Setup command. */
/* To make lasting changes edit the files unix/os.h.gen and Setup, */
/* and run Setup again. */

/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

/* Operating system dependent ABC configuration */

#include <stdio.h>
#include <stdlib.h>

#include <math.h>	/* mathematical library, see math(3) */
#include <ctype.h>	/* character classifications, see ctype(3) */
#include <string.h>	/* string operations, like strlen(), see string(3) */
#include <sys/types.h>	/* basic system types, see stat(2) */
#include <unistd.h>	/* for access(2) modes, like R_OK; only used below */
#include <dirent.h>	/* for readdir(3), and so on */
#include <sys/stat.h>	/* file status, see stat(2) */



#include <time.h>
#include <sys/time.h>
#undef  HAS_FTIME	/* ftime() available */
#define HAS_GETTIMEOFDAY/* gettimeofday() available */
#define HAS_MKDIR	/* mkdir() and rmdir() available */
#define HAS_RENAME	/* rename() available */
#define HAS_SELECT	/* 4.2 BSD select() system call available */
#define HAS_READDIR	/* Berkeley style directory reading routines */
			/* opendir(), readdir() and closedir(); */
#undef  HAS_DIRECT
#ifndef HAS_DIRECT
#define direct dirent	/* newer versions of readdir use struct dirent */
#endif

/* define either one of the next two, or neither: */
#undef  HAS_GETWD	/* getwd() available */
#define HAS_GETCWD	/* getcwd() available instead */

/* is this a termio system (unix) */
#define TERMIO		

/* how to make a directory; some functions don't have a 'mode' parameter */
#define Mkdir(path)	(mkdir(path, DIRMODE))
#define DIRMODE 0777

/* access checks for files/directories */
#define F_readable(f)	(access(f, R_OK) == 0)
#define D_writable(f)	(access(f, W_OK) == 0)
#define F_exists(f)	(access(f, F_OK) == 0)
#define D_exists(f)	(access(f, F_OK) == 0)

/* Do we have to call a system routine to enable interrupts? (MSDOS only) */
#define ENABLE_INTERRUPT()

/* Can you lookahead in the system's input queue, and so can implement
 * trmavail() [trm.c] ?
 * There exists an implementation if TERMIO or HAS_SELECT has defined
 */
#define CANLOOKAHEAD		/* don't change this one */
#ifndef TERMIO
#ifndef HAS_SELECT
#undef CANLOOKAHEAD
/* if you do not define it here, you have to enable keyboard interrupts
 * in setttymode() [trm.c]
 */
#endif
#endif

#ifdef KEYS
/* do we know the keyboard codes ? */
#undef KNOWN_KEYBOARD
#endif /* KEYS */

#ifdef __cplusplus
}
#endif


#endif
