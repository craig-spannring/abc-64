/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef OSCONF_h_a41621bf8c2a47d884a0d1ae6d6f7bb1
#define OSCONF_h_a41621bf8c2a47d884a0d1ae6d6f7bb1

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

/* Operating system dependent ABC configuration */
/* This contains the things ../mkconfig.c needs */

#include <stdio.h>

typedef unsigned char literal;	/* to emphasize meaning only */

typedef short reftype;		/* type used for reference counts */
#define Maxrefcnt Maxintlet	/* Maxintlet is calculated in config.h */

#ifdef __cplusplus
}
#endif


#endif
