/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#include "b.h"
#include "b1grab.h"
#include "b1memo.h"
#include "bmem.h"
#include "i1btr.h"
#include "i1lta.h"
#include "i1tlt.h"
#include "i3err.h"

#include <assert.h>

/*********************************************************************/
/* grab, copy, release of btree(node)s                               */
/*********************************************************************/


static int count_grabbtreenode = 0; 
Visible btreeptr
grabbtreenode(pnode_type flag, item_type it)
{
	btreeptr pnode;
	unsigned syz;
	static const intlet isize[]= {
		sizeof(itexnode), sizeof(ilisnode),
		sizeof(itabnode), sizeof(itabnode)};
	static const unsigned int elcount_isize = sizeof(isize) / sizeof(isize[0]);
	static const intlet bsize[]= {
		sizeof(btexnode), sizeof(blisnode),
		sizeof(btabnode), sizeof(btabnode)};
	static const unsigned int elcount_bsize = sizeof(bsize) / sizeof(bsize[0]);
	if (++count_grabbtreenode) {
		// printf("inside grabbtreenode %d\n", count_grabbtreenode);
	}
	switch (flag) {
	case Inner:
		assert((unsigned int)it >= 0 && (unsigned int)it<=elcount_isize); 
		syz= isize[(unsigned int)it];
		break;
	case Bottom:
		assert((unsigned int)it >= 0 && (unsigned int)it<=elcount_bsize); 
		syz= bsize[(unsigned int)it];
		break;
	case Irange:
	case Crange:
		syz = sizeof(rangenode);
		break;
	default:
		assert(0); 
	}
	pnode = (btreeptr) getmem((unsigned) syz);    assert(syz >= sizeof(btreenode));
	Refcnt(pnode) = 1;  /* set pnode->refcnt */
	Flag(pnode) = flag; /* set pnode->type   */
	return(pnode);
}

/* ----------------------------------------------------------------- */

Visible btreeptr copybtree(btreeptr pnode) {
	if (pnode != Bnil && Refcnt(pnode) < Maxrefcnt) ++Refcnt(pnode);
	return(pnode);
}

Visible Procedure uniqlbtreenode(btreeptr *pptr, literal it) {
	if (*pptr NE Bnil && Refcnt(*pptr) > 1) {
		btreeptr qnode = *pptr;
		*pptr = ccopybtreenode(*pptr, it);
		relbtree(qnode, it);
	}
}

Visible btreeptr ccopybtreenode(btreeptr pnode, literal it) {
	intlet limp;
	btreeptr qnode;
	intlet iw;
	
	iw = Itemwidth(it);
	qnode = grabbtreenode(Flag(pnode), it);
	Lim(qnode) = limp = Lim(pnode);
	Size(qnode) = Size(pnode);
	switch (Flag(qnode)) {
	case Inner:
		cpynitms(Piitm(qnode, 0, iw), Piitm(pnode, 0, iw), limp, it);
		cpynptrs(&Ptr(qnode, 0), &Ptr(pnode, 0), limp+1);
		break;
	 case Bottom:
		cpynitms(Pbitm(qnode, 0, iw), Pbitm(pnode, 0, iw), limp, it);
		break;
	case Irange:
	case Crange:
		Lwbval(qnode) = copy(Lwbval(pnode));
		Upbval(qnode) = copy(Upbval(pnode));
		break;
	default:
		syserr(MESS(400, "unknown flag in ccopybtreenode"));
	}
	return(qnode);
}

/* make a new root (after the old ptr0 split) */

Visible btreeptr mknewroot(btreeptr ptr0, itemptr pitm0, btreeptr ptr1, literal it)
{
	int r;
	intlet iw = Itemwidth(it);
	btreeptr qnode = grabbtreenode(Inner, it);
	Ptr(qnode, 0) = ptr0;
	movnitms(Piitm(qnode, 0, iw), pitm0, 1, iw);
	Ptr(qnode, 1) = ptr1;
	Lim(qnode) = 1;
	r= Sincr(Size(ptr0));
	Size(qnode) = Ssum(r, Size(ptr1));
	return(qnode);
}

/* ----------------------------------------------------------------- */

/* release btree */

Visible Procedure relbtree(btreeptr pnode, literal it) {
	width iw;
	
	iw = Itemwidth(it);
	if (pnode == Bnil)
		return;
	if (Refcnt(pnode) == 0) {
		syserr(MESS(401, "releasing unreferenced btreenode"));
		return;
	}
	if (Refcnt(pnode) < Maxrefcnt && --Refcnt(pnode) == 0) {
		intlet l;
		switch (Flag(pnode)) {
		case Inner:
			for (l = 0; l < Lim(pnode); l++) {
				relbtree(Ptr(pnode, l), it);
				switch (it) {
				case Tt:
				case Kt:
					release(Ascval(Piitm(pnode, l, iw)));
				case Lt:
					release(Keyval(Piitm(pnode, l, iw)));
				}
			}
			relbtree(Ptr(pnode, l), it);
			break;
		case Bottom:
			for (l = 0; l < Lim(pnode); l++) {
				switch (it) {
				case Tt:
				case Kt:
					release(Ascval(Pbitm(pnode, l, iw)));
				case Lt:
					release(Keyval(Pbitm(pnode, l, iw)));
				}
			}
			break;
		case Irange:
		case Crange:
			release(Lwbval(pnode));
			release(Upbval(pnode));
			break;
		default:
			syserr(MESS(402, "wrong flag in relbtree()"));
		}
		freemem((ptr) pnode);
	}
}

