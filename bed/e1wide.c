/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Commands to make the focus larger and smaller in various ways.
 */

#include "e1wide.h"

#include "b.h"
#include "bedi.h"
#include "e1erro.h"
#include "e1gram.h"
#include "e1line.h"
#include "e1supr.h"
#include "etex.h"
#include "bobj.h"
#include "e1edoc.h"
#include "node.h"
#include "supr.h"
#include "gram.h"
#include "tabl.h"

/*
 * Widen -- make the focus larger.
 */

Visible bool widen(enviro *ep, bool deleting)
{
	nodeptr n;
	nodeptr nn;
	int sym;
	int ich;

	higher(ep);
	grow(ep, deleting);

	n = tree(ep->focus);
	sym = symbol(n);
	if (ep->mode == VHOLE && (ep->s1&1))
		ep->mode = FHOLE;
		
	switch (ep->mode) {

	case ATBEGIN:
	case ATEND:
		/* Shouldn't occur after grow(ep) */
		ep->mode = WHOLE;
		return Yes;

	case VHOLE:
		if (ep->s2 >= lenitem(ep))
			--ep->s2;
		ep->mode = SUBRANGE;
		ep->s3 = ep->s2;
		return Yes;

	case FHOLE:
		if (ep->s2 >= lenitem(ep)) {
			if (ep->s2 > 0)
				--ep->s2;
			else {
				leftvhole(ep);
				switch (ep->mode) {
				case ATBEGIN:
				case ATEND:
					ep->mode = WHOLE;
					return Yes;
				case VHOLE:
				case FHOLE:
					if (ep->s2 >= lenitem(ep)) {
						if (ep->s2 == 0) {
#ifndef NDEBUG
							debug("[Desperate in widen]");
#endif /* NDEBUG */
							ep->mode = SUBSET;
							ep->s2 = ep->s1;
							return widen(ep, deleting);
						}
						--ep->s2;
					}
					ep->mode = SUBRANGE;
					ep->s3 = ep->s2;
					return Yes;
				}
				Abort();
			}
		}
		ep->mode = SUBRANGE;
		ep->s3 = ep->s2;
		return Yes;

	case SUBRANGE:
		ep->mode = SUBSET;
		ep->s2 = ep->s1;
		return Yes;
			
	case SUBSET:
		if (!issublist(sym)) {
			ep->mode = WHOLE;
			return Yes;
		}
		nn= lastchild(n);
		if (nodewidth(nn) == 0) {
			ep->mode = WHOLE;
			return Yes;
		}
		if (ep->s2 < 2*nchildren(n)) {
			ep->mode = SUBLIST;
			ep->s3 = 1;
			return Yes;
		}
		/* Fall through */
	case SUBLIST:
		for (;;) {
			ich = ichild(ep->focus);
			if (!up(&ep->focus)) {
				ep->mode = WHOLE;
				return Yes;
			}
			higher(ep);
			n = tree(ep->focus);
			if (ich != nchildren(n) || !samelevel(sym, symbol(n))) {
				ep->mode = SUBSET;
				ep->s1 = ep->s2 = 2*ich;
				return Yes;
			}
		}
		/* Not reached */
			
	case WHOLE:
		ich = ichild(ep->focus);
		if (!up(&ep->focus))
			return No;
		n = tree(ep->focus);
		if (issublist(symbol(n)) && ich < nchildren(n)) {
			ep->mode = SUBLIST;
			ep->s3 = 1;
		}
		return Yes;

	default:
		Abort();
		return No;
		/* NOTREACHED */
	}
	/* Not reached */
}


/*
 * Narrow -- make the focus smaller.
 */

Visible bool narrow(enviro *ep)
{
	nodeptr n;
	int sym;
	int nch;
	cstring repr;
	
	higher(ep);

	shrink(ep);
	n = tree(ep->focus);
	sym = symbol(n);

	switch (ep->mode) {
		
	case ATBEGIN:
	case ATEND:
	case VHOLE:
	case FHOLE:
		return No;
	
	case SUBRANGE:
		if (ep->s3 > ep->s2)
			ep->s3 = ep->s2;
		else
			ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
		return Yes;
		
	case SUBSET:
		if (ep->s1 <= 2) {
			nch = nchildren(n);	
			if (ep->s2 >= 2*nch && issublist(symbol(n))) {
				if (ep->s1 <= 1) {
					ep->s2 = 2*nch - 1;
					return Yes;
				}
				repr = noderepr(n)[0];
				if (!Fw_positive(repr)) {
					ep->s2 = 2*nch - 1;
					return Yes;
				}
			}
		}
		ep->s2 = ep->s1;
		return Yes;
		
	case SUBLIST:
		Assert(ep->s3 > 1);
		ep->s3 = 1;
		return Yes;
		
	case WHOLE:
		Assert(sym == Hole || sym == Optional);
		return No;
		
	default:
		Abort();
		return No;
		/* NOTREACHED */
	}
}


Visible bool extend(enviro *ep)
{
	nodeptr n;
	int i;
	int len;
	int s1save;
	int sym;

	grow(ep, No);
	higher(ep);
	switch (ep->mode) {

	case VHOLE:
	case FHOLE:
	case ATBEGIN:
	case ATEND:
		return widen(ep, No);

	case SUBRANGE:
		len = lenitem(ep);
		if (ep->s3 < len-1)
			++ep->s3;
		else if (ep->s2 > 0)
			--ep->s2;
		else {
			ep->mode = SUBSET;
			ep->s2 = ep->s1;
			return extend(ep); /* Recursion! */
		}
		return Yes;

	case SUBSET:
		s1save = ep->s1;
		ep->s1 = ep->s2;
		if (nextnnitem(ep)) {
			ep->s2 = ep->s1;
			ep->s1 = s1save;
		}
		else {
			ep->s1 = s1save;
			if (!prevnnitem(ep)) Abort();
		}
		if (ep->s1 == 1 
		    && ((sym= symbol(n= tree(ep->focus))) == Test_suite
		        || sym == Refinement)
		    && ep->s2 == 3)
		{
			oneline(ep);
		}
			
		return Yes;

	case WHOLE:
		return up(&ep->focus);

	case SUBLIST:
		n = tree(ep->focus);
		for (i = ep->s3; i > 1; --i)
			n = lastchild(n);
		if (samelevel(symbol(n), symbol(lastchild(n)))) {
			++ep->s3;
			return Yes;
		}
		ep->mode = WHOLE;
		if (symbol(lastchild(n)) != Optional)
			return Yes;
		return extend(ep); /* Recursion! */

	default:
		Abort();
    return 0;
		/* NOTREACHED */
	}
}


/**
 * Right-Narrow -- make the focus smaller, going to the last item of a list.
 */
Visible bool rnarrow(enviro *ep)
{
	nodeptr n;
	nodeptr nn;
	int i;
	int sym;
	
	higher(ep);

	shrink(ep);
	n = tree(ep->focus);
	sym = symbol(n);
	if (sym == Optional || sym == Hole)
		return No;

	switch (ep->mode) {
		
	case ATBEGIN:
	case ATEND:
	case VHOLE:
	case FHOLE:
		return No;
	
	case SUBRANGE:
		if (ep->s3 > ep->s2)
			ep->s2 = ep->s3;
		else {
			++ep->s2;
			ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
		}
		return Yes;
		
	case SUBSET:
		if (issublist(sym) && ep->s2 >= 2*nchildren(n)) {
			do {
				sym = symbol(n);
				s_downrite(ep);
				n = tree(ep->focus);
			} while (samelevel(sym, symbol(n))
				&& (nn = lastchild(n), nodewidth(nn) != 0));
			ep->mode = WHOLE;
			return Yes;
		}
		ep->s1 = ep->s2;
		return Yes;
		
	case SUBLIST:
		Assert(ep->s3 > 1);
		for (i = ep->s3; i > 1; --i)
			s_downi(ep, nchildren(tree(ep->focus)));
		ep->s3 = 1;
		return Yes;
		
	case WHOLE:
		Assert(sym == Hole || sym == Optional);
		return No;
		
	default:
		Abort();
		return 0;
		/* NOTREACHED */
	}
}
