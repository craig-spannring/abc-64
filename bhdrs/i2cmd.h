#ifndef I2CMD_h_67184b3199796a490e8b7d4275789b84
#define I2CMD_h_67184b3199796a490e8b7d4275789b84

#include "b.h"
#include "bint.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern Visible bool is_comment(value *v);
    extern Visible bool term_com(char *kw, parsetree *v);
    extern Visible bool control_command(char *kw, parsetree *v);
    extern Visible bool simple_command(char *kw, parsetree *v, value *c);
    extern Visible parsetree cmd_suite(intlet cil, bool first, parsetree (*suite)(intlet cil, bool first, bool *emp));
    extern Visible parsetree cmd_seq(intlet cil, bool first, bool *emp);
    extern Visible bool is_comment(value *v);
    extern Visible value tail_line(void);
    extern Visible bool term_com(char *kw, parsetree *v);
    extern Visible bool control_command(char *kw, parsetree *v);
    
#ifdef __cplusplus
}
#endif

#endif
