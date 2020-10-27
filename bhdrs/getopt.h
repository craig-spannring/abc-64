/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef GETOPT_h_4bfddd74b1110f3b7518cb1a808a377b
#define GETOPT_h_4bfddd74b1110f3b7518cb1a808a377b

#ifdef __cplusplus
extern "C" {
    #endif
    extern int opterr;	/* no error messages if zero */
extern int optopt;	/* option letter found */
extern int optind;	/* argv index of next argument */
extern char *optarg;	/* start of option argument */

extern int getopt();	/* returns option letter or '?' or EOF */

#ifdef __cplusplus
}
#endif


#endif
