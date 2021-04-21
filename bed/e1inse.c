/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

/*
 * Subroutines (refinements) for ins_string() (see que2.c).
 */

#include "e1inse.h"

#include "b.h"
#include "bedi.h"
#include "etex.h"
#include "bobj.h"
#include "e1gram.h"
#include "e1lexi.h"
#include "e1node.h"
#include "e1que1.h"
#include "e1sugg.h"
#include "node.h"
#include "gram.h"
#include "supr.h"
#include "tabl.h"
#include "code.h"
#include "b1grab.h"

Forward Hidden bool ifmatch(enviro *ep, string *pstr, cstring str, int alt_c);

/*
 * Try to insert the character c in the focus *pp.
 */

Visible bool insguess(pathptr *pp, char c, enviro *ep)
{
	pathptr pa = parent(*pp);
	nodeptr n;
	int sympa = pa ? symbol(tree(pa)) : Rootsymbol;
	int ich = ichild(*pp);
	struct classinfo *ci = table[sympa].r_class[ich-1];
	classptr cp;
	cstring *rp;
	int code = Code(c);
	int sym;
	char buf[2];

#ifdef USERSUGG
	if (isascii(c) && isinclass(Suggestion, ci)
	    && (isalpha(c) || (c == ':' && sympa == Rootsymbol)))
	{
		if (setsugg(pp, c, ep, allows_colon(sympa)))
			return Yes;
	}
#endif /* USERSUGG */
	for (cp = ci->c_insert; *cp; cp += 2) {
		if (cp[0] == code)
			break;
	}
	if (!*cp)
		return No;
	sym = cp[1];
	if (sym >= LEXICAL) {
		buf[0] = c;
		buf[1] = 0;
		treereplace(pp, (nodeptr) mk_etext(buf));
		ep->mode = VHOLE;
		ep->s1 = 2*ich;
		ep->s2 = 1;
		return Yes;
	}
	Assert(sym < TABLEN);
	rp = (cstring*)table[sym].r_repr;
	n = table[sym].r_node;
	if (Fw_zero(rp[0])) {
		buf[0] = c;
		buf[1] = 0;
		setchild(&n, 1, (nodeptr) mk_etext(buf));
		treereplace(pp, n);
		ep->mode = VHOLE;
		ep->s1 = 2;
		ep->s2 = 1;
		return Yes;
	}
	treereplace(pp, n);
	if (c == '\n' || c == '\r') {
		ep->mode = SUBSET;
		ep->s1 = ep->s2 = 2;
	}
	else {
		ep->mode = FHOLE;
		ep->s1 = 1;
		ep->s2 = 1;
	}
	return Yes;
}


/*
 * Test whether character `c' may be inserted in position `s2' in
 * child `ich' of node `n'; that child must be a Text.
 */

Visible bool mayinsert(nodeptr n, int ich, int s2, char c)
{
	int sympa = symbol(n);
	struct classinfo *ci;
	classptr cp;
	value v = (value) child(n, ich);
	char c1;
	bool (*fun1)(char, int) = s2 > 0 ? /*&*/maystart : /*&*/maycontinue;
	bool (*fun2)(char, int) = s2 > 0 ? /*&*/maycontinue : /*&*/maystart;

	Assert(v && v->type == Etex);
	Assert(sympa > 0 && sympa < TABLEN);
	ci = table[sympa].r_class[ich-1];
	Assert(ci && ci->c_class);
	/* c1 = strval(v)[0]; */
	c1= e_ncharval(1, v);
	for (cp = ci->c_class; *cp; ++cp) {
		if (*cp >= LEXICAL && (*fun1)(c1, *cp)) {
			if ((*fun2)(c, *cp))
				return Yes;
		}
	}
	return No;
}


/*
 * Change a Fixed into a Variable node, given a string pointer variable
 * which contains the next characters to be inserted.
 * If the change is not appropriate, No is returned.
 * Otherwise, as many (though maybe zero) characters from the string
 * as possible will have been incorporated in the string node.
 */

Visible bool soften(enviro *ep, string *pstr, int alt_c)
{
	pathptr pa = parent(ep->focus);
	nodeptr n;
	int sympa = pa ? symbol(tree(pa)) : Rootsymbol;
	struct classinfo *ci;
	classptr cp;
	int code;
	cstring repr;
	struct table *tp;
	char buf[1024];

	if (ep->mode == VHOLE && (ep->s1&1))
		ep->mode = FHOLE;
	if (ep->mode != FHOLE || ep->s1 != 1 || ep->s2 <= 0 || !issuggestion(ep))
		return No;
	n = tree(ep->focus);
	repr = noderepr(n)[0];
	if (!repr || !isupper(repr[0]))
		return No;
	if (symbol(n) == Select && repr[ep->s2-1] == ':')
		return No;
	if (symbol(n) == Head)
		return No;
	code = Code(repr[0]);
	ci = table[sympa].r_class[ichild(ep->focus) - 1];
	n = Nnil;
	for (cp = ci->c_insert; *cp; cp += 2) {
		if (cp[0] != code)
			continue;
		if (cp[1] >= TABLEN)
			continue;
		tp = &table[(unsigned int)cp[1]];
		if (Fw_zero(tp->r_repr[0])) {
			Assert(tp->r_class[0]->c_class[0] >= LEXICAL);
			n = tp->r_node;
			break;
		}
	}
	if (!n)
		return No;
	strncpy(buf, repr, ep->s2);
	buf[ep->s2] = 0;
	setchild(&n, 1, (nodeptr) mk_etext(buf));
	if (!mayinsert(n, 1, ep->s2, repr[ep->s2])) {
		if (!**pstr || (!mayinsert(n, 1, ep->s2, **pstr)
			&& (!alt_c || !mayinsert(n, 1, ep->s2, alt_c)))) {
			noderelease(n); /* Don't forget! */
			return No;
		}
	}
	if (!ep->spflag && **pstr && mayinsert(n, 1, ep->s2, **pstr)) {
		do {
			buf[ep->s2] = **pstr;
			++*pstr;
			++ep->s2;
		} while (((size_t)(ep->s2)) < sizeof buf - 1 && **pstr
			 && mayinsert(n, 1, ep->s2, **pstr));
		buf[ep->s2] = 0;
		setchild(&n, 1, (nodeptr) mk_etext(buf));
	}
	treereplace(&ep->focus, n);
	ep->mode = VHOLE;
	ep->s1 = 2;
	return Yes;
}


/*
 * Renew suggestion, or advance in old suggestion.
 * Return Yes if *pstr has been advanced.
 */

Visible bool resuggest(enviro *ep, string *pstr, int alt_c)
{
	struct table *tp;
	struct classinfo *ci;
	classptr cp;
	pathptr pa;
	nodeptr nn;
	nodeptr n = tree(ep->focus);
	cstring *oldrp = noderepr(n);
	int ich = ep->s1/2;
	cstring str = oldrp[ich];
	int oldsym = symbol(n);
	int childsym[MAXCHILD];
	cstring *newrp;
	int sympa;
	int sym;
	int symfound = -1;
	int i;
	int code;
	char buf[15]; /* Should be sufficient for all fixed texts */
	bool ok;
	bool anyok = No;

	if (!str || !**pstr || !issuggestion(ep))
		return No;
	/***** Change this if commands can be prefixes of others! *****/
	/***** Well, they can!
	if (!c)
		return No;
		*****/

	if (ich > 0 && ifmatch(ep, pstr, str, alt_c))
		/* Shortcut: sec. keyword, exact match will do just fine */
		return Yes;
	if (ep->s2 <= 0 || Fw_zero(oldrp[0]))
		return No;
	if (**pstr != ' ' && !isupper(**pstr)
		&& !alt_c && **pstr != '"' && **pstr != '\'' && **pstr != '.')
		/* Shortcut: not a keyword, must match exactly */
		return ifmatch(ep, pstr, str, alt_c);
	for (i = 0; i < ich; ++i) { /* Preset some stuff for main loop */
		if (!oldrp[i])
			oldrp[i] = "";
		childsym[i] = symbol(child(n, i+1));
	}
	Assert(((size_t)(ep->s2 + 1)) < sizeof buf);
	strcpy(buf, oldrp[ich]);
	buf[ep->s2] = alt_c ? alt_c : **pstr;
	buf[ep->s2 + 1] = 0;
	pa = parent(ep->focus);
	sympa = pa ? symbol(tree(pa)) : Rootsymbol;
	ci = table[sympa].r_class[ichild(ep->focus) - 1];
	code = Code(oldrp[0][0]);

	for (cp = ci->c_insert; *cp; cp += 2) {
		if (cp[0] != code)
			continue;
		sym = cp[1];
		if (sym >= TABLEN)
			continue;
		if (sym == oldsym) {
			anyok = Yes;
			continue;
		}
		tp = &table[sym];
		newrp = tp->r_repr;
		ok = Yes;
		for (i = 0; i < ich; ++i) {
			str = newrp[i];
			if (!str)
				str = "";
			if (strcmp(str, oldrp[i])
				|| (childsym[i] != Optional && childsym[i] != Hole
					&& !isinclass(childsym[i], tp->r_class[i]))) {
				ok = No;
				break;
			}
		}
		if (!ok)
			continue;
		str = newrp[i];
		if (!str || strncmp(str, buf, ep->s2+1))
			continue;
		if (anyok) {
			if (!strcmp(str, oldrp[ich]))
				continue; /* Same as it was: no new suggestion */
			symfound = sym;
			break;
		}
		else if (symfound < 0 && strcmp(str, oldrp[ich]))
			symfound = sym;
	}

	if (symfound < 0) {
		return ifmatch(ep, pstr, oldrp[ich], alt_c);
	}
	nn = table[symfound].r_node;
	for (i = 1; i <= ich; ++i) { /* Copy children to the left of the focus */
		sym = symbol(child(n, i));
		if (sym == Optional || sym == Hole)
			continue;
		setchild(&nn, i, nodecopy(child(n, i)));
	}
	treereplace(&ep->focus, nn);
	str = newrp[ich];
	do { /* Find easy continuation */
		++ep->s2;
		++*pstr;
	} while (**pstr && **pstr == str[ep->s2]);
	
	return Yes;
}


/*
 * Refinement for resuggest(): see if there is a match, and if so, find
 * longest match.
 */

Hidden bool ifmatch(enviro *ep, string *pstr, cstring str, int alt_c)
{
	int c = str[ep->s2];

	if (c != **pstr && (!alt_c || c != alt_c))
		return No;
	do {
		++ep->s2;
		++*pstr;
	} while (**pstr && **pstr == str[ep->s2]);
	
	return Yes;
}

