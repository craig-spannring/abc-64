/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BVIS_h_e0b3d54e89a0b7e545681a60f0271fe5
#define BVIS_h_e0b3d54e89a0b7e545681a60f0271fe5

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1991. */

    
/* b1memo.c */

/* b1mess.c */

/* b1outp.c */

/* e1cell.c */

/* e1comm.c */

/* e1deco.c*/

/* e1edoc.c */

/* e1erro.c */

/* e1eval.c*/

/* e1getc.c*/
Visible Procedure undefine(int code, int deflen, string def);

/* e1goto.c*/
// Visible Procedure gotofix(environ *ep, int y, int x);

/* e1gram.c*/
Visible Procedure setroot(int isym);
Visible Procedure initgram(void);
Visible Procedure initkeys(void);
Visible Procedure initclasses(void);
Visible Procedure endnoderepr(void);

/* e1line.c*/
Visible Procedure oneline();

/* e1node.c*/
Visible Procedure setchild();
Visible Procedure markpath();
Visible Procedure unmkpath();
Visible Procedure treereplace();
Visible Procedure top();
Visible Procedure touchpath();
Visible Procedure putintrim();

/* e1outp.c*/
Visible Procedure startactupdate();
Visible Procedure outline();
Visible Procedure endactupdate();
Visible Procedure savefocus();
Visible Procedure setfocus();

/* e1que1.c*/
Visible Procedure preptoqueue();
Visible Procedure addtoqueue();
Visible Procedure stringtoqueue();
Visible Procedure splitnode();
Visible Procedure nosuggtoqueue();
Visible Procedure fixfocus();
Visible Procedure subsettoqueue();

/* e1que2.c*/
Visible Procedure qshow();

/* e1scrn.c*/
Visible Procedure actupdate();
Visible Procedure virtupdate();
Visible Procedure initterm();
Visible Procedure endterm();
Visible Procedure endshow();
Visible Procedure setindent();
Visible Procedure cmdprompt();

/* e1spos.c */
Visible Procedure initpos();
Visible Procedure endpos();
Visible Procedure delpos();
Visible Procedure movpos();

/* e1sugg.c */
Visible Procedure addsugg();
Visible Procedure acksugg();
Visible Procedure killsugg();
Visible Procedure ackhowsugg();
Visible Procedure killhowsugg();
Visible Procedure check_last_unit();
Visible Procedure readsugg();
Visible Procedure writesugg();
Visible Procedure initcensugg();
Visible Procedure initsugg();
Visible Procedure endsugg();
Visible Procedure endclasses();

/* e1supr.c */
Visible Procedure subgrow();
Visible Procedure subgrsubset();
Visible Procedure shrsubset();
Visible Procedure ritevhole();
Visible Procedure leftvhole();
Visible Procedure s_up();
Visible Procedure s_downi();
Visible Procedure grow();
Visible Procedure shrink();
Visible Procedure s_down();
Visible Procedure s_downrite();
Visible Procedure fixit();

/* i1nua.c */
Visible Procedure app_print();

/* i1nuc.c */
Visible Procedure printnum();

/* i1num.c */
Visible Procedure initapp();
Visible Procedure endapp();
Visible Procedure initnum();
Visible Procedure endnum();
Visible Procedure set_random();

/* i1nur.c */
Visible Procedure rat_init();
Visible Procedure endrat();

/* i1tra.c */
Visible Procedure ins_range();

/* i2ana.c */
Visible Procedure analyze();
Visible Procedure cleanup();

/* i2dis.c */
Visible Procedure display();

/* i2exp.c */
Visible Procedure do_dya();
Visible Procedure reduce();
Visible Procedure selection();
// Visible Procedure initexp(expadm *adm, int n, char level);
Visible Procedure endstack();
Visible Procedure push_item();
Visible Procedure trim_target();

/* i2fix.c */

/* i2gen.c */
Visible Procedure jumpto();
// Visible Procedure fix(parsetree *pt, char flag);
Visible Procedure hold();
Visible Procedure let_go();
Visible Procedure fix_nodes();

/* i2syn.c */
Visible Procedure skipsp();
Visible Procedure findceol();
Visible Procedure req();
Visible Procedure upto();
Visible Procedure need();
Visible Procedure veli();
Visible Procedure upto1();
Visible Procedure initsyn();
Visible Procedure endsyn();
Visible Procedure first_ilev();

/* i3bws.c */
Visible Procedure lst_wss();
Visible Procedure goto_ws();
Visible Procedure initbws();
Visible Procedure endbws();

/* i3com.c */
Visible Procedure idelpos();
Visible Procedure imovpos();

/* i3env.c */
Visible Procedure setprmnv();
Visible Procedure sv_context();
Visible Procedure set_context();
Visible Procedure initenv();
Visible Procedure endenv();
Visible Procedure e_replace();
Visible Procedure e_delete();
Visible Procedure re_env();
Visible Procedure lst_ttgs();
Visible Procedure initprmnv();
Visible Procedure extbnd_tags();
Visible Procedure sethowtoname();

/* i3err.c */

/* i3fil.c */
Visible Procedure f_delete();
Visible Procedure f_close();
Visible Procedure f_rename();

/* i3fpr.c */
Visible Procedure initfpr();
Visible Procedure endfpr();

/* i3imm.c */
Visible Procedure process();

/* i3ini.c */
Visible Procedure endall();
Visible Procedure pre_init();
Visible Procedure checkfileargs();
Visible Procedure init();
Visible Procedure abc();
Visible Procedure crashend();

/* i3int.c */
Visible Procedure execthread();

/* i3in2.c */
Visible Procedure load_global();

/* i3loc.c */
Visible Procedure check_location();
Visible Procedure put();
Visible Procedure put_with_check();
Visible Procedure l_delete();
Visible Procedure l_insert();
Visible Procedure l_remove();
Visible Procedure bindlocation();
Visible Procedure unbind();
Visible Procedure l_del();

/* i3scr.c */
Visible Procedure flushout();
Visible Procedure wri();
Visible Procedure oline();
Visible Procedure writ();
Visible Procedure writnewline();
Visible Procedure read_eg();
Visible Procedure read_raw();
Visible Procedure re_screen();
Visible Procedure init_scr();
Visible Procedure end_scr();
Visible Procedure re_outfile();
Visible Procedure vs_ifile();

/* i3sta.c */
Visible Procedure push();
Visible Procedure ret();
Visible Procedure call_refinement();
Visible Procedure x_user_command();
Visible Procedure endsta();

/* i3typ.c */
Visible Procedure must_agree();

/* e1etex.c */
Visible Procedure e_fstrval();
Visible Procedure e_concto();

/* i1btr.c */
// Visible Procedure relbtree(btreeptr pnode, literal it);
// Visible Procedure uniqlbtreenode(btreeptr *pptr, literal it);

/* i1obj.c */
Visible Procedure rel_subvalues();

/* i1tex.c */
Visible Procedure endstrval();
Visible Procedure fstrval();
Visible Procedure concato();
// Visible Procedure convtext();

/* i1lta.c */

/* i2tca.c */
Visible Procedure type_check();
Visible Procedure initstc();
Visible Procedure endstc();
Visible Procedure del_types();
Visible Procedure adjust_types();
Visible Procedure rectypes();
Visible Procedure put_types();

/* i2tce.c */
Visible Procedure start_vars();
Visible Procedure add_var();
Visible Procedure end_vars();
Visible Procedure setreprtable();
Visible Procedure starterrvars();
Visible Procedure enderrvars();
Visible Procedure badtyperr();
Visible Procedure delreprtable();
Visible Procedure adderrvar();

/* i2tcp.c */
// Visible Procedure putsubtype(polytype sub, polytype u, intlet isub);
Visible Procedure new_externals();
Visible Procedure p_release();
Visible Procedure repl_type_of();
Visible Procedure usetypetable();
Visible Procedure deltypetable();
Visible Procedure initpol();
Visible Procedure endpol();

/* i2tcu.c */
Visible Procedure unify();

/* i4bio.c */
Visible Procedure abcio();
Visible Procedure bioerr();
Visible Procedure bioerrV();

/* i4grp.c */
Visible Procedure rec_wsgroup();

/* i4inp.c */
Visible Procedure abcinput();

/* i4lis.c */
Visible Procedure abclist();

/* i4out.c */
Visible Procedure abcoutput();

/* i4pack.c */
Visible Procedure abcpack();

/* i4rec.c */
Visible Procedure rec_workspace();
Visible Procedure rec_suggestions();

/* trm.c */

#ifdef __cplusplus
}
#endif


#endif
