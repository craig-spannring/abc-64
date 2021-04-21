/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I3SOU_h_fd9c7492ed650ce1c146dea84efff0ff
#define I3SOU_h_fd9c7492ed650ce1c146dea84efff0ff

#include "b.h"
#include "bint.h"
#include "i3cen.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1987. */

Visible bool is_zerfun(value t, value *f);
Visible bool is_monfun(value t, value *f);
Visible bool is_dyafun(value t, value *f);
Visible bool is_zerprd(value t, value *p);
Visible bool is_monprd(value t, value *p);
Visible bool is_dyaprd(value t, value *p);
Visible bool is_loaded(char *fname, value pname, value **aa);
Visible bool u_exists(value pname, value **aa);
Visible bool p_exists(value pname, value **aa);
Visible Procedure def_unit(value pname, value u);
Visible Procedure def_std_howto(value pname, value h);
Visible Procedure def_perm(value pname, value fname);
Visible Procedure free_perm(value pname);
Visible unsigned f_size(FILE *file);
Visible value get_unit(value *pname, bool filed, bool editing);

extern value last_unit;
extern value last_target;
extern bool need_rec_suggestions;

#define Permname(pname) (behead(pname, MkSmallInt(2)))
#define Permtype(pname) (strval(pname)[0])
	/* possible types:
	 *	1-8 [Cmd ... Tar]	(order used in mac/m1print.c!)
	 *	: [last_unit]
	 *	= [last_target]
	 */

#define Cmd '1'
#define Zfd '2'
#define Mfd '3'
#define Dfd '4'
#define Zpd '5'
#define Mpd '6'
#define Dpd '7'
#define Tar '8'
#define OldHow '+'	/* old how-to type (used in bio) */
#define OldTar '-'	/* old target type (used in bio) */
#define Wsp '.'		/* workspace type */

#define	Cmd_ext ".cmd"
#define Zfd_ext ".zfd"
#define Mfd_ext ".mfd"
#define Dfd_ext ".dfd"
#define Zpd_ext ".zpd"
#define Mpd_ext ".mpd"
#define Dpd_ext ".dpd"
#define Cts_ext ".cts"
#define Wsp_ext ""

#define CONVP_SIGN '_'		/* to map point */
#define CONVDQ_SIGN '@'		/* to map double quote */


	extern Visible bool  need_rec_suggestions; /* e.g. after abc -u file ... */
	extern Visible value errtname;
	extern Visible value last_target;          /* last edited target */
	extern Visible value last_unit;            /* last edited/erroneous unit */

	extern Visible bool ckws_writable(int m);
	extern Visible bool is_loaded(char *fname, value pname, value **aa);
	extern Visible bool p_exists(value pname, value **aa);
	extern Visible bool u_exists(value pname, value **aa);
	extern Visible Procedure clear_perm(void);
	extern Visible Procedure create_unit(void);
	extern Visible Procedure def_perm(value pname, value fname);
	extern Visible Procedure def_std_howto(value pname, value h);
	extern Visible Procedure def_target(value name, value t);
	extern Visible Procedure def_unit(value pname, value u);
	extern Visible Procedure del_target(value name);
	extern Visible Procedure edit_target(void);
	extern Visible Procedure edit_unit(void);
	extern Visible Procedure endperm(void);
	extern Visible Procedure endsou(void);
	extern Visible Procedure free_perm(value pname);
	extern Visible Procedure initperm(void);
	extern Visible Procedure initsou(void);
	extern Visible Procedure lst_uhds(void);
	extern Visible Procedure put_perm(void);
	extern Visible Procedure puttarval(value v, char *dir, value fname, value tname, bool silently);
	extern Visible Procedure putval(value v, char *dir, const char *name, literal ct, bool silently);
	extern Visible Procedure rem_unit(parsetree u, wsenvptr wse);
	extern Visible Procedure rem_unit(parsetree u, wsenvptr wse);
	extern Visible string lastunitname(void);
	extern Visible value get_pname(parsetree v);
	extern Visible value gettarval(value fname, value name);
	extern Visible value get_unit(value *pname, bool filed, bool editing);
	extern Visible value getval(value fname, literal ct);
	extern Visible value mkabcname(char *name);	/* vice versa for recovering target name */
	extern Visible value new_fname(value name, literal type);	/* devise a filename for a unit or target */
	extern Visible value permkey(value name, literal type);

	
#ifdef __cplusplus
}
#endif


#endif
