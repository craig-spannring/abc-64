/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I1TLT_h_1a82b7d7c21e62e7561d1efbda29f192
#define I1TLT_h_1a82b7d7c21e62e7561d1efbda29f192

#include "i1btr.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Private definitions for B texts, lists and tables */
struct gdb_hostile_telita { // The original def was not something GDB liked.
    HEADER;
    btreeptr root;
};
struct telita {
    literal type;
    reftype refcnt;
    intlet len FILLER_FIELD;
    btreeptr root;
};
typedef struct telita *telitaptr;
		
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_telita old_unused8[0];
static struct telita             new_unused8[0];
STATIC_CHECK(sizeof(old_unused8[0]) == sizeof(new_unused8[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_telita, type)   == offsetof(struct telita, type));
STATIC_CHECK(offsetof(struct gdb_hostile_telita, refcnt) == offsetof(struct telita, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_telita, len)    == offsetof(struct telita, len));
STATIC_CHECK(offsetof(struct gdb_hostile_telita, root)   == offsetof(struct telita, root));
#pragma GCC diagnostic pop

#define Itemtype(v) (((telitaptr) (v))->len) /* Itemtype */
#define Root(v) (((telitaptr) (v))->root)
#define Tltsize(v) (Root(v) == Bnil ? 0 : Size(Root(v)))

#define Character(v)	((bool) (Type(v) == Tex && Tltsize(v) == 1))

#ifdef __cplusplus
}
#endif


#endif
