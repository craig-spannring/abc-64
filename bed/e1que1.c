/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Manipulate queues of nodes, lower levels.
 */

#include "b.h"
#include "bedi.h"
#include "etex.h"
#include "bobj.h"
#include "node.h"
#include "supr.h"
#include "queu.h"
#include "gram.h"
#include "tabl.h"

Forward Hidden bool rest_is_hollow();

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

Visible Procedure
joinqueues(pq, q)
	register queue *pq;
	register queue q;
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

Visible Procedure
preptoqueue(n, pq)
	node n;
	register queue *pq;
{
	register queue q;

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
	q = (queue) mk_compound(2);
	q->q_data = n;
	q->q_link = *pq;
	*pq = q;
}


/*
 * Append a node to the end of a queue (same extras as preptoqueue).
 */

Visible Procedure
addtoqueue(pq, n)
	register queue *pq;
	register node n;
{
	auto queue q = Qnil;

	preptoqueue(n, &q);
	joinqueues(pq, q);
}


/*
 * Push a string onto a queue.
 */

Visible Procedure
stringtoqueue(str, pq)
	register string str;
	register queue *pq;
{
	register value  v;

	if (str == NULL)
		return;
	v = mk_etext(str);
	preptoqueue((node) v, pq);
	release(v);
}

/*
 * Append a string to a queue.
 */

#ifdef NOT_USED

Visible Procedure
addstringtoqueue(pq, str)
	register queue *pq;
	register string str;
{
	register value v = mk_etext(str);

	addtoqueue(pq, (node) v);
	release(v);
}

#endif /* NOT_USED */

/*
 * Get the first node of a queue and delink it ("pop").
 */

Visible node
queuebehead(pq)
	register queue *pq;
{
	register node n;
	register queue q = *pq;

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

Visible Procedure
splitnode(n, pq)
	register node n;
	register queue *pq;
{
	register node nn;
	register string *rp;
	register int i;
	register int sym;

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

Visible bool
resttoqueue(pp, pq)
	register path *pp;
	register queue *pq;
{
	auto queue q = Qnil;
	register path pa = parent(*pp);
	register node n = tree(*pp);
	register int sym = symbol(n);
	/* register markbits x; */

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

Hidden bool rest_is_hollow(n) node n; {
	register node nn;
	register string *rp;
	register int i;
	register int sym;

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

Visible Procedure
nosuggtoqueue(ep, pq)
	register environ *ep;
	queue *pq;
{
	auto queue q = Qnil;
	register int i;
	register string *rp;
	register node n;
	register node nn;
	register int sym;
	string str;

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

Visible bool
issuggestion(ep)
	register environ *ep;
{
	register node n;
	register int nch;
	register int sym;
	register int i;

	if (ep->mode != VHOLE && ep->mode != FHOLE || !(ep->s1&1))
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

Visible bool
fitnode(pp, n)
	register path *pp;
	register node n;
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

Visible int
fitstring(pp, str, alt_c)
	register path *pp;
	register string str;
	int alt_c;
{
	environ dummyenv;
	register node n;
	register int ich;
	register int len;
	register string cp;
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
		       && len < sizeof buf - 1)
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
			treereplace(pp, (node) mk_etext(buf));
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

Visible Procedure
fixfocus(ep, len)
	register environ *ep;
	register int len;
{
	node nn;
	register node n = tree(ep->focus);
	register string *rp;
	register int i = 0;
	register int nch;
	register int w;

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
			if (w < 0 || w >= len && len >= 0) {
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

Visible bool
spacefix(ep)
	environ *ep;
{
	path pa;
	node n;
	string *rp;

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

Visible Procedure
subsettoqueue(n, s1, s2, pq)
	register node n;
	register int s1;
	register int s2;
	register queue *pq;
{
	register string *rp = noderepr(n);

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

Visible string
querepr(qv)
	value qv;
{
	queue q = (queue)qv;
	node n;
	static char buf[1000]; /***** Cannot overflow? *****/
	string cp;
	string sp;
	string *rp;
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
	register string str = stuff;
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
