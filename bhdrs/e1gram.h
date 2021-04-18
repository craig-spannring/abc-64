/**
 * @file
 * 
 */    
#ifndef E1GRAM_h_6f34d6c61c60053692c07c29fec8b1e1
#define E1GRAM_h_6f34d6c61c60053692c07c29fec8b1e1

#include "b.h"
#include "bedi.h"
#include "tabl.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible bool allowed(pathptr p, int sym);
	extern Visible bool allows_colon(int sym);
	extern Visible bool isinclass(int sym, struct classinfo *ci);
	extern Visible bool issublist(int sym);
	extern Visible bool samelevel(int sym, int sym1);
	extern Visible int  nametosym(string str);
	extern Visible int nametosym(string str);
	extern Visible nodeptr gram(int sym);
	extern Visible Procedure endnoderepr(void); /* hack to free noderepr static store */
	extern Visible Procedure initclasses(void);
	extern Visible Procedure initgram(void);
	extern Visible Procedure setroot(int isym);
	extern Visible Procedure setroot(int isym); /* symbols defined in tabl.h */
	extern Visible string *noderepr(nodeptr n);
	extern Visible string symname(int sym);

#ifdef __cplusplus
}
#endif


#endif
