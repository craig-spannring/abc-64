/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Manipulate queues of nodes, lower levels.
 */

#include "e1que1.h"

#include "b.h"
#include "bedi.h"
#include "e1deco.h"
#include "e1edoc.h"
#include "e1gram.h"
#include "e1inse.h"
#include "e1node.h"
#include "e1supr.h"
#include "etex.h"
#include "bobj.h"
#include "node.h"
#include "supr.h"
#include "queu.h"
#include "gram.h"
#include "tabl.h"
#include "b1grab.h"

Forward Hidden bool rest_is_hollow(nodeptr n);

#ifdef lint
Visible queue qcopy(q)
     queue q;
{
	return (queue) copy((value) q);
}

Visible Procedure qrelease(q)
     queue q;
{
	release((value) q);
}
#endif

/*
 * Append queue 2 to the end of queue 1.
 */

Visible Procedure joinqueues(queueptr *pq, queueptr q)
{
	if (emptyqueue(q))
		return;
	while (*pq) {
		if (Refcnt(*pq) > 1)
			uniql((value*)pq);
		pq = &(*pq)->q_link;
	}
	*pq = q;
}


/*
 * Prepend a node to a queue ("push").
 * Empty strings and Optional holes are silently discarded.
 */

Visible Procedure preptoqueue(nodeptr n, queueptr *pq)
{
	queueptr q;

	if (Is_etext(n)) {
		if (e_length((value) n) == 0)
			return;
		n = nodecopy(n);
	}
	else { /* Avoid Optional holes */
		if (symbol(n) == Optional)
			return;
		n = nodecopy(n);
	}
	q = (queueptr) mk_compound(2);
	q->q_data = n;
	q->q_link = *pq;
	*pq = q;
}


/*
 * Append a node to the end of a queue (same extras as preptoqueue).
 */

Visible Procedure addtoqueue(queueptr *pq, nodeptr n)
{
	queueptr q = Qnil;

	preptoqueue(n, &q);
	joinqueues(pq, q);
}


/*
 * Push a string onto a queue.
 */

Visible Procedure stringtoqueue(cstring str, queueptr *pq)
{
	value  v;

	if (str == NULL)
		return;
	v = mk_etext(str);
	preptoqueue((nodeptr) v, pq);
	release(v);
}

/*
 * Append a string to a queue.
 */

#ifdef NOT_USED

Visible Procedure
addstringtoqueue(pq, str)
	queue *pq;
	string str;
{
	value v = mk_etext(str);

	addtoqueue(pq, (node) v);
	release(v);
}

#endif /* NOT_USED */

/*
 * Get the first node of a queue and delink it ("pop").
 */

Visible nodeptr queuebehead(queueptr *pq)
{
	nodeptr n;
	queueptr q = *pq;

	Assert(q);

	n = nodecopy(q->q_data);
	*pq = qcopy(q->q_link);
	qrelease(q);
	return n;
}


/*
 * Split a node in successive queue elements which are pushed
 * on the queue using preptoqueue.
 * 'Atomic' nodes (texts and holes) are pushed unadorned.
 */

Visible Procedure splitnode(nodeptr n, queueptr *pq)
{
	nodeptr nn;
	cstring *rp;
	int i;
	int sym;

	if (Is_etext(n)) {
		preptoqueue(n, pq);
		return;
	}
	sym = symbol(n);
	if (sym == Optional)
		return;
	if (sym == Hole) {
		preptoqueue(n, pq);
		return;
	}

	rp = noderepr(n);
	for (i = nchildren(n); i >= 0; --i) {
		if (rp[i] && rp[i][0])
			stringtoqueue(rp[i], pq);
		if (i) {
			nn = child(n, i);
			if (Is_etext(nn) || symbol(nn) != Optional)
				preptoqueue(nn, pq);
		}
	}
}


/*
 * Substitute the focus for its parent, appending the remainder of
 * the parent to the queue.
 * The focus must be the first child and not preceded by fixed text.
 * The focus must be allowed in the place of its parent.
 * If any of these conditions is not met, No is returned and nothing
 * is changed.
 *
 * Do not queue a "hollow" rest, since it seems to be substituted anyway.
 * (timo)
 */

Visible bool resttoqueue(pathptr *pp, queueptr *pq)
{
	queueptr q = Qnil;
	pathptr pa = parent(*pp);
	nodeptr n = tree(*pp);
	int sym = symbol(n);
	/* markbits x; */

	if (!pa || ichild(*pp) != 1
		|| fwidth(noderepr(tree(pa))[0]) != 0 || !allowed(pa, sym))
		return No;

	n = nodecopy(n);
	/* x = marks(n); */
	if (!up(pp)) Abort();
	if (!rest_is_hollow(tree(*pp))) {
		splitnode(tree(*pp), &q);
		noderelease(queuebehead(&q));
		joinqueues(pq, q);
	}
	treereplace(pp, n);
	/* if (x) { */
		/* markpath(pp, x); */ /* Actually, should restore all n's marks? */
	/* } */
	return Yes;
}

Hidden bool rest_is_hollow(nodeptr n) {
	nodeptr nn;
	cstring *rp;
	int i;
	int sym;

	Assert(!Is_etext(n));
	
	rp = noderepr(n);
	for (i = nchildren(n); i >= 0; --i) {
		if (Fwidth(rp[i]) > 0)
			return No;
		if (i > 1) {
			nn = child(n, i);
			if (Is_etext(nn)
			    ||
			    ((sym=symbol(nn)) != Optional
			     &&
			     sym != Hole
			    )
			   )
				return No;
		}
	}
	return Yes;
}

/*
 * Like resttoqueue, but exactly from current position in fixed text.
 * Also, it cannot fail.
 */

Visible Procedure nosuggtoqueue(enviro *ep, queueptr *pq)
{
	queueptr q = Qnil;
	int i;
	cstring *rp;
	nodeptr n;
	nodeptr nn;
	int sym;
	cstring str;

	if (issuggestion(ep))
		return;
	Assert((ep->mode == FHOLE || ep->mode == VHOLE) && (ep->s1&1));

	n = tree(ep->focus);
	rp = noderepr(n);
	for (i = nchildren(n); i > ep->s1/2; --i) {
		if (!Fw_zero(rp[i]))
			stringtoqueue(rp[i], &q);
		nn = child(n, i);
		sym = symbol(nn);
		if (sym != Optional) {
			preptoqueue(nn, &q);
			if (sym != Hole) {
				s_downi(ep, i);
				delfocus(&ep->focus);
				s_up(ep);
			}
		}
	}
	str = rp[i];
	if (str && str[ep->s2]) /* Push partial first text */
		stringtoqueue(str + ep->s2, &q);
	joinqueues(pq, q);
}


/*
 * Check whether the remainder of the current node is all suggestion.
 */

Visible bool issuggestion(enviro *ep)
{
	nodeptr n;
	int nch;
	int sym;
	int i;

	if ((ep->mode != VHOLE && ep->mode != FHOLE) || !(ep->s1&1))
		return No; /* Actually wrong call? */

	n = tree(ep->focus);
	nch = nchildren(n);
	for (i = ep->s1/2 + 1; i <= nch; ++i) {
		sym = symbol(child(n, i));
		if (sym != Hole && sym != Optional)
			return No;
	}
	return Yes;
}


/*
 * See if a node fits in a hole.
 */

Visible bool fitnode(pathptr *pp, nodeptr n)
{
	if (!allowed(*pp, symbol(n)))
		return No;
	treereplace(pp, nodecopy(n));
	return Yes;
}


/*
 * Fit a string in a hole.
 * Returns the number of characters consumed.
 * (This does not have to be the maximum possible, but a reasonable attempt
 * is made.  If the internal buffer is exhausted, it leaves the rest for
 * another call.)
 */

Visible int fitstring(pathptr *pp, cstring str, int alt_c)
{
	enviro dummyenv;
	nodeptr n;
	int ich;
	int len;
	cstring cp;
	int sym;
	char buf[1024];

	Assert(str);
	if (!str[0])
		return 0;
	if (!insguess(pp, str[0], &dummyenv)) {
		if (!alt_c)
			return 0;
		if (!insguess(pp, alt_c, &dummyenv))
			return 0;
	}
	if (Is_etext(tree(*pp)))
		if (!up(pp)) Abort();
	if (dummyenv.mode == FHOLE) {
		cp = noderepr(tree(*pp))[0];
		len = 1;
		if (cp) {
			++str;
			++cp;
			while (*str >= ' ' && *str == *cp) {
				++len;
				++str;
				++cp;
			}
		}
		return len;
	}
	if (dummyenv.mode == VHOLE) {
		buf[0] = str[0];
		++str;
		len = 1;
		n = tree(*pp);
		sym = symbol(n);
		ich = dummyenv.s1/2;
		while (*str && mayinsert(n, ich, len, *str)
		       && (size_t)len < sizeof buf - 1)
		{
			if (len >= 2 && (sym == Name || sym == Keyword)
			    && *str == '.' && *(str-1) == '.') {
				/* no range in Name or Keyword */
				--str;
				--len;
				break;
			}
			buf[len] = *str;
			++str;
			++len;
		}
		if (len > 1) {
			buf[len] = 0;
			if (!downi(pp, ich)) Abort();
			treereplace(pp, (nodeptr) mk_etext(buf));
			if (!up(pp)) Abort();
		}
		return len;
	}
	return 1;
}


/*
 * Set the focus position (some VHOLE/FHOLE setting, probably)
 * at the 'len'th character from the beginning of the current node.
 * This may involve going to a child or moving beyond the current subtree.
 * Negative 'len' values may be given to indicate negative widths;
 * this is implemented incomplete.
 */

Visible Procedure fixfocus(enviro *ep, int len)
{
	nodeptr nn;
	nodeptr n = tree(ep->focus);
	cstring *rp;
	int i = 0;
	int nch;
	int w;

	if (Is_etext(n)) {
		w = e_length((value)n);
		Assert(w >= len && len >= 0);
		if (w > len)
			ep->spflag = No;
		ep->mode = VHOLE;
		ep->s1 = ichild(ep->focus) * 2;
		ep->s2 = len;
		s_up(ep);
		return;
	}
	nch = nchildren(n);
	w = nodewidth(n);
	if (len > w && w >= 0) {
		i = ichild(ep->focus); /* Change initial condition for for-loop */
		if (!up(&ep->focus)) {
			ep->mode = ATEND;
			return;
		}
		higher(ep);
		n = tree(ep->focus);
	}

	rp = noderepr(n);
	for (; i <= nch; ++i) {
		if (i) {
			nn = child(n, i);
			w = nodewidth(nn);
			if (w < 0 || (w >= len && len >= 0)) {
				s_downi(ep, i);
				fixfocus(ep, len);
				return;
			}
			if (len >= 0)
				len -= w;
		}
		w = Fwidth(rp[i]);
		if (w >= len && len >= 0) {
			if (w > len)
				ep->spflag = No;
			ep->mode = FHOLE;
			ep->s1 = 2*i + 1;
			ep->s2 = len;
			return;
		}
		else if (w < 0)
			len = 0;
		else
			len -= w;
	}
	ep->mode = ATEND;
}


/*
 * Apply, if possible, a special fix relating to spaces:
 * when a space has been interpreted as joining character
 * and we end up in the following hole, but we don't succeed
 * in filling the hole; it is then tried to delete the hole
 * and the space.
 * Usually this doesn't occur, but it may occur when inserting
 * after a space that was already fixed on the screen but now
 * deserves re-interpretation.
 */

Visible bool spacefix(enviro *ep)
{
	pathptr pa;
	nodeptr n;
	cstring *rp;

	if (ichild(ep->focus) != 2 || symbol(tree(ep->focus)) != Hole)
		return No;
	pa = parent(ep->focus);
	n = tree(pa);
	rp = noderepr(n);
	if (!Fw_zero(rp[0]) || Fwidth(rp[1]) != 1 || rp[1][0] != ' ')
		return No;
	n = firstchild(n);
	if (!allowed(pa, symbol(n)))
		return No;
	s_up(ep);
	treereplace(&ep->focus, nodecopy(n));
	ep->mode = ATEND;
	ep->spflag = Yes;
	return Yes;
}


/*
 * Prepend a subset of a node to a queue.
 */

Visible Procedure subsettoqueue(nodeptr n, int s1, int s2, queueptr *pq)
{
	cstring *rp = noderepr(n);

	for (; s2 >= s1; --s2) {
		if (s2&1)
			stringtoqueue(rp[s2/2], pq);
		else
			preptoqueue(child(n, s2/2), pq);
	}
}

#ifdef SHOWBUF

/*
 * Produce flat text out of a queue's first line, to show it on screen.
 */

Visible string querepr(value qv)
{
	queueptr q = (queueptr)qv;
	nodeptr n;
	static char buf[1000]; /***** Cannot overflow? *****/
	string cp;
	string sp;
	cstring *rp;
	int nch;
	int i;
	int len;
	value chld;

	cp = buf;
	for (; q; q = q->q_link) {
		n = q->q_data;
		if (Is_etext(n)) {
			for (sp = e_strval((value) n); cp < buf+80 && *sp; ++sp) {
				if (!isprint(*sp) && *sp != ' ')
					break;
				*cp++ = *sp;
			}
			if (*sp == '\n') {
				if (!emptyqueue(q->q_link)) {
					strcpy(cp, " ...");
					cp += 4;
				}
				break;
			}
		}
		else {
			rp = noderepr(n);
			nch = nchildren(n);
			for (i = 0; i <= nch; ++i) {
				if (i > 0) {
					if (Is_etext(child(n, i))) {
						chld= (value) child(n, i);
						len = e_length(chld);
						if (len > 80)
							len = 80;
						strncpy(cp, e_strval(chld), len);
						cp += len;
					}
					else {
						strcpy(cp, "...");
						cp += 3;
					}
				}
				if (Fw_negative(rp[i])) {
					strcpy(cp, " ...");
					cp += 4;
					break;
				}
				if (Fw_positive(rp[i])) {
					strcpy(cp, rp[i]);
					while (*cp)
						++cp;
					if (cp[-1] == '\t' || cp[-1] == '\b')
						--cp;
				}
			}
		}
		if (cp >= buf+80) {
			strcpy(buf+76, "...");
			break;
		}
	}
	*cp = 0;
	return buf;
}

#endif /* SHOWBUF */

#ifdef UNUSED
Visible Procedure dumpqueue(pq, m) queue *pq; string m; {
	char stuff[80];
	string str = stuff;
	FILE *fp;
	static int qdump;
	queue q= *pq;
	node n;
	
	fp= fopen("/userfs4/abc/timo/mark2/ABCENV", "a");
	Assert(fp != NULL);
	
	qdump++;
	fprintf(fp, "+++ QUEUE %d: %s +++\n", qdump, m);

	for (; q; q=q->q_link) {
		fputs("NEXTNODE: ", fp);
		n= q->q_data;
		writenode(n, fp);
		fputc('\n', fp);
	}
	fputs("NILQ\n", fp);
	fclose(fp);
}
#endif
