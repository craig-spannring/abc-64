/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BOBJ_h_945555dcedb9ec8701ff4cfb11761611
#define BOBJ_h_945555dcedb9ec8701ff4cfb11761611

#include "b.h"
#include "i1num.h"

#ifdef __cplusplus
extern "C" {
#endif


/****************************** general ******************************/

typedef int relation; /* < 0, == 0, > 0 */
relation compare(value v, value w);

/*************************************************************************/

value grab(literal type, intlet len);
unsigned tltsyze(literal type, intlet len, int *nptrs);
unsigned numsyze(intlet len, int *nptrs);
unsigned ptnsyze(intlet len, int *nptrs);

double hash(value v);

bool is_abcname(value name);

/****************************** Texts ******************************/

bool character(value v);

value mkchar(char c);
value mk_text(string s);
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
string convnum(value v);    /* character string approximation of any number */
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
value vpower();
value absval();
value signum();
value numerator();
value denominator();
value approximate();
value vrandom();
value root1();
value sin1();
value cos1();
value tan1();
value arctan1();
value angle1();
value sin2();
value cos2();
value tan2();
value arctan2();
value angle2();
value radius();
value vexp1();
value vlog1();
value root2();
value vlog2();
value vpi();
value e_natural();
value nowisthetime();
value exactly();
bool exact();

/****************************** Compounds ******************************/
#define Nfields(c) Length(c)
#define Field(c, i) ((Ats(c)+(i)))
#define k_Overfields for (k= 0; k < len; k++)
#define Lastfield(k) ((k) == len-1)

#define mk_compound(len) grab(Com, len)

/****************************** Lists ******************************/
value mk_range();
bool is_rangelist();

Visible Procedure insert();
Visible Procedure vremove();

/****************************** Tables ******************************/

value keys();
bool in_keys();
value associate();

Visible Procedure replace();
/* Procedure delete(); */

value* adrassoc();
value* key(value v, intlet k);
value* assoc(value v, intlet k);

/****************************** Texts, Lists, and Tables *******************/
value mk_elt(void);

bool in();

value size();
value size2();
value min1();
value min2();
value max1();
value max2();
#ifdef B_COMPAT
value th_of();
#endif
value thof();
value item();
value choice();

int length(value v); /* The same as size, temporary until part2 is written in B */
bool empty(); /* whether #v=0: also temporary */




#ifdef __cplusplus
}
#endif


#endif
