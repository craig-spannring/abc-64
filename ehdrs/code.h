/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef CODE_h_f6df38462c69aa26a8cc45a543a7bb5c
#define CODE_h_f6df38462c69aa26a8cc45a543a7bb5c

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

extern char code_array[];
extern char invcode_array[];
extern int lastcode;

extern Procedure initcodes();

#define RANGE 128 /* ASCII characters are in {0 .. RANGE-1} */

#define Code(c) code_array[(unsigned int)c]
#define Invcode(code) invcode_array[code]

#ifdef __cplusplus
}
#endif


#endif
