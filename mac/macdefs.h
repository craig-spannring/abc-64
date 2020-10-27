/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef MACDEFS_h_8e9ee480ca00bfaaa93852fedd26df06
#define MACDEFS_h_8e9ee480ca00bfaaa93852fedd26df06

#ifdef __cplusplus
extern "C" {
#endif
/* Useful #includes and #defines for programming a set of Unix
   look-alike file system access functions on the Macintosh. */

#include <Types.h>
#include <Files.h>

#include <ErrNO.h>
#include <Strings.h>

/* Macro to find out whether we can do HFS-only calls: */
#define FSFCBLen (* (short *) 0x3f6)
#define hfsrunning() (FSFCBLen > 0)

/* Universal constants: */
#define MAXPATH 256
#define TRUE 1
#define FALSE 0
#define NULL 0
#define EOS '\0'
#define SEP ':'

/* Call Macsbug: */
pascal void Debugger() extern 0xA9FF;

#ifdef __cplusplus
}
#endif


#endif
