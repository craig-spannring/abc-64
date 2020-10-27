/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef DIR_h_e67f6a16bc15ed73144899ab374aab56
#define DIR_h_e67f6a16bc15ed73144899ab374aab56

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

#ifdef HAS_READDIR

#include <sys/dir.h>

#else /* !HAS_READDIR */

/*
 * "dir.h" voor de Atari ST  (Mark Williams C)
 */

#define MAXNAMLEN 31
#define MAXPATH 256

#define DIR struct _dir

struct _dir {
	int flags;
	char name[MAXNAMLEN];
};

struct direct {
	char d_name[MAXPATH];
};

Visible DIR *opendir();
Visible struct direct *readdir();
Visible Procedure closedir();

#endif /* !HAS_READDIR */

#ifdef __cplusplus
extern "C" }
#endif


#endif
