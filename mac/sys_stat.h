/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef SYS_STAT_h_bd7eeb6c977ca10f315c3170ddade494
#define SYS_STAT_h_bd7eeb6c977ca10f315c3170ddade494

#ifdef __cplusplus
extern "C" {
    #endif
    struct stat {
	unsigned short st_mode;
	unsigned long st_size;
	unsigned long st_mtime;
};

#define S_IFMT	0170000l
#define S_IFDIR	0040000l
#define S_IFREG 0100000l
#define S_IREAD    0400
#define S_IWRITE   0200
#define S_IEXEC    0100

#ifdef __cplusplus
}
#endif


#endif
