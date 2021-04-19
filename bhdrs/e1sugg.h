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
    Visible bool      setsugg(pathptr *pp, char c, enviro *ep, bool colon_allowed);
    Visible bool      newsugg(enviro *ep, string *pstr, int alt_c);
    Visible Procedure killsugg(enviro *ep, string *pstr);
    Visible Procedure acksugg(enviro *ep);
    Visible bool      newhowsugg(enviro *ep, string *pstr, int alt_c);
    Visible Procedure ackhowsugg(enviro *ep);
    Visible Procedure killhowsugg(enviro *ep);
    Visible Procedure check_last_unit(enviro *ep, int curr);
    Visible Procedure readsugg(pathptr p);
    Visible Procedure writesugg(pathptr p);
    Visible Procedure endclasses(void);
    
#ifdef __cplusplus
}
#endif
