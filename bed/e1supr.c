/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * B editor -- Superroutines.
 */

#include "e1supr.h"

#include "b.h"
#include "bedi.h"
#include "etex.h"
#include "bobj.h"
#include "e1edoc.h"
#include "e1eval.h"
#include "e1gram.h"
#include "e1supr.h"
#include "erro.h"
#include "i3err.h"
#include "node.h"
#include "supr.h"
#include "gram.h"
#include "tabl.h"
#include "b1grab.h"

Forward Hidden bool subisnull(nodeptr n, string *rp, int i, bool ignorespaces);
Forward Hidden bool isnull(nodeptr n, string *rp, int i);
Forward Hidden bool nextitem(enviro *ep);
Forward Hidden bool previtem(enviro *ep);
Forward Hidden bool isunititem(enviro *ep);
	
/*
 * Compute the length of the ep->s1'th item of node tree(ep->focus).
 */

Visible int lenitem(enviro *ep)
{
	nodeptr n = tree(ep->focus);
	nodeptr nn;

	if (ep->s1&1) { /* Fixed text */
		string *nr= noderepr(n);
		return fwidth(nr[ep->s1/2]);
	}
	/* Else, variable text or a whole node */
	nn = child(n, ep->s1/2);
	return nodewidth(nn);
}


Visible Procedure subgrow(enviro *ep, bool ignorespaces, bool deleting)
{
	nodeptr n;
	int sym;
	int i;
	int len;
	string repr;

	switch (ep->mode) {
	case ATBEGIN:
	case ATEND:
	case VHOLE:
	case FHOLE:
		ritevhole(ep);
		if ((ep->mode != FHOLE && ep->mode != VHOLE) || lenitem(ep) == 0)
			leftvhole(ep);
		else if (ep->mode == FHOLE && ep->s2 == 0 && ep->s1 > 1) {
			n= tree(ep->focus);
			sym= symbol(n);
			repr= (noderepr(n))[ep->s1/2];
			if (symbol(child(n, ep->s1/2)) == Optional) {
				/* implicit extra widen from optional hole */
				/* e.g. {>?<} -> >{?}< */
				ep->mode= SUBSET;
				ep->s2= --ep->s1;
			}
			else if (!deleting
			    || strchr("()[]{}\"'`:;.", repr[0]) != NULL
			    || (repr[0] == ' ' && sym != Grouped
			        && sym != Grouped_ff && sym != Keyword_list)
			)
				/* widen/extend left before some delimiter */
				/* if deleting: only if this delimiter */
				/* is doomed undeletable */
				leftvhole(ep);
		}
	}

	for (;;) {
		n = tree(ep->focus);
		sym = symbol(n);

		switch (ep->mode) {

		case VHOLE:
		case FHOLE:
			if ((sym == Optional || sym == Hole) && ep->s2 == 0) {
				ep->mode = WHOLE;
				continue;
			}
			if (lenitem(ep) <= 0) {
				ep->mode = SUBSET;
				ep->s2 = ep->s1;
				continue;
			}
			return;

		case ATBEGIN:
		case ATEND:
			if (sym == Optional || sym == Hole) {
				ep->mode = WHOLE;
				continue;
			}
			return;

		case SUBRANGE:
			if (ep->s1&1) {
				string *nr= noderepr(n);
				repr = nr[ep->s1/2];
				len = fwidth(repr);
				if (!ignorespaces) {
				  while (ep->s2 > 0 && repr[ep->s2-1] == ' ')
					--ep->s2;
				  while (ep->s3 < len && repr[ep->s3+1] == ' ')
					++ep->s3;
				}
			}
			else {
				value chld= (value) firstchild(n);
				len = Length(chld);
			}
			if (ep->s2 == 0 && ep->s3 >= len - 1) {
				ep->mode = SUBSET;
				ep->s2 = ep->s1;
				continue;
			}
			return;

		case SUBSET:
			subgrsubset(ep, ignorespaces);
			if (ep->s1 == 1) {
				if (ep->s2 == 2*nchildren(n) + 1) {
					ep->mode = WHOLE;
					continue;
				}
				if (ep->s2 == 2*nchildren(n) - 1 && issublist(sym)) {
					ep->mode = SUBLIST;
					ep->s3 = 1;
					return;
				}
			}
			return;

		case SUBLIST:
			for (i = ep->s3; i > 0; --i)
				n = lastchild(n);
			sym = symbol(n);
			if (sym == Optional) {
				ep->mode = WHOLE;
				continue;
			}
			return;

		case WHOLE:
			ep->s1 = 2*ichild(ep->focus);
			if (up(&ep->focus)) {
				ep->mode = SUBSET;
				ep->s2 = ep->s1;
				higher(ep);
				continue;
			}
			return; /* Leave as WHOLE if there is no parent */

		default:
			Abort();
			/* NOTREACHED */

		}

	}
	/* Not reached */
}

/*
 * Find the largest possible representation of the focus.
 * E.g., a WHOLE can also be represented as a SUBSET of its parent,
 * provided it has a parent.
 * Also, a SUBSET may be extended with some empty left and right
 * items and then look like a WHOLE, etc.
 * This process is repeated until no more improvements can be made.
 */

Visible Procedure grow(enviro *ep, bool deleting)
{
	subgrow(ep, Yes, deleting);
}

/*
 * Ditto to find smallest possible representation.
 */

Visible Procedure shrink(enviro *ep)
{
	nodeptr n;
	int sym;

	for (;;) {
		n = tree(ep->focus);
		sym = symbol(n);

		switch (ep->mode) {

		case WHOLE:
			if (sym == Hole || sym == Optional)
				return;
			ep->mode = SUBSET;
			ep->s1 = 1;
			ep->s2 = 2*nchildren(n) + 1;
			continue;

		case SUBLIST:
			if (sym == Hole || sym == Optional) {
				ep->mode = WHOLE;
				return;
			}
			if (ep->s3 == 1) {
				ep->mode = SUBSET;
				ep->s1 = 1;
				ep->s2 = 2*nchildren(n) - 1;
				continue;
			}
			return;

		case SUBSET:
			if (sym == Hole || sym == Optional) {
				ep->mode = WHOLE;
				return;
			}
			shrsubset(ep);
			if (ep->s1 == ep->s2) {
				if (isunititem(ep)) {
					ep->mode = SUBRANGE;
					ep->s2 = 0;
					ep->s3 = lenitem(ep) - 1;
					return;
				}
				else {
					s_downi(ep, ep->s1/2);
					ep->mode = WHOLE;
					continue;
				}
			}
			return;

		case SUBRANGE:
			if (sym == Optional || sym == Hole)
				ep->mode = WHOLE;
			return;

		case ATBEGIN:
			ritevhole(ep);
			if (ep->mode == ATBEGIN) {
				if (sym == Optional || sym == Hole)
					ep->mode = WHOLE;
				return;
			}
			continue;

		case FHOLE:
		case VHOLE:
			ritevhole(ep);
			if (ep->mode != VHOLE && ep->mode != FHOLE)
				continue;
			sym = symbol(tree(ep->focus));
			if (sym == Optional || (sym == Hole && ep->s2 == 0))
				ep->mode = WHOLE;
			return;

		case ATEND:
			return;

		default:
			Abort();
			/* NOTREACHED */

		}
	}
	/* Not reached */

}


/*
 * Subroutine to find the largest way to describe a SUBSET focus
 * (modulo surrounding blanks and newlines).
 */

#ifdef NOT_USED
Visible Procedure growsubset(environ *ep)
{
	subgrsubset(ep, Yes);
}
#endif

Visible Procedure subgrsubset(enviro *ep, bool ignorespaces)
{
	nodeptr n = tree(ep->focus);
	string *rp = noderepr(n);
	int nch21 = nchildren(n)*2 + 1;
	int i;

	Assert(ep->mode == SUBSET);
	for (i = ep->s1; i > 1 && subisnull(n, rp, i-1, ignorespaces); --i)
		;
	ep->s1 = i;
	for (i = ep->s2; i < nch21 && subisnull(n, rp, i+1, ignorespaces); ++i)
		;
	ep->s2 = i;
}


/*
 * Ditto for the smallest way.
 */

Visible Procedure shrsubset(enviro *ep)
{
	nodeptr n = tree(ep->focus);
	string *rp = noderepr(n);
	int s1 = ep->s1;
	int s2 = ep->s2;

	for (; s1 < s2 && isnull(n, rp, s1); ++s1)
		;
	ep->s1 = s1;
	for (; s2 > s1 && isnull(n, rp, s2); --s2)
		;
	ep->s2 = s2;
}


/*
 * Subroutine for grow/shrink to see whether item i is (almost) invisible.
 */

Hidden bool subisnull(nodeptr n, string *rp, int i, bool ignorespaces)
{
	string repr;
	nodeptr nn;

	if (i&1) { /* Fixed text */
		repr = rp[i/2];
		return !Fw_positive(repr) || (ignorespaces && allspaces(repr));
	}
	nn = child(n, i/2);
	return nodewidth(nn) == 0;
}


Hidden bool isnull(nodeptr n, string *rp, int i)
{
	return subisnull(n, rp, i, Yes);
}

/*
 * Find the rightmost VHOLE which would look the same as the current one.
 */

Visible Procedure ritevhole(enviro *ep)
{
	nodeptr n;
	int ich;
	int len;
	int s1save;

	for (;;) {
		n = tree(ep->focus);
		
		switch (ep->mode) {

		case WHOLE:
			ep->mode = ATEND;
			break;

		case VHOLE:
		case FHOLE:
			len = lenitem(ep);
			Assert(len >= 0);
			if (ep->s2 < len)
				return; /* Hole in middle of string */
			s1save = ep->s1;
			if (nextitem(ep)) {
				if (isunititem(ep)) {
					ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
					ep->s2 = 0;
				}
				else if (fwidth(noderepr(child(n, ep->s1/2))[0]) < 0) {
					/* Next item begins with newline -- avoid */
					ep->s1 = s1save;
					return;
				}
				else {
					s_downi(ep, ep->s1/2);
					ep->mode = ATBEGIN;
				}
				break;
			}
			ep->mode = ATEND;
			/* Fall through */
		case ATEND:
			if (!parent(ep->focus) || nodewidth(n) < 0)
				return;
			ich = ichild(ep->focus);
			ep->s1 = 2*ich;
			s_up(ep);
			if (nextitem(ep)) {
                                /* Note -- negative width cannot occur 
                                 * (see test above) [says Guido]
                                 */
				if (isunititem(ep)) {
					ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
					ep->s2 = 0;
				}
				else {
					ep->mode = ATBEGIN;
					s_downi(ep, ep->s1/2);
				}
				break;
			}
			continue;

		case ATBEGIN:
			if (fwidth(noderepr(n)[0]) < 0)
				return; /* Already at dangerous position */
			ep->mode = FHOLE;
			ep->s1 = 1;
			ep->s2 = 0;
			continue;

		default:
			Abort();
			/* NOTREACHED */

		}
	}
}


/*
 * Ditto to the left.
 */

Visible Procedure leftvhole(enviro *ep)
{
	int ich;

	for (;;) {
		switch (ep->mode) {

		case WHOLE:
			ep->mode = ATBEGIN;
			break;

		case VHOLE:
		case FHOLE:
			if (ep->s2 > 0)
				return;
			if (previtem(ep)) {
				if (isunititem(ep)) {
					ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
					ep->s2 = lenitem(ep);
				}
				else {
					s_downi(ep, ep->s1/2);
					ep->mode = ATEND;
				}
			}
			else if (fwidth(noderepr(tree(ep->focus))[0]) < 0)
				return;
			else
				ep->mode = ATBEGIN;
			continue;

		case ATBEGIN:
			ich = ichild(ep->focus);
			if (!up(&ep->focus))
				return;
			higher(ep);
			ep->s1 = 2*ich;
			if (prevnnitem(ep)) {
				if (isunititem(ep)) {
					ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
					ep->s2 = lenitem(ep);
				}
				else {
					s_downi(ep, ep->s1/2);
					ep->mode = ATEND;
				}
			}
			else if (fwidth(noderepr(tree(ep->focus))[0]) < 0) {
				s_downi(ep, ich); /* Undo up */
				return;
			}
			else
				ep->mode = ATBEGIN;
			continue;

		case ATEND:
			lastnnitem(ep);
			if (isunititem(ep)) {
				ep->s2 = lenitem(ep);
				ep->mode = (ep->s1&1) ? FHOLE : VHOLE;
			}
			else
				s_downi(ep, ep->s1/2);
			continue;

		default:
			Abort();

		}
	}
}


/*
 * Safe up, downi, left and rite routines:
 * 1) Rather die than fail;
 * 2) Update ep->highest properly.
 */

Visible Procedure s_up(enviro *ep)
{
	if (!up(&ep->focus))
		syserr(MESS(7100, "s_up failed"));
	higher(ep);
}

Visible Procedure s_downi(enviro *ep, int i)
{
	if (!downi(&ep->focus, i))
		syserr(MESS(7101, "s_downi failed"));
}

Visible Procedure s_down(enviro *ep)
{
	if (!down(&ep->focus))
		syserr(MESS(7102, "s_down failed"));
}

Visible Procedure s_downrite(enviro *ep)
{
	if (!downrite(&ep->focus))
		syserr(MESS(7103, "s_downrite failed"));
}

#ifdef NOT_USED
Visible Procedure s_left(environ *ep)
{
	int ich = ichild(ep->focus);

	s_up(ep);
	s_downi(ep, ich-1);
}
#endif

#ifdef NOT_USED
Visible Procedure s_rite(environ *ep)
{
	int ich = ichild(ep->focus);

	s_up(ep);
	s_downi(ep, ich+1);
}
#endif

/*
 * Find next item in a subset, using ep->s1 as index.
 * (This used to be less trivial, so it's still a subroutine rather than
 * coded in-line or as a macro.)
 */

Hidden bool nextitem(enviro *ep)
{
	if (ep->s1 >= 2*nchildren(tree(ep->focus)) + 1)
		return No; /* Already at last item */
	++ep->s1;
	return Yes;
}


/*
 * Ditto for previous.
 */

Hidden bool previtem(enviro *ep)
{
	if (ep->s1 <= 1
      || (ep->s1 == 2 && fwidth(noderepr(tree(ep->focus))[0]) < 0))
		return No; /* Already at first item */
	--ep->s1;
	return Yes;
}


/*
 * Test whether item ep->s1 is "small", i.e., fixed or varying text
 * but not a whole subtree.
 */

Hidden bool isunititem(enviro *ep)
{
	if (ep->s1&1)
		return Yes;
	return Is_etext(child(tree(ep->focus), ep->s1/2));
}


/*
 * Check for consistent mode information.
 */

Visible bool checkep(enviro *ep)
{
	switch (ep->mode) {

	case FHOLE:
		if (!(ep->s1&1))
			break;
		if (ep->s2 < 0 || ep->s2 > lenitem(ep))
			break;
		return Yes;

	case VHOLE:
		if (!(ep->s1&1)) {
			if (!Is_etext(child(tree(ep->focus), ep->s1/2)))
				break;
		}
		if (ep->s2 < 0 || ep->s2 > lenitem(ep))
			break;
		return Yes;

	case SUBSET:
		if (ep->s2 == ep->s1 && isunititem(ep) && lenitem(ep) <= 0)
			break;
		return Yes;

	default:
		return Yes;

	}
#ifndef NDEBUG
	dbmess(ep);
#endif /* NDEBUG */
	return No;
}


/*
 * Like {next,prev,first,last}item, but with empty items skipped
 * (i.e., those with length <= 0).
 */

Visible bool nextnnitem(enviro *ep)
{
	int s1save = ep->s1;

	while (nextitem(ep)) {
		if (lenitem(ep) != 0)
			return Yes;
	}
	ep->s1 = s1save;
	return No;
}

Visible bool prevnnitem(enviro *ep)
{
	int s1save = ep->s1;
	int len;

	while (previtem(ep)) {
		len = lenitem(ep);
		if (len > 0 || (len < 0 && ep->s1 > 1))
			return Yes;
	}
	ep->s1 = s1save;
	return No;
}

#ifdef NOT_USED
Visible Procedure firstnnitem(environ *ep)
{
	ep->s1 = fwidth(noderepr(tree(ep->focus))[0]) < 0 ? 2 : 1;
	while (lenitem(ep) == 0) {
		if (!nextitem(ep))
			break;
	}
	return;
}
#endif

Visible Procedure lastnnitem(enviro *ep)
{
	ep->s1 = 2*nchildren(tree(ep->focus)) + 1;
	while (lenitem(ep) == 0) {
		if (!previtem(ep))
			break;
	}
	return;
}


/*
 * Prepare the focus for insertion.
 * If the focus isn't a hole, make a hole just before it which becomes the
 * new focus.
 * Also repair strange statuses left by moves, so we may have more chance
 * to insert a character.
 */

Visible Procedure fixit(enviro *ep)
{
	/* First, make a hole if it's not already a hole. */

	switch (ep->mode) {

	case FHOLE:
		break;

	case VHOLE:
		if (ep->s1&1)
			ep->mode = FHOLE;
		break;

	case SUBRANGE:
		if (ep->s1&1)
			ep->mode = FHOLE;
		else
			ep->mode = VHOLE;
		break;

	case SUBSET:
		if (ep->s1&1) {
			if (ep->s1 == 1)
				ep->mode = ATBEGIN;
			else {
				ep->mode = FHOLE;
				ep->s2 = 0;
			}
		}
		else if (Is_etext(child(tree(ep->focus), ep->s1/2))) {
			ep->mode = VHOLE;
			ep->s2 = 0;
		}
		else {
			s_downi(ep, ep->s1/2);
			ep->mode = ATBEGIN;
		}
		break;

	case ATBEGIN:
	case SUBLIST:
	case WHOLE:
		ep->mode = ATBEGIN;
		break;

	case ATEND:
		break;

	default:
		Abort();
	}

	leftvhole(ep);
	if (ep->mode == ATEND && symbol(tree(ep->focus)) == Hole)
		ep->mode = WHOLE; /***** Experiment! *****/
}


/*
 * Small utility to see if a string contains only spaces
 * (this is true for the empty string "").
 * The string pointer must not be null!
 */

Visible bool allspaces(string str)
{
	Assert(str);
	for (; *str; ++str) {
		if (*str != ' ')
			return No;
	}
	return Yes;
}


/*
 * Function to compute the actual width of the focus.
 */

Visible int focwidth(enviro *ep)
{
	nodeptr nn;
	nodeptr n = tree(ep->focus);
	string *rp = noderepr(n);
	int i;
	int w;
	int len = 0;

	switch (ep->mode) {

	case VHOLE:
	case FHOLE:
	case ATEND:
	case ATBEGIN:
		return 0;

	case WHOLE:
		return nodewidth(n);

	case SUBRANGE:
		return ep->s3 - ep->s2 + 1;

	case SUBSET:
		for (i = ep->s1; i <= ep->s2; ++i) {
			if (i&1)
				w = fwidth(rp[i/2]);
			else {
				nn = child(n, i/2);
				w = nodewidth(nn);
			}
			if (w < 0 && len >= 0)
				len = w;
			else if (w >= 0 && len < 0)
				;
			else
				len += w;
		}
		return len;

	case SUBLIST:
		len = nodewidth(n);
		for (i = ep->s3; i > 0; --i)
			n = lastchild(n);
		w = nodewidth(n);
		if (w < 0 && len >= 0)
			return w;
		if (w >= 0 && len < 0)
			return len;
		return len - w;

	default:
		Abort();
		return 0;
		/* NOTREACHED */
	}
}


/*
 * Compute the offset of the focus from the beginning of the current node.
 * This may be input again to fixfocus to allow restoration of this position.
 */

Visible int focoffset(enviro *ep)
{
	nodeptr nn;
	nodeptr n;
	string *rp;
	int w;
	int len;
	int i;

	switch (ep->mode) {

	case WHOLE:
	case SUBLIST:
		return 0;

	case ATBEGIN:
		return ep->spflag;

	case ATEND:
		w = nodewidth(tree(ep->focus));
		if (w < 0)
			return w;
		return w + ep->spflag;

	case SUBSET:
	case FHOLE:
	case VHOLE:
	case SUBRANGE:
		n = tree(ep->focus);
		rp = noderepr(n);
		len = 0;
		for (i = 1; i < ep->s1; ++i) {
			if (i&1)
				w = Fwidth(rp[i/2]);
			else {
				nn = child(n, i/2);
				w = nodewidth(nn);
			}
			if (w < 0) {
				if (len >= 0)
					len = w;
				else
					len += w;
			}
			else if (len >= 0)
				len += w;
		}
		if (ep->mode == SUBSET || len < 0)
			return len;
		return len + ep->s2 + ep->spflag;

	default:
		Abort();
		return 0;
		/* NOTREACHED */
	}
}

/*
 * Return the first character of the focus (maybe '\n'; 0 if zero-width).
 */

Visible int focchar(enviro *ep)
{
	nodeptr n = tree(ep->focus);
	string *rp;
	int i;
	int c;

	switch (ep->mode) {

	case VHOLE:
	case FHOLE:
	case ATBEGIN:
	case ATEND:
		return 0;

	case WHOLE:
	case SUBLIST:
		return nodechar(n);

	case SUBSET:
		rp = noderepr(n);
		for (i = ep->s1; i <= ep->s2; ++i) {
			if (i&1) {
				if (!Fw_zero(rp[i/2]))
				return rp[i/2][0];
			}
			else {
				c = nodechar(child(n, i/2));
				if (c)
					return c;
			}
		}
		return 0;

	case SUBRANGE:
		if (ep->s1&1) {
			string *nr= noderepr(n);
			return nr[ep->s1/2][ep->s2];
		}
		else {
			Assert(Is_etext(child(n, ep->s1/2)));
			return e_ncharval(ep->s2 + 1, (value) child(n, ep->s1/2));
		}

	default:
		Abort();
		return 0;
		/* NOTREACHED */

	}
}


/*
 * Subroutine to return first character of node.
 */

Visible int nodechar(nodeptr n)
{
	string *rp;
	int nch;
	int i;
	int c;

	if (Is_etext(n))
/*		return strval((value)n)[0]; */
		return e_ncharval(1, (value) n);
	rp = noderepr(n);
	if (!Fw_zero(rp[0]))
		return rp[0][0];
	nch = nchildren(n);
	for (i = 1; i <= nch; ++i) {
		c = nodechar(child(n, i));
		if (c)
			return c;
		if (!Fw_zero(rp[i]))
			return rp[i][0];
	}
	return 0;
}


/*
 * Function to compute the actual indentation level at the focus.
 */

Visible int focindent(enviro *ep)
{
	int y = Ycoord(ep->focus);
	int x = Xcoord(ep->focus);
	int level = Level(ep->focus);
	nodeptr n = tree(ep->focus);

	switch (ep->mode) {

	case WHOLE:
	case ATBEGIN:
	case SUBLIST:
		break;

	case ATEND:
		evalcoord(n, 1 + nchildren(n), &y, &x, &level);
		break;

	case SUBSET:
	case FHOLE:
	case VHOLE:
		evalcoord(n, ep->s1/2, &y, &x, &level);
		break;

	default:
		Abort();
	}
	return level;
}


/*
 * Routines to move 'environ' structures.
 */

Procedure emove(enviro *s,	enviro *d)
{
#ifdef STRUCTASS
	*d = *s;
#else /* !STRUCTASS */
	d->focus = s->focus;

	d->mode = s->mode;
	d->copyflag = s->copyflag;
	d->spflag = s->spflag;
	d->changed = s->changed;

	d->s1 = s->s1;
	d->s2 = s->s2;
	d->s3 = s->s3;

	d->highest = s->highest;

	d->copybuffer = s->copybuffer;
#ifdef RECORDING
	d->oldmacro = s->oldmacro;
	d->newmacro = s->newmacro;
#endif /* RECORDING */

	d->generation = s->generation;
#endif /* !STRUCTASS */
}

void ecopy(enviro *s, enviro *d)
{
	emove(s, d);
	VOID pathcopy(d->focus);
	VOID copy(d->copybuffer);
#ifdef RECORDING
	VOID copy(d->oldmacro);
	VOID copy(d->newmacro);
#endif /* RECORDING */
}

void erelease(enviro* ep)
{
	pathrelease(ep->focus);
	release(ep->copybuffer);
#ifdef RECORDING
	release(ep->oldmacro);
	release(ep->newmacro);
#endif /* RECORDING */
}

/*
 * Routines to move 'environ' structures.
 */

Visible bool ev_eq(enviro *l, enviro *r)
{
	if (l->focus == r->focus
	    && l->mode == r->mode
	    && l->copyflag == r->copyflag
	    && l->spflag == r->spflag
	    && l->changed == r->changed
	    && l->s1 == r->s1
	    && l->s2 == r->s2
	    && l->s3 == r->s3
	    && (l->highest == r->highest || l->highest == Maxintlet)
	    && l->copybuffer == r->copybuffer
#ifdef RECORDING
	    && l->oldmacro == r->oldmacro
	    && l->newmacro == r->newmacro
#endif /* RECORDING */
	)
		return Yes;
	else
		return No;
}
