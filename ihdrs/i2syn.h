#ifndef I2SYM_h_59d903023cdc6918ba231e05336e38fb
#define I2SYM_h_59d903023cdc6918ba231e05336e38fb

#include "b.h"
#include "i2par.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible bool nothing(txptr q, int m);
	extern Visible bool is_tag(value *v);
	extern Visible bool is_keyword(char **kw);
	extern Visible bool find(string s, txptr q, txptr* ftx, txptr* ttx);
	extern Visible bool findkw(txptr q, txptr* ftx);
	extern Visible bool ateol(void);
	extern Visible bool findrel(txptr q, txptr* ftx);
	
	extern Visible bool less_than_sign_(void);
	extern Visible bool greater_than_sign_(void);
	
	extern Visible bool is_cmdname(txptr q, char** name);
	
	extern Visible bool dyamon_sign(value *v);
	extern Visible bool dya_sign(value *v);
	extern Visible bool findtrim(txptr q, txptr *first);
	extern Visible bool texdis_sign(value *v);
	
	extern Visible Procedure veli(void);
	
	extern Visible Procedure req(string s, txptr q, txptr *ftx, txptr *ttx);
	
	extern Visible Procedure skipsp(txptr *tx0);

#ifdef __cplusplus
}
#endif


#endif
