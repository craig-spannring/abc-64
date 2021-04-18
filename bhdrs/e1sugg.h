#include "b.h"
#include "bedi.h"
#include "supr.h"

#ifdef __cplusplus
extern "C" {
#endif

    Visible Procedure initcensugg(void);
    Visible Procedure initsugg(void);
    Visible Procedure endsugg(void);
    Visible Procedure addsugg(string str, int builtin);
    Visible bool      setsugg(pathptr *pp, char c, environ *ep, bool colon_allowed);
    Visible bool      newsugg(environ *ep, string *pstr, int alt_c);
    Visible Procedure killsugg(environ *ep, string *pstr);
    Visible Procedure acksugg(environ *ep);
    Visible bool      newhowsugg(environ *ep, string *pstr, int alt_c);
    Visible Procedure ackhowsugg(environ *ep);
    Visible Procedure killhowsugg(environ *ep);
    Visible Procedure check_last_unit(environ *ep, int curr);
    Visible Procedure readsugg(pathptr p);
    Visible Procedure writesugg(pathptr p);
    Visible Procedure endclasses(void);
    
#ifdef __cplusplus
}
#endif
