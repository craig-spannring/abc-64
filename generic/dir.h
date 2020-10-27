/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef DIR_h_e67f6a16bc15ed73144899ab374aab56
#define DIR_h_e67f6a16bc15ed73144899ab374aab56

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

/* Generic version, as basis for porting.
 * See Portability Guide (./PORTING.DOC) for details.
 */

#ifdef HAS_READDIR

#include <sys/dir.h>

#else /* !HAS_READDIR */

struct direct {
	char d_name[ /* some value */ ];
	/* other fields */
};

typedef /* whatever */ DIR;

Visible DIR *opendir();
Visible struct direct *readdir();
Visible Procedure closedir();

#endif /* !HAS_READDIR */

#ifdef __cplusplus
extern "C" }
#endif


#endif
