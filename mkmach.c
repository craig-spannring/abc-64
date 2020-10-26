/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */

/* Generate constants for configuration file			*/

#include <stdio.h>
#include <stdlib.h>
#include "comp.h" 	/* for literal, SIGNAL and SETJMP */
#include "feat.h"	/* for reftype */

/* Check for signal SIGFPE and SETJMP on your system : */

#ifdef SIGNAL
#include <signal.h>
#ifndef SIGFPE
#undef SIGNAL
#endif
#endif

#ifdef SIGNAL
#ifdef SETJMP
#include <setjmp.h>
#else
#undef SIGNAL
#endif
#endif

/****************************************************************************/

#ifdef SIGNAL

	jmp_buf lab;
	SIGTYPE overflow(sig) int sig; { /* what to do on overflow/underflow */
		signal(sig, overflow);
		longjmp(lab, 1);
	}

#else /* !SIGNAL */

	/* Dummy routines instead */
	int lab=1;
	int setjmp(lab) int lab; { return(0); }

#endif /* !SIGNAL */

#define absval(x) (((x)<0.0)?(-x):(x))
#define min(x,y) (((x)<(y))?(x):(y))

/* These routines are intended to defeat any attempt at optimisation */
void Dstore(a, b) double a, *b; { *b=a; }
double Dsum(a, b) double a, b; { double r; Dstore(a+b, &r); return (r); }
double Ddiff(a, b) double a, b; { double r; Dstore(a-b, &r); return (r); }
double Dmul(a, b) double a, b; { double r; Dstore(a*b, &r); return (r); }
double Ddiv(a, b) double a, b; { double r; Dstore(a/b, &r); return (r); }

double power(x, n) int x, n; {
	double r=1.0;
	for (;n>0; n--) r*=x;
	return r;
}

int floor_log(base, x) int base; double x; { /* return floor(log base(x)) */
	int r=0;
	while (x>=base) { r++; x/=base; }
	return r;
}

int ceil_log(base, x) int base; double x; {
	int r=0;
	while (x>1.0) { r++; x/=base; }
	return r;
}

/* 	The following is ABC specific.				*/
/* 	It tries to prevent different alignments for the field	*/
/*	following common HEADER fields in various structures	*/
/*	used by the ABC system for different types of values.	*/

typedef short intlet;
#define HEADER literal type; reftype refcnt; intlet len
typedef struct header { HEADER; } header;
typedef struct value { HEADER; char **cts;} value;

int main(argc, argv) int argc; char *argv[]; {
	char co[4], oc[4];	/* Comment starter and ender symbols */
	char c;
	short newshort, maxshort, maxershort;
	int newint, maxint, maxdigit, shortbits, bits, mantbits,
	    *p, shortpower, intpower, longpower;
	long newlong, maxlong;
#ifdef MEMSIZE
	long count;
#endif
	unsigned long nfiller;
	int i, ibase, iexp, irnd, imant, iz, k, machep, maxexp, minexp,
	    mx, negeps, tendigs;
	double a, b, base, basein, basem1, eps, epsneg, xmax, newxmax,
	       xmin, xminner, y, y1, z, z1, z2;

	double BIG, Maxreal;
	int ABCBASE, MAXNUMDIG, tenlogBASE, Maxexpo, Minexpo, DBLBITS, LONGBITS;
	co[0]= '/'; oc[0]= ' ';
	co[1]= '*'; oc[1]= '*';
	co[2]= ' '; oc[2]= '/';
	co[3]= '\0'; oc[3]= '\0';

#ifdef SIGNAL
	signal(SIGFPE, overflow);
	if (setjmp(lab)!=0) { printf("Unexpected over/underflow\n"); exit(1); }
#endif

/****** Calculate number of bits per character **************************/

	c=1; bits=0;
	do { c=c<<1; bits++; } while(c!=0);
	c= (char)(-1);
	printf("%schar=%d bits, %ssigned%s\n", co, (int)(sizeof(c)*bits),
			((int)c)<0?"":"un", oc);

/****** Calculate max short *********************************************/
/*      Calculate 2**n-1 until overflow - then use the previous value	*/

	newshort=1; maxshort=0;

	if (setjmp(lab)==0)
		for(shortpower=0; newshort>maxshort; shortpower++) {
			maxshort=newshort;
			newshort=newshort*2+1;
		}

	/* Now for those daft Cybers: */

	maxershort=0; newshort=maxshort;

	if (setjmp(lab)==0)
		for(shortbits=shortpower; newshort>maxershort; shortbits++) {
			maxershort=newshort;
			newshort=newshort+newshort+1;
		}
	
	printf("%smaxshort=%d (=2**%d-1)%s\n", co, maxshort, shortpower, oc);

	if (maxershort>maxshort) {
		printf("%sThere is a larger maxshort, %d (=2**%d-1), %s%s\n",
			co, maxershort, shortbits, 
			"but only for addition, not multiplication", oc);
	}

/****** Calculate max int by the same method ***************************/

	newint=1; maxint=0;

	if (setjmp(lab)==0)
		for(intpower=0; newint>maxint; intpower++) {
			maxint=newint;
			newint=newint*2+1;
		}

	printf("%smaxint=%d (=2**%d-1)%s\n", co, maxint, intpower, oc);

/****** Calculate max long by the same method ***************************/

	newlong=1; maxlong=0;

	if (setjmp(lab)==0)
		for(longpower=0; newlong>maxlong; longpower++) {
			maxlong=newlong;
			newlong=newlong*2+1;
		}

	if (setjmp(lab)!=0) { printf("\nUnexpected under/overflow\n"); exit(1); }

	printf("%smaxlong=%ld (=2**%d-1)%s\n", co, maxlong, longpower, oc);

/****** Pointers ********************************************************/
	printf("%spointers=%d bits%s%s\n", co, (int)(sizeof(p)*bits),
		sizeof(p)>sizeof(int)?" BEWARE! larger than int!":"", oc);

/****** Base and size of mantissa ***************************************/
	a=1.0;
	do { a=Dsum(a, a); } while (Ddiff(Ddiff(Dsum(a, 1.0), a), 1.0) == 0.0);
	b=1.0;
	do { b=Dsum(b, b); } while ((base=Ddiff(Dsum(a, b), a)) == 0.0);
	ibase=base;
	printf("%sbase=%d%s\n", co, ibase, oc);

	imant=0; b=1.0;
	do { imant++; b=Dmul(b, base); }
	while (Ddiff(Ddiff(Dsum(b,1.0),b),1.0) == 0.0);
	printf("%sSignificant base digits=%d%s\n", co, imant, oc);
	tendigs= ceil_log(10, b); /* the number of digits */

/****** Various flavours of epsilon *************************************/
	basem1=Ddiff(base,1.0);
	if (Ddiff(Dsum(a, basem1), a) != 0.0) irnd=1; 
	else irnd=0;

	negeps=imant+imant;
	basein=1.0/base;
	a=1.0;
	for(i=1; i<=negeps; i++) a*=basein;

	b=a;
	while (Ddiff(Ddiff(1.0, a), 1.0) == 0.0) {
		a*=base;
		negeps--;
	}
	negeps= -negeps;
	printf("%sSmallest x such that 1.0-base**x != 1.0=%d%s\n", co,
	       negeps, oc);

	epsneg=a;
	if ((ibase!=2) && (irnd==1)) {
	/*	a=(a*(1.0+a))/(1.0+1.0); => */
		a=Ddiv(Dmul(a, Dsum(1.0, a)), Dsum(1.0, 1.0));
	/*	if ((1.0-a)-1.0 != 0.0) epsneg=a; => */
		if (Ddiff(Ddiff(1.0, a), 1.0) != 0.0) epsneg=a;
	}
	printf("%sSmall x such that 1.0-x != 1.0=%g%s\n", co, epsneg, oc);
	/* it may not be the smallest */

	machep= -imant-imant;
	a=b;
	while (Ddiff(Dsum(1.0, a), 1.0) == 0.0) { a*=base; machep++; }
	printf("%sSmallest x such that 1.0+base**x != 1.0=%d%s\n",
	       co, machep, oc);

	eps=a;
	if ((ibase!=2) && (irnd==1)) {
	/*	a=(a*(1.0+a))/(1.0+1.0); => */
		a=Ddiv(Dmul(a, Dsum(1.0, a)), Dsum(1.0, 1.0));
	/*	if ((1.0+a)-1.0 != 0.0) eps=a; => */
		if (Ddiff(Dsum(1.0, a), 1.0) != 0.0) eps=a;
	}
	printf("%sSmallest x such that 1.0+x != 1.0=%g%s\n", co, eps, oc);

/****** Round or chop ***************************************************/
	if (irnd == 1) { printf("%sArithmetic rounds%s\n", co, oc); }
	else { 
		printf("%sArithmetic chops", co);
		if (Ddiff(Dmul(Dsum(1.0,eps),1.0),1.0) != 0.0) {
			printf(" but uses guard digits");
		}
		printf("%s\n", oc);
	}

/****** Size of and minimum normalised exponent ****************************/
	y=0; i=0; k=1; z=basein; z1=(1.0+eps)/base;

	/* Coarse search for the largest power of two */
	if (setjmp(lab)==0) /* in case of underflow trap */
		do {
			y=z; y1=z1;
			z=Dmul(y,y); z1=Dmul(z1, y);
			a=Dmul(z,1.0);
			z2=Ddiv(z1,y);
			if (z2 != y1) break;
			if ((Dsum(a,a) == 0.0) || (absval(z) >= y)) break;
			i++;
			k+=k;
		} while(1);

	if (ibase != 10) {
		iexp=i+1; /* for the sign */
		mx=k+k;
	} else {
		iexp=2;
		iz=ibase;
		while (k >= iz) { iz*=ibase; iexp++; }
		mx=iz+iz-1;
	}

	/* Fine tune starting with y and y1 */
	if (setjmp(lab)==0) /* in case of underflow trap */
		do {
			xmin=y; z1=y1;
			y=Ddiv(y,base); y1=Ddiv(y1,base);
			a=Dmul(y,1.0);
			z2=Dmul(y1,base);
			if (z2 != z1) break;
			if ((Dsum(a,a) == 0.0) || (absval(y) >= xmin)) break;
			k++;
		} while (1);

	if (setjmp(lab)!=0) { printf("Unexpected over/underflow\n"); exit(1); }

	minexp= (-k)+1;

	if ((mx <= k+k-3) && (ibase != 10)) { mx+=mx; iexp+=1; }
	printf("%sNumber of bits used for exponent=%d%s\n", co, iexp, oc);
	printf("%sMinimum normalised exponent=%d%s\n", co, minexp, oc);
	printf("%sMinimum normalised positive number=%g%s\n", co, xmin, oc);

/****** Minimum exponent ***************************************************/
	if (setjmp(lab)==0) /* in case of underflow trap */
		do {
			xminner=y;
			y=Ddiv(y,base);
			a=Dmul(y,1.0);
			if ((Dsum(a,a) == 0.0) || (absval(y) >= xminner)) break;
		} while (1);

	if (setjmp(lab)!=0) { printf("Unexpected over/underflow\n"); exit(1); }

	if (xminner != 0.0 && xminner != xmin) {
		printf("%sThe smallest numbers are not kept normalised%s\n",
		       co, oc);
		printf("%sSmallest unnormalised positive number=%g%s\n",
			co, xminner, oc);
	}

/****** Maximum exponent ***************************************************/
	maxexp=2; xmax=1.0; newxmax=base+1.0;
	if (setjmp(lab) == 0) {
		while (xmax<newxmax) {
			xmax=newxmax;
			newxmax=Dmul(newxmax, base);
			if (Ddiv(newxmax, base) != xmax) break; /* ieee infinity */
			maxexp++;
		}
	}
	if (setjmp(lab)!=0) { printf("Unexpected over/underflow\n"); exit(1); }

	printf("%sMaximum exponent=%d%s\n", co, maxexp, oc);

/****** Largest and smallest numbers ************************************/
	xmax=Ddiff(1.0, epsneg);
	if (Dmul(xmax,1.0) != xmax) xmax=Ddiff(1.0, Dmul(base,epsneg));
	for (i=1; i<=maxexp; i++) xmax=Dmul(xmax, base);
	printf("%sMaximum number=%g%s\n", co, xmax, oc);

/****** Hidden bit + sanity check ***************************************/
	if (ibase != 10) {
		mantbits=floor_log(2, (double)ibase)*imant;
		if (mantbits+iexp+1 == sizeof(double)*bits+1) {
			printf("%sDouble arithmetic uses a hidden bit%s\n",
			       co, oc);
		} else if (mantbits+iexp+1 == sizeof(double)*bits) {
			printf("%sDouble arithmetic doesn't use a hidden bit%s\n",
			       co, oc);
		} else {
			printf("%sSomething fishy here! %s %s%s\n", co,
				"Exponent size + mantissa size doesn't match",
				"with the size of a double.", oc);
		}
	}

/****** The point of it all: ********************************************/
	printf("\n%sNumeric package constants%s\n", co, oc);

	tenlogBASE= floor_log(10, (double)maxlong)/2;
	ABCBASE=1; for(i=1; i<=tenlogBASE; i++) ABCBASE*=10;

	BIG= power(ibase, imant)-1.0;
	MAXNUMDIG= tendigs;
	Maxreal= xmax;
	Maxexpo= floor_log(2, (double)ibase)*maxexp;
	Minexpo= floor_log(2, (double)ibase)*minexp;
	DBLBITS= floor_log(2, (double)ibase)*imant;
	LONGBITS= longpower;

	printf("#define Maxintlet %d %sMaximum short%s\n", maxshort, co, oc);
	printf("#define Maxint %d %sMaximum int%s\n", maxint, co, oc);

	if (2*intpower + 1 <= longpower) {
		printf("typedef int digit;\n");
		maxdigit= maxint;
	}
	else {
		printf("typedef short digit;\n");
		maxdigit= maxshort;
	}
	printf("typedef long twodigit;\n");
	
	printf("%sABCBASE must be a power of ten, ABCBASE**2 must fit in a twodigit%s\n", co, oc);
	printf("%sand -2*ABCBASE as well as ABCBASE*2 must fit in a digit%s\n",
	       co, oc);

	printf("#define ABCBASE %d\n", ABCBASE);
	if (((double)ABCBASE)*ABCBASE > maxlong || ((double)ABCBASE)+ABCBASE > maxdigit) {
		printf("*** ABCBASE value wrong\n");
		exit(1);
	}
	printf("#define tenlogBASE %d %s = log10(ABCBASE)%s\n", tenlogBASE,
	       co, oc);

	printf("#define BIG %1.1f %sMaximum integral double%s\n", BIG, co, oc);
	printf("#define MAXNUMDIG %d %sThe number of decimal digits in BIG%s\n",
		MAXNUMDIG, co, oc);
	printf("#define MINNUMDIG 6 %sDon't change: this is here for consistency%s\n", co, oc);

	printf("#define Maxreal %e %sMaximum double%s\n", Maxreal, co, oc);
	printf("#define Maxexpo %d %sMaximum value such that 2**Maxexpo<=Maxreal%s\n",
		Maxexpo, co, oc);
	printf("#define Minexpo (%d) %sMinimum value such that -2**Minexpo>=Minreal%s\n",
		Minexpo, co, oc);
	printf("#define DBLBITS %d %sThe number of bits in the fraction of a double%s\n",
		DBLBITS, co, oc);

	printf("#define LONGBITS %d %sThe number of bits in a long%s\n",
		LONGBITS, co, oc);
	printf("#define TWOTO_DBLBITSMIN1 %1.1f %s2**(DBLBITS-1)%s\n",
		power(2, DBLBITS-1), co, oc);
	printf("#define TWOTO_LONGBITS %1.1f %s2**LONGBITS%s\n",
		power(2, LONGBITS), co, oc);

	printf("\n%sEnable fair choice from object whose size exceeds%s\n",
	       co, oc);
	printf("\n%sthe maximum allowed by the granularity of random():%s\n",
	       co, oc);
	printf("#define RNDM_LIMIT %1.1f %ssafe limit for choice%s\n",
		power(2, (DBLBITS < 66 ? DBLBITS-3 : 63)), co, oc);

#ifdef MEMSIZE
/* An extra goody: the approximate amount of data-space */
/* Put here because it is likely to be slower then the rest */

	/*Allocate blocks of 1000 until no more available*/
	/*Don't be tempted to change this to 1024: */
	/*we don't know how much header information there is*/

	for(count=0; (p=(int *)malloc(1000))!=0; count++) { }

	printf("\n%sMemory~= %d000%s\n", co, count, oc);
#endif /*MEMSIZE*/


	/* ABC Small Integers; see bhdrs/b.h */
	printf("\n%sABC's Small Integer Representation (compare bhdrs/b.h)%s\n",
	       co, oc);
	printf("%sThese values must be so because of the canonical number representation%s\n", co, oc);
	printf("#define MaxSmallInt (ABCBASE-1) %sDo not change!%s\n", co, oc);
	printf("#define MinSmallInt (-ABCBASE) %sDo not change!%s\n", co, oc);
	
	/* Max x for sin(x) etc. */
	printf("\n#define Maxtrig BIG %sMax x for sin(x), cos(x), tan(x)%s\n",
	       co, oc);

	/* Aligning ABC values */
	printf("\n");
	nfiller= (unsigned)
		((sizeof(value)) - ((sizeof(header)) + (sizeof(char **))));
	printf("#define HEADER literal type; reftype refcnt; intlet len");
	if (nfiller > 0)
		printf("; char filler[%lu]", nfiller);
	printf("\n");
	printf("#define FILLER");
	if (nfiller > 0) {
		printf(" {");
		for (i= 1; i < nfiller; i++) {
			printf("0, ");
		}
		printf("0},");
	}
	printf("\n");
	
	exit(0);
}
