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

#ifdef __cplusplus
}
#endif


#endif
