/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GETOPT_h_4bfddd74b1110f3b7518cb1a808a377b
#define GETOPT_h_4bfddd74b1110f3b7518cb1a808a377b

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
    #endif
    extern int opterr;	/* no error messages if zero */
extern int optopt;	/* option letter found */
extern int optind;	/* argv index of next argument */
extern char *optarg;	/* start of option argument */

#ifdef __cplusplus
}
#endif


#endif
