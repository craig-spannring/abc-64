/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BOBJ_h_945555dcedb9ec8701ff4cfb11761611
#define BOBJ_h_945555dcedb9ec8701ff4cfb11761611

#include "b.h"
#include "i1num.h"

#ifdef __cplusplus
extern "C" {
#ifdef GARBAGE_help_emacs_with_indentation
}
#endif
#endif


/****************************** general ******************************/

typedef int relation; /* < 0, == 0, > 0 */
relation compare(value v, value w);

/*************************************************************************/


/// Create a new value object on the heap
value grab(NodeTypeT type, intlet len);
	
unsigned tltsyze(literal type, intlet len, int *nptrs);
unsigned numsyze(intlet len, int *nptrs);
unsigned ptnsyze(intlet len, int *nptrs);

double hash(value v);

bool is_abcname(value name);

/****************************** Texts ******************************/

bool character(value v);

value mkchar(char c);
value mk_text(cstring s);
char charval(value v);
char ncharval(int n, value v);
string strval(value v);
string sstrval(value v);

value concat(value tleft, value tright);
value behead(value t, value before);
value curtail(value t, value after);
value repeat(value t, value n);

value stripped(value t);
value split(value t);
value upper(value t);
value lower(value t);

value adjleft(value v, value w);
value centre(value v, value w);
value adjright(value v, value w);

value convert(value v, bool coll, bool outer);

/****************************** Numbers ******************************/

/* Predicates */
bool integral(value v);	    /* is the value an integer? */
bool large(value v);	    /* can a number be represented by a C int? */
#ifdef RANGEPRINT
bool is_increment();	/* a = b+1 ? */
#endif

/* Constants */
#define zero MkSmallInt(0)
#define one MkSmallInt(1)

/* Conversion of abstract values to concrete objects */
double numval(value v);     /* numeric value of any number */
int intval(value v);        /* numeric value of integral number */
int propintlet(int i);    /* checks int for fitting in intlet */
cstring convnum(value v);    /* character string approximation of any number */
relation numcomp(value u, value v);  /* comparison of two numbers: yields -1, 0 or 1 */
double numhash(value v);    /* hashes any abstract number to a 'double' */

/* Conversion of concrete objects to abstract numbers */
value numconst(value v);    /* string argument */
value mk_integer(int i);  /* int argument */

/* Functions on numbers */
value sum(value u, value v);
value diff(value u, value v);
value negated(value u);
value prod(value u, value v);
value quot(value u, value v);
value floor_f(value u);
value ceil_f(value u);
value round1(value u);
value round2(value n, value v);
value vmod(value u, value v);
value vpower(value u, value v);
value absval(value);
value signum(value u);
value numerator(value);
value denominator(value);
value approximate(value);
value vrandom(void);
value root1(value);
value sin1(value);
value cos1(value);
value tan1(value);
value arctan1(value);
value angle1(value u, value v);
value sin2(value u, value v);
value cos2(value u, value v);
value tan2(value u, value v);
value arctan2(value u, value v);
value angle2(value c, value u, value v);
value radius(value u, value v);
value vexp1(value);
value vlog1(value);
value root2(value u, value v);
value vlog2(value u, value v);
value vpi(void);
value e_natural(void);
value nowisthetime(void);
value exactly(value v);
bool exact(value v);

/****************************** Compounds ******************************/
#define Nfields(c) Length(c)
#define Field(c, i) ((Ats(c)+(i)))
#define k_Overfields for (k= 0; k < len; k++)
#define Lastfield(k) ((k) == len-1)

#define mk_compound(len) grab(Com, len)

/****************************** Lists ******************************/
value mk_range(value v1, value v2);
bool is_rangelist(value v);

Visible Procedure insert(value v, value *pl);
Visible Procedure vremove(value v, value *pl);

/****************************** Tables ******************************/

value keys(value t);
bool in_keys(value k, value t);
value associate(value t, value k);

Visible Procedure replace(value a, value *pt, value k);
/* Procedure delete(); */

value* adrassoc(value t, value k);
value* key(value v, intlet k);
value* assoc(value v, intlet k);

/****************************** Texts, Lists, and Tables *******************/
value mk_elt(void);

bool in(value e, value t);

value size(value t);
value size2(value e, value t);
value min1(value t);
value min2(value e, value t);
value max1(value t);
value max2(value e, value t);
#ifdef B_COMPAT
value th_of();
#endif
value thof(int k, value v);
value item(value v, value num);
value choice(value);

int length(value v); /* The same as size, temporary until part2 is written in B */
bool empty(value v); /* whether #v=0: also temporary */




#ifdef __cplusplus
}
#endif


#endif
