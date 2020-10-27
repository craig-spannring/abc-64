/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Width attribute evaluation.
 */

#include "b.h"
#include "b0lan.h"
#include "bedi.h"
#include "etex.h"
#include "node.h"
#include "gram.h"


/*
 * The following convention is used throughout the editor to indicate
 * the sizes of objects.
 * - A zero or positive `width' value means the object contains no
 *   linefeeds.  The width is counted in characters.
 * - A negative `width' means the object (or its children) contains
 *   at leasty one linefeed (return is treated as a linefeed here).
 *   The number of linefeeds is -width.
 *   There is no indication whether the object fits on that number of
 *   physical lines, as logical lines may have arbitrary length.
 *
 * For coordinates the following convention is used.
 * (Note that, in accordance to the convention in curses(3), the
 * `y' coordinate always precedes the `x' coorxdinate.)
 * - `Y' is the line number, counted from the beginning of the unit.
 *   These are logical lines rather than physical lines.
 *   The first line has line number 0.
 * - `X' is the column number.  The first column is 0.  For x < 0,
 *   see the important notice below.
 * - `Level' is the indentation level, indicating where a new line
 *   would start if inserted at the current position.
 *   The initial `x' position of such a line is `level*INDENTSIZE'.
 *
 * ***** IMPORTANT NOTICE *****
 * A special case is x = -1.  This means that the current x position is
 * unknown.  Further output on the same line is suppressed, until a
 * linefeed is encountered.  This feature is necessary because while
 * calculating coordinates, when an object has width < 0, only the y
 * coordinate of the end of that object is known.  In this case, the
 * next non-empty object MUST START WITH A LINEFEED, or it will not
 * be visible on the screen (in practice, a space is sometimes present
 * in the parse tree which is not shown then).
 */


/*
 * Compute the (y, x) coordinates and indent level just before
 * the beginning of the j'th child, if the current node starts
 * at the initial values of (y, x) and level.
 */

Visible Procedure
evalcoord(n, jch, py, px, plevel)
	node n;
	int jch;
	int *py;
	int *px;
	int *plevel;
{
	node nn;
	int i;
	string *rp = noderepr(n);
	int k;
	int y = 0;
	int x = *px;
	int level = *plevel;
	int nch;
	
	nch = Is_etext(n) ? 0 : nchildren(n);
	if (jch > nch)
		jch = nch+1;
	for (i = 0; i < jch; ++i) {
		if (i) {
			nn = child(n, i);
			k = nodewidth(nn);
			if (k < 0) {
				y += -k;
				x = k;
			}
			else if (x >= 0)
				x += k;
		}
		k = Fwidth(rp[i]);
		if (k < 0) {
			y += -k;
			/* The \r in the next line is actually a
			   \n on the Mac.  I forgot what \r was meant
			   for; believe it isn't used. */
			x = /*rp[i][0] == '\r' ? 0 :*/ INDENTSIZE*level;
			x += strlen(rp[i]) - 1;
		}
		else {
			if (x >= 0)
				x += k;
			if (rp[i]) {
				if (rp[i][k] == '\t')
					++level;
				else if (rp[i][k] == '\b')
					--level;
			}
		}
	}

	*py += y;
	*px = x;
	*plevel = level;
}


/*
 * Yield the width of a piece of fixed text as found in a node's repr,
 * excluding \b or \t.  If \n or \r is found, -1 is returned.
 * It assumes that \n or \r only occur as first
 * character, and \b or \t only as last.
 */

Visible int
fwidth(string str)
{
	int c;
	int n = 0;

	if (!str)
		return 0;
	c = str[0];
	if (c == '\r' || c == '\n')
		return -1;
	for (; c; c = *++str)
		++n;
	if (n > 0) {
		c = str[-1];
		if (c == '\t' || c == '\b')
			--n;
	}
	return n;
}


/*
 * Evaluate the width of node n, assuming the widths of its children
 * have correctly been calculated.
 */

Visible int
evalwidth(node n)
	node n;
{
	int w;
	int i;
	string *rp;
	int y = 0;
	int x = 0;
	int nch;
	node nn;

	rp = noderepr(n);
	nch = Is_etext(n) ? 0 : nchildren(n);
	for (i = 0; i <= nch; ++i) {
		if (i) {
			nn = child(n, i);
			w = nodewidth(nn);
			if (w < 0) {
				y += -w;
				x = w;
			}
			else
				x += w;
		}
		w = Fwidth(rp[i]);
		if (w < 0) {
			y += -w;
			x = 0;
		}
		else
			x += w;
	}
	if (y > 0)
		return -y;
	return x;
}
