/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef B_h_f3a79ec21e8ae24eef6ee57844d8f0cc
#define B_h_f3a79ec21e8ae24eef6ee57844d8f0cc

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TOKEN_MK(x, y)  x ## y
#define TOKEN_MK2(x, y) TOKEN_MK(x, y)
#define STATIC_CHECK(t) extern const int TOKEN_MK2(static_chkr_, __LINE__)[(t)?0:-1]
		
/* b.h: general */

/* The following are not intended as pseudo-encapsulation, */
/* but to emphasize intention. */

#ifndef __cplusplus
typedef int bool;
#endif
typedef char *string; /* Strings are always terminated with a char '\0'. */

#define Yes ((bool) 1)
#define No  ((bool) 0)

typedef short intlet;

#include "os.h"
#include "comp.h"
#include "feat.h"
#include "mach.h"

#define Forward
#define Visible
#define Porting
#define Hidden static
#ifdef NO_VOID
#define Procedure int
#else
#define Procedure void
#endif

#include "bvis.h" /* Public declarations for Visible Procedures */

/************************************************************************/
/*                                                                      */
/* Values                                                               */
/*                                                                      */
/* There are different modules for values, however all agree that       */
/* the first field of a value is its type, and the second its reference */
/* count. All other fields depend on the module.                        */
/*                                                                      */
/************************************************************************/

/*
 * "SMALL INTEGERS":
 *
 * When a "value" pointer has its low bit set, it is not a pointer.
 * By casting to int and shifting one bit to the right, it is converted
 * to its "int" value.  This can save a lot of heap space used for
 * small integers.
 * Sorry, you have to change this on machines with word rather than byte
 * addressing (maybe you can use the sign bit as tag).
 */

#define IsSmallInt(v) (((intptr_t)(v)) & 1)
#define SmallIntVal(v) (((intptr_t)(v) & ~1) / 2)
#define MkSmallInt(i) ( (value) (((intptr_t) i)*2 | 1) )
	/* (Can't use << and >> because their effect on negative numbers
		is not defined.) */
typedef struct gdb_hostile_value_ {HEADER; string *cts;} *gdb_hostile_value;
typedef struct value_ {
		literal type;            /* See "Types:" in b.h? */
		reftype refcnt;
		intlet len FILLER_FIELD; /* number of fields? */
		string *cts;
} *value;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_value_ old_unused0[0];
static struct value_             new_unused0[0];
STATIC_CHECK(sizeof(old_unused0[0]) == sizeof(new_unused0[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_value_, type)   == offsetof(struct value_, type));
STATIC_CHECK(offsetof(struct gdb_hostile_value_, refcnt) == offsetof(struct value_, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_value_, len)    == offsetof(struct value_, len));
STATIC_CHECK(offsetof(struct gdb_hostile_value_, cts)    == offsetof(struct value_, cts));
#pragma GCC diagnostic pop

								
#define Hdrsize (sizeof(struct value_)-sizeof(string))

		
#define Type(v) (IsSmallInt(v) ? Num : (v)->type)
#define Length(v) ((v)->len)
#define Refcnt(v) ((v)->refcnt)
#define Unique(v) ((v)->refcnt==1)

#define Dummy NULL
#define Dumval ((value) Dummy)
#define Vnil ((value) NULL)
#define Pnil ((value *) NULL)
#define PPnil ((value **) NULL)

#define Valid(v) ((v) != Vnil)

#define Ats(v) ((value *)&((v)->cts))
#define Str(v) ((string)&((v)->cts))

/* Types: */

#define Num '0'
#define Tex '"'
#define Com ','
#define Lis 'L'
#define Ran 'R'		/* doesn't belong here !!! */
#define Tab 'M'
#define ELT '}'

#define Is_text(v) (Type(v) == Tex)
#define Is_number(v) (Type(v) == Num)
#define Is_compound(v) (Type(v) == Com)
#define Is_list(v) (Type(v) == Lis || Type(v) == ELT || Type(v) == Ran)
#define Is_range(v) (Type(v) == Ran)
#define Is_table(v) (Type(v) == Tab || Type(v) == ELT)
#define Is_tlt(v) (Type(v)==Tex||Type(v)==Lis||Type(v)==Ran||Type(v)==Tab||Type(v)==ELT)
#define Is_ELT(v) (Type(v) == ELT)

/****************************************************************************/

value copy(value v);
extern bool still_ok;
extern bool mess_ok;
extern bool interactive;
extern bool rd_interactive;
extern bool testing_on;
extern bool terminated;
/* interrupts are polled; see comments in e1getc.c */
extern int pollcnt;
#define POLLDELAY 100
#define Interrupted() \
	((pollcnt > POLLDELAY ? pollinterrupt(), pollcnt= 0 : pollcnt++), interrupted)
extern bool interrupted;
extern bool can_interrupt;

#define MESS(nr, text) nr
#define GMESS(nr, text) getmess(nr)
string getmess(int nr);
extern char *messbuf;
#define MESSBUFSIZE 300

#define CONSOLE (FILE *) NULL

    
#ifdef __cplusplus
}
#endif


#endif
