/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BEDI_h_3e5204f0d36fcc21d2c1e4e37e9958be
#define BEDI_h_3e5204f0d36fcc21d2c1e4e37e9958be

#ifdef __cplusplus
extern "C" {
#endif
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1988. */

#define CMDPROMPT ">>> " /* Prompt user for immediate command */

/* Types */

#define Nod 'N'
#define Pat 'P'
#define Etex 'E'
	/* text values in the kernel of the editor are stored
	 * according to the lineair model.
	 */

#define Is_Node(n) (Type(n) == Nod)
#define Is_Pat(p) (Type(p) == Pat)
#define Is_etext(v) (Type(v) == Etex)

typedef struct node *node;
typedef struct path *path;
typedef int markbits;

struct gdb_hostile_node {
	HEADER;
	markbits	n_marks;
	intlet	n_width;
	intlet	n_symbol;
	node	n_child[1];
};
struct node {
	literal  type;
	reftype  refcnt;
	intlet   len FILLER_FIELD; 
	markbits n_marks;
	intlet   n_width;
	intlet   n_symbol;
	node     n_child[1];
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_node old_unused6[0];
static struct node             new_unused6[0];
STATIC_CHECK(sizeof(old_unused6[0]) == sizeof(new_unused6[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_node, type)
	     == offsetof(struct node, type));
STATIC_CHECK(offsetof(struct gdb_hostile_node, refcnt)
	     == offsetof(struct node, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_node, len)
	     == offsetof(struct node, len));
STATIC_CHECK(offsetof(struct gdb_hostile_node, n_marks)
	     == offsetof(struct node, n_marks));
STATIC_CHECK(offsetof(struct gdb_hostile_node, n_width)
	     == offsetof(struct node, n_width));
STATIC_CHECK(offsetof(struct gdb_hostile_node, n_symbol)
	     == offsetof(struct node, n_symbol));
STATIC_CHECK(offsetof(struct gdb_hostile_node, n_child)
	     == offsetof(struct node, n_child));
#pragma GCC diagnostic pop

#define Nnil ((node) Vnil)

#define NodOffset (sizeof(int) + 2*sizeof(intlet))

struct gdb_hostile_path {
	HEADER;
	path	p_parent;
	node	p_tree;
	intlet	p_ichild;
	intlet	p_ycoord;
	intlet	p_xcoord;
	intlet	p_level;
	markbits	p_addmarks;
	markbits	p_delmarks;
};
struct path {
	literal   type;
	reftype   refcnt;
	intlet    len FILLER_FIELD;
	path      p_parent;
	node      p_tree;
	intlet    p_ichild;
	intlet    p_ycoord;
	intlet    p_xcoord;
	intlet    p_level;
	markbits  p_addmarks;
	markbits  p_delmarks;
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_path old_unused7[0];
static struct path             new_unused7[0];
STATIC_CHECK(sizeof(old_unused7[0]) == sizeof(new_unused7[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_path, type)       == offsetof(struct path, type));
STATIC_CHECK(offsetof(struct gdb_hostile_path, refcnt)     == offsetof(struct path, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_path, len)        == offsetof(struct path, len));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_parent)   == offsetof(struct path, p_parent));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_tree)     == offsetof(struct path, p_tree));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_ichild)   == offsetof(struct path, p_ichild));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_ycoord)   == offsetof(struct path, p_ycoord));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_xcoord)   == offsetof(struct path, p_xcoord));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_level)    == offsetof(struct path, p_level));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_addmarks) == offsetof(struct path, p_addmarks));
STATIC_CHECK(offsetof(struct gdb_hostile_path, p_delmarks) == offsetof(struct path, p_delmarks));
#pragma GCC diagnostic pop

#define NilPath ((path) Vnil)


extern int doctype;	/* type of document edited by editdocument() */
#define D_perm 0	/* a how-to definition or permanent location */
#define D_input 1	/* input for READ or question */
#define D_immcmd 2	/* editing immediate command */

#ifdef __cplusplus
}
#endif


#endif
