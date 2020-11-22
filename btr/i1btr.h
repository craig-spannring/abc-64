/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef I1BTR_h_bb1040275fcdc1f4455c6eab5174a23d
#define I1BTR_h_bb1040275fcdc1f4455c6eab5174a23d

#ifdef __cplusplus
extern "C" {
#endif

/* Private definitions for the b-tree module */

#define EQ ==
#define NE !=

extern bool comp_ok;
#define reqerr(s) interr(s)

/*********************************************************************/
/* items                                                             */
/*********************************************************************/

typedef char texitem;
typedef value lisitem;
typedef struct pair {value k, a;} tabitem;
typedef struct onpair {value ka, u;} keysitem;
typedef union itm {
    texitem c;
    lisitem l;
    tabitem t;
} btritem, *itemarray, *itemptr;

#define Charval(pitm) ((pitm)->c)
#define Keyval(pitm) ((pitm)->l)
#define Ascval(pitm) ((pitm)->t.a)

/* Xt = itemtype, do not change these, their order is used */
#define Ct (0)
#define Lt (1)
#define Tt (2)
#define Kt (3)

/* Itemwidth, used for offset in btreenodes */
typedef char width;
#define Itemwidth(it) (itemwidth[(unsigned int)it])
extern char itemwidth[];	/*  uses: */
#define Cw (sizeof(texitem))
#define Lw (sizeof(lisitem))
#define Tw (sizeof(tabitem))
#define Kw (sizeof(keysitem))


/*********************************************************************/
/* sizes of btrees                                                   */
/*********************************************************************/

#define Bigsize (-1)
#define Stail(r,s) ((r) > Maxint - (s) ? Bigsize : (r)+(s))
#define Ssum(r,s)  ((r) EQ Bigsize || (s) EQ Bigsize ? Bigsize : Stail(r,s))
#define Sincr(r)   ((r) EQ Bigsize ? Bigsize : Stail(r,1))
#define Sadd2(r)   ((r) EQ Bigsize ? Bigsize : Stail(r,2))
#define Sdiff(r,s) ((r) EQ Bigsize || (s) EQ Bigsize ? Bigsize : (r)-(s))
#define Sdecr(r)   ((r) EQ Bigsize ? Bigsize : (r)-(1))

/*********************************************************************/
/* (A,B)-btrees                                                      */
/*********************************************************************/

/* innernodes: using A=6 B=12 */
#define Mininner 5 		/* A - 1 */
#define Maxinner 11 	        /* B - 1 */
/* bottomnodes */
#define Minbottom 11
#define Maxbottom 22
/* rangenodes */
#define Biglim		(Maxbottom+1)

struct gdb_hostile_btrnode {
    HEADER;
    int size;
    char **g;
};
typedef struct btrnode {
    literal type;
    reftype refcnt;
    intlet  len FILLER_FIELD;
    int     size;
    char  **g;
} btreenode, *btreeptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_btrnode old_unused9[0];
static struct btrnode             new_unused9[0];
STATIC_CHECK(sizeof(old_unused9[0]) == sizeof(new_unused9[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_btrnode, type)   == offsetof(struct btrnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_btrnode, refcnt) == offsetof(struct btrnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_btrnode, len)    == offsetof(struct btrnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_btrnode, size)   == offsetof(struct btrnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_btrnode, g)      == offsetof(struct btrnode, g));
#pragma GCC diagnostic pop

struct gdb_hostile_innernode {
    HEADER;
    int size;
    btreeptr pnptr[Maxinner+1]; itemarray iitm;
};
typedef struct innernode {
    literal   type;
    reftype   refcnt;
    intlet    len FILLER_FIELD;
    int       size;
    btreeptr  pnptr[Maxinner+1];
    itemarray iitm;
} innernode, *innerptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_innernode old_unused10[0];
static struct innernode             new_unused10[0];
STATIC_CHECK(sizeof(old_unused10[0]) == sizeof(new_unused10[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, type)   == offsetof(struct innernode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, refcnt) == offsetof(struct innernode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, len)    == offsetof(struct innernode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, size)   == offsetof(struct innernode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, pnptr)  == offsetof(struct innernode, pnptr));
STATIC_CHECK(offsetof(struct gdb_hostile_innernode, iitm)   == offsetof(struct innernode, iitm));
#pragma GCC diagnostic pop

struct gdb_hostile_itexnode {
    HEADER;
    int size;
    btreeptr pnptr[Maxinner+1];
    texitem icitm[Maxinner];
};
typedef struct itexnode {
    literal   type;
    reftype   refcnt;
    intlet    len FILLER_FIELD;
    int       size;
    btreeptr  pnptr[Maxinner+1];
    texitem   icitm[Maxinner];
} itexnode, *itexptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_itexnode old_unused11[0];
static struct itexnode             new_unused11[0];
STATIC_CHECK(sizeof(old_unused11[0]) == sizeof(new_unused11[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, type)   == offsetof(struct itexnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, refcnt) == offsetof(struct itexnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, len)    == offsetof(struct itexnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, size)   == offsetof(struct itexnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, pnptr)  == offsetof(struct itexnode, pnptr));
STATIC_CHECK(offsetof(struct gdb_hostile_itexnode, icitm)  == offsetof(struct itexnode, icitm));
#pragma GCC diagnostic pop

struct gdb_hostile_ilisnode {
    HEADER;
    int size;
    btreeptr pnptr[Maxinner+1]; lisitem ilitm[Maxinner];
};
typedef struct ilisnode {
    literal    type;
    reftype    refcnt;
    intlet     len FILLER_FIELD;
    int        size;
    btreeptr   pnptr[Maxinner+1];
    lisitem    ilitm[Maxinner];
}
ilisnode, *ilisptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_ilisnode old_unused12[0];
static struct ilisnode             new_unused12[0];
STATIC_CHECK(sizeof(old_unused12[0]) == sizeof(new_unused12[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, type)   == offsetof(struct ilisnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, refcnt) == offsetof(struct ilisnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, len)    == offsetof(struct ilisnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, size)   == offsetof(struct ilisnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, pnptr)  == offsetof(struct ilisnode, pnptr));
STATIC_CHECK(offsetof(struct gdb_hostile_ilisnode, ilitm)  == offsetof(struct ilisnode, ilitm));
#pragma GCC diagnostic pop


struct gdb_hostile_itabnode {
    HEADER;
    int size;
    btreeptr pnptr[Maxinner+1];
    tabitem ititm[Maxinner];
};
typedef struct itabnode {
    literal    type;
    reftype    refcnt;
    intlet     len FILLER_FIELD;
    int        size;
    btreeptr   pnptr[Maxinner+1];
    tabitem    ititm[Maxinner];
}
itabnode, *itabptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_itabnode old_unused13[0];
static struct itabnode             new_unused13[0];
STATIC_CHECK(sizeof(old_unused13[0]) == sizeof(new_unused13[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, type)   == offsetof(struct itabnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, refcnt) == offsetof(struct itabnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, len)    == offsetof(struct itabnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, size)   == offsetof(struct itabnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, pnptr)  == offsetof(struct itabnode, pnptr));
STATIC_CHECK(offsetof(struct gdb_hostile_itabnode, ititm)  == offsetof(struct itabnode, ititm));
#pragma GCC diagnostic pop

struct gdb_hostile_bottomnode {
    HEADER;
    int size;
    itemarray bitm;
};
typedef struct bottomnode {
    literal   type;
    reftype   refcnt;
    intlet    len FILLER_FIELD;
    int       size;
    itemarray bitm;
}
bottomnode, *bottomptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_bottomnode old_unused14[0];
static struct bottomnode             new_unused14[0];
STATIC_CHECK(sizeof(old_unused14[0]) == sizeof(new_unused14[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_bottomnode, type)   == offsetof(struct bottomnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_bottomnode, refcnt) == offsetof(struct bottomnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_bottomnode, len)    == offsetof(struct bottomnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_bottomnode, size)   == offsetof(struct bottomnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_bottomnode, bitm)   == offsetof(struct bottomnode, bitm));
#pragma GCC diagnostic pop

struct gdb_hostile_btexnode {
    HEADER;
    int size;
    texitem bcitm[Maxbottom];
};
typedef struct btexnode {
    HEADER;
    int size;
    texitem bcitm[Maxbottom];
}
btexnode, *btexptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_btexnode old_unused15[0];
static struct btexnode             new_unused15[0];
STATIC_CHECK(sizeof(old_unused15[0]) == sizeof(new_unused15[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_btexnode, type)   == offsetof(struct btexnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_btexnode, refcnt) == offsetof(struct btexnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_btexnode, len)    == offsetof(struct btexnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_btexnode, size)   == offsetof(struct btexnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_btexnode, bcitm)  == offsetof(struct btexnode, bcitm));
#pragma GCC diagnostic pop

struct gdb_hostile_blisnode {
    HEADER;
    int size;
    lisitem blitm[Maxbottom];
};
typedef struct blisnode {
    literal type;
    reftype refcnt;
    intlet  len FILLER_FIELD;
    int     size;
    lisitem blitm[Maxbottom];
}
blisnode, *blisptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_blisnode old_unused16[0];
static struct blisnode             new_unused16[0];
STATIC_CHECK(sizeof(old_unused16[0]) == sizeof(new_unused16[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_blisnode, type)   == offsetof(struct blisnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_blisnode, refcnt) == offsetof(struct blisnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_blisnode, len)    == offsetof(struct blisnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_blisnode, size)   == offsetof(struct blisnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_blisnode, blitm)  == offsetof(struct blisnode, blitm));
#pragma GCC diagnostic pop

struct gdb_hostile_btabnode {
    HEADER;
    int size;
    tabitem btitm[Maxbottom];
};
typedef struct btabnode {
    literal type;
    reftype refcnt;
    intlet  len FILLER_FIELD;
    int     size;
    tabitem btitm[Maxbottom];
}
btabnode, *btabptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_btabnode old_unused17[0];
static struct btabnode             new_unused17[0];
STATIC_CHECK(sizeof(old_unused17[0]) == sizeof(new_unused17[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_btabnode, type)   == offsetof(struct btabnode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_btabnode, refcnt) == offsetof(struct btabnode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_btabnode, len)    == offsetof(struct btabnode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_btabnode, size)   == offsetof(struct btabnode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_btabnode, btitm)  == offsetof(struct btabnode, btitm));
#pragma GCC diagnostic pop


struct gdb_hostile_rangenode {
    HEADER;
    int size;
    lisitem lwb, upb;
};
typedef struct rangenode {
    literal type;
    reftype refcnt;
    intlet  len FILLER_FIELD;
    int     size;
    lisitem lwb;
    lisitem upb;
}
rangenode, *rangeptr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_rangenode old_unused18[0];
static struct rangenode             new_unused18[0];
STATIC_CHECK(sizeof(old_unused18[0]) == sizeof(new_unused18[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, type)   == offsetof(struct rangenode, type));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, refcnt) == offsetof(struct rangenode, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, len)    == offsetof(struct rangenode, len));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, size)   == offsetof(struct rangenode, size));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, lwb)    == offsetof(struct rangenode, lwb));
STATIC_CHECK(offsetof(struct gdb_hostile_rangenode, upb)    == offsetof(struct rangenode, upb));
#pragma GCC diagnostic pop



#define Bnil ((btreeptr) 0)

#define Flag(pnode)	((pnode)->type)
#define Inner	'i'
#define Bottom	'b'
#define Irange  '.'
#define Crange  '\''

#define Lim(pnode)	((pnode)->len)
#define Minlim(pnode)	(Flag(pnode) EQ Inner ? Mininner : Minbottom)
#define Maxlim(pnode)	(Flag(pnode) EQ Inner ? Maxinner : Maxbottom)
#define SetRangeLim(pnode) (Size(pnode) EQ Bigsize || Size(pnode) > Maxbottom\
			    ? Biglim : Size(pnode))

#define Size(pnode)	((pnode)->size)

#define Ptr(pnode,l)	(((innerptr) (pnode))->pnptr[l])
/* pointer to item in innernode: */
#define Piitm(pnode,l,w) ((itemptr) (((char*)&(((innerptr) (pnode))->iitm)) + ((l)*(w))))
/* pointer to item in bottomnode: */
#define Pbitm(pnode,l,w) ((itemptr) (((char*)&(((bottomptr) (pnode))->bitm)) + ((l)*(w))))
#define Ichar(pnode,l)	(((itexptr) (pnode))->icitm[l])
#define Bchar(pnode,l)	(((btexptr) (pnode))->bcitm[l])

#define Lwbval(pnode)	(((rangeptr) (pnode))->lwb)
#define Upbval(pnode)	(((rangeptr) (pnode))->upb)
#define Lwbchar(pnode)  (Bchar(Root(Lwbval(pnode)), 0))
#define Upbchar(pnode)  (Bchar(Root(Upbval(pnode)), 0))

#define Maxheight 20        /* should be some function of B */

intlet uflow(intlet n, intlet l, char *cbuf, btreeptr *pbuf, intlet it);

/* Private definitions for grabbing and ref count scheme */

btreeptr grabbtreenode(literal flag, literal it);	/* literal flag, it */
btreeptr copybtree(btreeptr pnode);    	/* btreeptr pnode */
void uniqlbtreenode(btreeptr *pptr, literal it);
btreeptr ccopybtreenode(btreeptr pnode, literal it);	/* btreeptr pnode; literal it */
btreeptr mknewroot(btreeptr ptr0, itemptr pitm0, btreeptr ptr1, literal it);
void relbtree(btreeptr pnode, literal it);

#ifdef __cplusplus
}
#endif


#endif
