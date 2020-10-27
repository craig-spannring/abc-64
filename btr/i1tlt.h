/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I1TLT_h_1a82b7d7c21e62e7561d1efbda29f192
#define I1TLT_h_1a82b7d7c21e62e7561d1efbda29f192

#ifdef __cplusplus
extern "C" {
#endif

/* Private definitions for B texts, lists and tables */

typedef struct telita {
    HEADER; btreeptr root;
} a_telita, *telita;

#define Itemtype(v) (((telita) (v))->len) /* Itemtype */
#define Root(v) (((telita) (v))->root)
#define Tltsize(v) (Root(v) EQ Bnil ? 0 : Size(Root(v)))

#define Character(v)	((bool) (Type(v) EQ Tex && Tltsize(v) EQ 1))

#ifdef __cplusplus
extern "C" }
#endif


#endif
