#ifndef I2SYM_h_59d903023cdc6918ba231e05336e38fb
#define I2SYM_h_59d903023cdc6918ba231e05336e38fb

#include "b.h"
#include "i2par.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern Visible txptr  tx;
	extern Visible txptr  ceol;
	extern Visible txptr  first_col;
	extern Visible bool   i_looked_ahead;
	extern Visible intlet cur_ilev;
	extern Visible value  res_cmdnames;
	

	extern Visible bool ateol(void);
	extern Visible bool denomtor_sign_(void);
	extern Visible bool dyamon_sign(value *v);
	extern Visible bool dya_sign(value *v);
	extern Visible bool findkw(txptr q, txptr* ftx);
	extern Visible bool findrel(txptr q, txptr* ftx);
	extern Visible bool find(conststring s, txptr q, txptr* ftx, txptr* ttx);
	extern Visible bool findtrim(txptr q, txptr *first);
	extern Visible bool greater_than_sign_(void);
	extern Visible bool is_abcname(value name);
	extern Visible bool is_cmdname(txptr q, char** name);
	extern Visible bool is_keyword(char **kw);
	extern Visible bool is_tag(value *v);
	extern Visible bool join_sign_(void);
	extern Visible bool less_than_sign_(void);
	extern Visible bool mon_sign(value *v);
	extern Visible bool nothing(txptr q, int m) ;
	extern Visible bool nothing(txptr q, int m);
	extern Visible bool numtor_sign_(void);
	extern Visible bool nwl_sign_(void);
	extern Visible bool over_sign_(void);
	extern Visible bool power_sign_(void);
	extern Visible bool texdis_sign(value *v);
	extern Visible bool times_sign_(void);
	extern Visible char *keyword(void);
	extern Visible intlet ilev(void);
	extern Visible Procedure endsyn(void);
	extern Visible Procedure findceol(void);
	extern Visible Procedure first_ilev(void); /* initialise read buffer for new input */
	extern Visible Procedure initsyn(void);
	extern Visible Procedure need(string s);
	extern Visible Procedure req(string s, txptr q, txptr *ftx, txptr *ttx);
	extern Visible Procedure skipsp(txptr *tx0);
	extern Visible Procedure upto1(txptr q, int m);
	extern Visible Procedure upto(txptr q, string s);
	extern Visible Procedure veli(void);
	extern Visible Procedure veli(void); /* After a look-ahead call of ilev */
	extern Visible txptr fcol(void); /* the first position of the current line */
	extern Visible value cr_text(txptr p, txptr q);

#ifdef __cplusplus
}
#endif


#endif
