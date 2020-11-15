#ifndef E1CELL_h_47aab256c5fabc934d6183f2427c8b53
#define E1CELL_h_47aab256c5fabc934d6183f2427c8b53

#include "b.h"
#include "cell.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible Procedure discard(cell *p);
	extern Visible cell *replist(cell *tops, cell *rep, int oldlno, int oldlcnt);
	extern Visible cell *build(path p, int lcnt);
	extern Visible cell *gettop(cell *tops);

#ifdef __cplusplus
    }
#endif

#endif
