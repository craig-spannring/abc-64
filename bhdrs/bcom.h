/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BCOM_h_af3b751c2ce54ffe70051d7b829ba338
#define BCOM_h_af3b751c2ce54ffe70051d7b829ba338

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

	/* communication between interpreter and editor */

	typedef enum interp_to_ed_cmd
	{
		R_cmd=    'c',  /* command */
		R_expr=   'e',  /* EG expression */
		R_raw=    'r',  /* RAW expression */
		R_ioraw=  'i',  /* RAW expression for abc_input */
		R_answer= 'q', 	/* Yes/No */
	} interp_to_ed_cmd;


#ifdef __cplusplus
}
#endif


#endif
