/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Routines for treating the parse tree as a sequence of lines.
 *
 * WARNING: The routines in this file (and many others!) assume that a
 * `newline' can only occur in the zero'th representation string of a node
 * (i.e., rp[0]).
 */

#include "b.h"
#include "bedi.h"
#include "etex.h"
#include "bobj.h"
#include "node.h"
#include "gram.h"
#include "supr.h"


/*
 * Compute equality of subtrees, based on common descent.
 * Strings are not checked for characterwise equality, but must
 * be the same pointer; other nodes must have the same symbol and
 * their children must be equal in this sense (equal pointers are
 * always used as a shortcut).
 *
 * (Used by screen update algorithm only.)
 */

Visible bool
eqlines(n1, n2)
	node n1;
	node n2;
{
	node nn1;
	node nn2;
	int w1;
	int w2;
	int nch;
	int i;

	if (n1 == n2)
		return Yes;
	if (!Is_Node(n1) || !Is_Node(n2))
		return No;
	if (symbol(n1) != symbol(n2))
		return No;
	nch = nchildren(n1);
	Assert(nch == nchildren(n2));
	for (i = 1; i <= nch; ++i) {
		nn1 = child(n1, i);
		nn2 = child(n2, i);
		w1 = nodewidth(nn1);
		w2 = nodewidth(nn2);
		if (w1 >= 0 && w2 >= 0) {
			if (!eqlines(nn1, nn2))
				return No;
		}
		else {
			if (nn1 == nn2)
				return Yes;
			if (fwidth(noderepr(nn1)[0]) < 0 || fwidth(noderepr(nn2)[0]) < 0)
				return linelen(n1) == linelen(n2);
			return eqlines(nn1, nn2);
		}
	}
	return Yes;
}


/*
 * Compute the length of the line beginning at the current node.
 */

Visible int
linelen(n)
	node n;
{
	node nn;
	string *rp = noderepr(n);
	int w;
	int nch = nchildren(n);
	int i;
	int len = fwidth(rp[0]);

	if (len < 0)
		len = 0;
	for (i = 1; i <= nch; ++i) {
		nn = child(n, i);
		w = nodewidth(nn);
		if (w >= 0)
			len += w;
		else {
			n = nn;
			i = 0;
			nch = nchildren(n);
			rp = noderepr(n);
		}
		w = Fwidth(rp[i]);
		if (w < 0)
			break;
		len += w;
	}
	return len;
}


/*
 * Move the focus to the next line.
 * NB: This is a building block for use in the 'show' module;
 * it cannot set ep->mode or call higher() properly!
 */

Visible bool
nextline(pp)
	path *pp;
{
	node n;
	node nn;
	int w;
	int nch;
	int i = 0;

	for (;;) {
		n = tree(*pp);
		if (nodewidth(n) < 0) {
			nch = nchildren(n);
			while (++i <= nch) {
				nn = child(n, i);
				w = nodewidth(nn);
				if (w < 0) {
					if (!downi(pp, i)) Abort();
					n = tree(*pp);
					if (fwidth(noderepr(n)[0]) < 0)
						return Yes;
					nch = nchildren(n);
					i = 0;
				}
			}
		}
		/* Must go upward in the tree */
		i = ichild(*pp);
		if (!up(pp))
			return No;
	}
}


/*
 * Compute the current line number.  If the current node begins with
 * a `newline', add one because the first character is actually
 * on the next line.
 */

Visible int
lineno(ep)
	environ *ep;
{
	int y;

	y = -focoffset(ep);
	if (y < 0)
		y = 0;
	if (focchar(ep) == '\n')
		++y;
	return y + Ycoord(ep->focus);
}


/*
 * Similarly, compute the current column number.
 * (Hope the abovementioned trick isn't necessary.)
 */

Visible int
colno(ep)
	environ *ep;
{
	int x= focoffset(ep);

	if (x < 0)
		x= 0; /* In fact, give up */
	return x + Xcoord(ep->focus);
}


/*
 * Make the focus exactly one line wide (if at all possible).
 */

Visible Procedure
oneline(ep)
	environ *ep;
{
	node n;
	node nn;
	string *rp;
	int s1;
	int s2;
	int len;
	int ich;
	int nch;

	ich = 1;
	while (nodewidth(tree(ep->focus)) >= 0) {
		ich = ichild(ep->focus);
		if (!up(&ep->focus)) {
			ep->mode = WHOLE;
			higher(ep);
			return;
		}
	}
	higher(ep);
	n = tree(ep->focus);
	nch = nchildren(n);
	rp = noderepr(n);
	for (s1 = 2*ich-1; s1 >= 1; --s1) {
		if (s1&1)
			len = fwidth(rp[s1/2]);
		else {
			nn = child(n, s1/2);
			len = nodewidth(nn);
		}
		if (len < 0)
			break;
	}
	for (s2 = 2*ich+1; s2 <= 2*nch+1; ++s2) {
		if (s2&1)
			len = fwidth(rp[s2/2]);
		else {
			nn = child(n, s2/2);
			len = nodewidth(nn);
		}
		if (len < 0)
			break;
	}
	ep->mode = SUBSET;
	ep->s1 = s1+1;
	ep->s2 = s2-1;
}
