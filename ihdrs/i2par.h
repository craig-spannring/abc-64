/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I2PAR_h_6b9a47915959416229f3ee9dd029ca64
#define I2PAR_h_6b9a47915959416229f3ee9dd029ca64

#include "bint.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************/

/* Avoid name conflict with standard header files: */
#define compound b_compound

/* General parsing routines */

typedef char *txptr;

#define Eotc '\0'

#define Char(tx)	(*(tx))
#define Eol(tx)		(Char(tx) == '\n')
#define Ceol(tx)	(Char(tx) == C_COMMENT || Eol(tx))
#define Text(q) 	(tx < q)

#define Space(c)	((c) == ' ' || (c) == '\t')

#define Letter(c)	(islower(c))
#define Cap(c)		(isupper(c))
#define Dig(c)		(isdigit(c))

#define Tagmark(tx) \
		(Tagletmark(Char(tx)) || (Char(tx) == C_POINT && \
		Tagletmark(Char(tx-1)) && Tagletmark(Char(tx+1)) ))
#define Tagletmark(c) \
	(Letter(c) || Dig(c) || (c) == C_APOSTROPHE || (c) == C_QUOTE)

#define Keytagmark(tx) \
	(keymark(tx) || Tagmark(tx))
	
#define Isexpr(c) \
	(Letter(c) || (c) == C_OPEN || Dig(c) || (c) == C_POINT || \
	 (c) == C_APOSTROPHE || (c) == C_QUOTE || (c) == C_CUROPEN || \
	 (c) == C_ABOUT || (c) == C_TIMES || (c) == C_OVER || \
	 (c) == C_PLUS || (c) == C_MINUS || (c) == C_NUMBER)

txptr fcol(void);
char *keyword(void);

bool mon_sign(value *v);

extern txptr tx, ceol, first_col;
extern intlet cur_ilev;
intlet ilev(void);

extern value res_cmdnames;

value cr_text(txptr p, txptr q);

/* contexts: */
#define In_share 's'
#define In_ranger 'q'
#define In_formal 'f'
#define In_ref 'r'

/* Expressions: */

parsetree expr(txptr q);
parsetree singexpr(txptr q);

/* Targets: */

parsetree targ(txptr q); 

/* Tests: */

parsetree test(txptr q); 
parsetree unp_test(txptr q);

/* Commands: */

parsetree cmd_suite(intlet cil, bool first, parsetree (*suite)(intlet cil, bool first, bool *emp));
parsetree cmd_seq(intlet cil, bool first, bool *emp);
parsetree ucmd_seq(intlet cil, bool first, bool *emp);
value tail_line(void);

/* B units */

parsetree unit(bool heading, bool editing);
parsetree collateral(txptr q, parsetree (*base) (txptr q));
parsetree compound(txptr q, parsetree (*base)(txptr q));
parsetree idf(txptr q);
extern literal idf_cntxt;

/* signs */

#define C_COLON		':'
#define S_COLON		":"
#define C_SEMICOLON	';'
#define S_SEMICOLON	";"
#define C_OPEN		'('
#define S_OPEN		"("
#define C_CLOSE		')'
#define S_CLOSE		")"
#define C_COMMA		','
#define S_COMMA		","
#define C_POINT		'.'
#define S_POINT		"."
#define C_APOSTROPHE	'\''
#define S_APOSTROPHE	"'"
#define C_QUOTE		'"'
#define S_QUOTE		"\""
#define C_CONVERT	'`'
#define S_CONVERT	"`"
#define C_CUROPEN	'{'
#define S_CUROPEN	"{"
#define C_CURCLOSE	'}'
#define S_CURCLOSE	"}"
#define C_SUB		'['
#define S_SUB		"["
#define C_BUS		']'
#define S_BUS		"]"
#define C_BEHEAD	'@'
#define S_BEHEAD	"@"
#define C_CURTAIL	'|'
#define S_CURTAIL	"|"
#define C_ABOUT		'~'
#define S_ABOUT		"~"
#define C_PLUS		'+'
#define S_PLUS		"+"
#define C_MINUS		'-'
#define S_MINUS		"-"
#define C_TIMES		'*'
#define S_TIMES		"*"
#define C_OVER		'/'
#define S_OVER		"/"
#define C_JOIN		'^'
#define S_JOIN		"^"
#define C_NUMBER	'#'
#define S_NUMBER	"#"
#define C_LESS		'<'
#define S_LESS		"<"
#define C_EQUAL		'='
#define S_EQUAL		"="
#define C_GREATER	'>'
#define S_GREATER	">"
#define S_POWER		"**"
#define S_NUMERATOR	"*/"
#ifdef __STDC__
#define S_DENOMINATOR	"/*"
#else
#define S_DENOMINATOR	"/\*"
	/* \ is needed, else some C preprocessors see it as comment start! */
#endif
#define S_REPEAT	"^^"
#define S_LEFT_ADJUST	"<<"
#define S_CENTER	"><"
#define S_RIGHT_ADJUST	">>"
#define S_AT_MOST	"<="
#define S_UNEQUAL	"<>"
#define S_AT_LEAST	">="
#define S_RANGE		".."

#define C_COMMENT	'\\'
#define S_COMMENT	"\\"
#define C_NEWLINE	'/'
#define S_NEWLINE	"/"

#define open_sign	_sign_is(C_OPEN)
#define point_sign	_sign_is(C_POINT)
#define apostrophe_sign	_sign_is(C_APOSTROPHE)
#define quote_sign	_sign_is(C_QUOTE)
#define conv_sign	_sign_is(C_CONVERT)
#define curlyopen_sign	_sign_is(C_CUROPEN)
#define curlyclose_sign	_sign_is(C_CURCLOSE)
#define sub_sign	_sign_is(C_SUB)
#define behead_sign	_sign_is(C_BEHEAD)
#define curtl_sign	_sign_is(C_CURTAIL)
#define about_sign	_sign_is(C_ABOUT)
#define plus_sign	_sign_is(C_PLUS)
#define minus_sign	_sign_is(C_MINUS)
#define number_sign	_sign_is(C_NUMBER)
#define equals_sign	_sign_is(C_EQUAL)
#define greater_sign	_sign_is(C_GREATER)

#define comment_sign	_sign_is(C_COMMENT)

#define reptext_sign	_sign2_is(S_REPEAT)
#define leftadj_sign	_sign2_is(S_LEFT_ADJUST)
#define center_sign	_sign2_is(S_CENTER)
#define rightadj_sign	_sign2_is(S_RIGHT_ADJUST)
#define at_most_sign	_sign2_is(S_AT_MOST)
#define unequal_sign	_sign2_is(S_UNEQUAL)
#define at_least_sign	_sign2_is(S_AT_LEAST)

#define _sign_is(c) \
	(Char(tx) == (c) ? (tx++, Yes) : No)
#define _sign2_is(s) \
	(Char(tx) == (s[0]) && Char(tx+1) == (s[1]) ? (tx+= 2, Yes) : No)

/*
 * Implicitly invoke function call in a way that looks like a variable access
 */
#define nwl_sign	nwl_sign_()
#define times_sign	times_sign_()
#define over_sign	over_sign_()
#define power_sign	power_sign_()
#define numtor_sign	numtor_sign_()
#define denomtor_sign	denomtor_sign_()
#define join_sign	join_sign_()
#define less_than_sign	less_than_sign_()
#define greater_than_sign greater_than_sign_()

extern Visible bool nwl_sign_(void);
extern Visible bool times_sign_(void);
extern Visible bool over_sign_(void);
extern Visible bool power_sign_(void);
extern Visible bool numtor_sign_(void);
extern Visible bool denomtor_sign_(void);
extern Visible bool join_sign_(void);
extern Visible bool less_than_sign_(void);
extern Visible bool greater_than_sign_(void);
    
/* keywords */

// #define atkw(kw, s)		(strcmp(kw, s) == 0)
static inline bool atkw(const char* kw, const char* s) {return (strcmp(kw, s) == 0);}

#define check_keyword(kw)	(atkw(kw, K_CHECK))
#define delete_keyword(kw) 	(atkw(kw, K_DELETE))
#define insert_keyword(kw) 	(atkw(kw, K_INSERT))
#define pass_keyword(kw)	(atkw(kw, K_PASS))
#define put_keyword(kw) 	(atkw(kw, K_PUT))
#define read_keyword(kw) 	(atkw(kw, K_READ))
#define remove_keyword(kw) 	(atkw(kw, K_REMOVE))
#define setrandom_keyword(kw) 	(atkw(kw, K_SETRANDOM))
#define write_keyword(kw) 	(atkw(kw, K_WRITE))
#define fail_keyword(kw)	(atkw(kw, K_FAIL))
#define quit_keyword(kw) 	(atkw(kw, K_QUIT))
#define return_keyword(kw)	(atkw(kw, K_RETURN))
#define report_keyword(kw) 	(atkw(kw, K_REPORT))
#define succeed_keyword(kw) 	(atkw(kw, K_SUCCEED))
#define if_keyword(kw) 		(atkw(kw, K_IF))
#define select_keyword(kw) 	(atkw(kw, K_SELECT))
#define while_keyword(kw) 	(atkw(kw, K_WHILE))
#define for_keyword(kw) 	(atkw(kw, K_FOR))
#define else_keyword(kw) 	(atkw(kw, K_ELSE))
#define not_keyword(kw) 	(atkw(kw, K_NOT))
#define some_keyword(kw) 	(atkw(kw, K_SOME))
#define each_keyword(kw) 	(atkw(kw, K_EACH))
#define no_keyword(kw) 		(atkw(kw, K_NO))
#define how_keyword(kw) 	(atkw(kw, K_HOW))
#define share_keyword(kw) 	(atkw(kw, K_SHARE))

#ifdef GFX

#define spacefrom_keyword(kw)	(atkw(kw, K_SPACEFROM))
#define linefrom_keyword(kw)	(atkw(kw, K_LINEFROM))
#define clearscreen_keyword(kw)	(atkw(kw, K_CLEARSCREEN))

#endif /* GFX */

#ifdef __cplusplus
}
#endif


#endif
