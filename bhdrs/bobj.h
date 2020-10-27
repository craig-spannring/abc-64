/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BOBJ_h_945555dcedb9ec8701ff4cfb11761611
#define BOBJ_h_945555dcedb9ec8701ff4cfb11761611

#ifdef __cplusplus
extern "C" {
#endif

/* B values, locations, environments: the B abstract machine */

/* Avoid name conflicts with standard header files: */
#define power b_power
#define exp1 b_exp1
#define log1 b_log1
#define log2 b_log2
#define pi b_pi
#define random b_random
#define remove b_remove
#define mod b_mod

/****************************** general ******************************/

typedef int relation; /* < 0, == 0, > 0 */
relation compare();

/*************************************************************************/

value grab();
unsigned tltsyze();
unsigned numsyze();
unsigned ptnsyze();

double hash();

bool is_abcname();

/****************************** Texts ******************************/

bool character();

value mkchar();
value mk_text();
char charval();
char ncharval();
string strval();
string sstrval();

value concat();
value behead();
value curtail();
value repeat();

value stripped();
value split();
value upper();
value lower();

value adjleft();
value centre();
value adjright();

value convert();

/****************************** Numbers ******************************/

/* Predicates */
bool integral();	    /* is the value an integer? */
bool large();	    /* can a number be represented by a C int? */
#ifdef RANGEPRINT
bool is_increment();	/* a = b+1 ? */
#endif

/* Constants */
#define zero MkSmallInt(0)
#define one MkSmallInt(1)

/* Conversion of abstract values to concrete objects */
double numval();     /* numeric value of any number */
int intval();        /* numeric value of integral number */
int propintlet();    /* checks int for fitting in intlet */
string convnum();    /* character string approximation of any number */
relation numcomp();  /* comparison of two numbers: yields -1, 0 or 1 */
double numhash();    /* hashes any abstract number to a 'double' */

/* Conversion of concrete objects to abstract numbers */
value numconst();    /* string argument */
value mk_integer();  /* int argument */

/* Functions on numbers */
value sum();
value diff();
value negated();
value prod();
value quot();
value floor_f();
value ceil_f();
value round1();
value round2();
value mod();
value power();
value absval();
value signum();
value numerator();
value denominator();
value approximate();
value random();
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
value exp1();
value log1();
value root2();
value log2();
value pi();
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
Visible Procedure remove();

/****************************** Tables ******************************/

value keys();
bool in_keys();
value associate();

Visible Procedure replace();
/* Procedure delete(); */

value* adrassoc();
value* key();
value* assoc();

/****************************** Texts, Lists, and Tables *******************/
value mk_elt();

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

int length(); /* The same as size, temporary until part2 is written in B */
bool empty(); /* whether #v=0: also temporary */




#ifdef __cplusplus
extern "C" }
#endif


#endif
