/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef DIR_h_e67f6a16bc15ed73144899ab374aab56
#define DIR_h_e67f6a16bc15ed73144899ab374aab56

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1990. */

/*
 * Interface for MS-DOS version of UNIX directory access package.
 * (opendir, readdir, closedir).
 */

struct direct {
	char d_namlen;
	char d_name[13];
};

typedef char DIR;

Visible DIR *opendir();
Visible struct direct *readdir();
Visible Procedure closedir();

#ifdef __cplusplus
}
#endif


#endif
