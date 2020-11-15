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

typedef struct btrnode {
    HEADER; int size;
    char **g;
}
btreenode, *btreeptr;

typedef struct innernode {
    HEADER; int size;
    btreeptr pnptr[Maxinner+1]; itemarray iitm;
}
innernode, *innerptr;

typedef struct itexnode {
    HEADER; int size;
    btreeptr pnptr[Maxinner+1]; texitem icitm[Maxinner];
}
itexnode, *itexptr;

typedef struct ilisnode {
    HEADER; int size;
    btreeptr pnptr[Maxinner+1]; lisitem ilitm[Maxinner];
}
ilisnode, *ilisptr;

typedef struct itabnode {
    HEADER; int size;
    btreeptr pnptr[Maxinner+1]; tabitem ititm[Maxinner];
}
itabnode, *itabptr;

typedef struct bottomnode {
    HEADER; int size;
    itemarray bitm;
}
bottomnode, *bottomptr;

typedef struct btexnode {
    HEADER; int size;
    texitem bcitm[Maxbottom];
}
btexnode, *btexptr;

typedef struct blisnode {
    HEADER; int size;
    lisitem blitm[Maxbottom];
}
blisnode, *blisptr;

typedef struct btabnode {
    HEADER; int size;
    tabitem btitm[Maxbottom];
}
btabnode, *btabptr;

typedef struct rangenode {
    HEADER; int size;
    lisitem lwb, upb;
}
rangenode, *rangeptr;

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
