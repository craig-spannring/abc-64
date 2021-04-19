#ifndef E1COMM_h_489fa08f22bd1705e716ccc82d71cacd
#define E1COMM_h_489fa08f22bd1705e716ccc82d71cacd

#include "b.h"
#include "supr.h"       /* for environ */

#ifdef __cplusplus
extern "C" {
#endif

	extern Visible int doctype;
	extern Visible enviro *tobesaved;
	extern Visible string savewhere;
	
	extern Visible Procedure initbed(void);
	extern Visible Procedure endbed(void);
	extern Visible Procedure abced_file(string filename, intlet errline, literal kind, bool creating, bool *changed);
	extern Visible char *ed_line(literal kind, int indent);
    
#ifdef __cplusplus
}
#endif


#endif
