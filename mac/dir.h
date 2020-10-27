/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef DIR_h_e67f6a16bc15ed73144899ab374aab56
#define DIR_h_e67f6a16bc15ed73144899ab374aab56

#ifdef __cplusplus
extern "C" {
#endif
/*
 * "Dir.h" for the Macintosh.
 */

#define MAXNAMLEN 31
#define MAXPATH 256

#define DIR  struct _dir

struct _dir {
	long dirid;
	int nextfile;
};

struct direct {
	char d_name[MAXPATH];
};

DIR *opendir();
struct direct *readdir();
closedir();
#ifdef __cplusplus
}
#endif


#endif
