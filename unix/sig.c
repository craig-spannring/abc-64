/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */


/*The operating system provides a function signal(s,f)
  that associates function f with the signal s, and returns
  a pointer to the previous function associated with s.
  Then, when signal s occurs, f is called and the function associated with s
  may or may not be reset. Thus f may need to call signal(s,f) again to.
  The code here doesn't depend on either interpretation, always being explicit
  about which handler to use.

  There are two signals that can come from the user: quit and interrupt.
  Interrupt should just stop the interpreter and return to B command level;
  quit should stop the B system completely.
  All other signals are caused by errors (eg memory exhausted)
  or come from outside the program, and are therefore fatal.

  SIG_IGN is the system supplied routine to ignore a signal.
  SIG_DFL is the system supplied default for a signal.
  kill(getpid(), signal) kills the program according to 'signal'

  On BSD systems, SIGTSTP and other signals causing the process to be
  suspended, and SIGCONT and others that are ignored by default,
  must not be caught.  It is assumed that all these are defined
  when SIGTSTP is defined.
*/

#include "b.h"
#include "b1mess.h"
#include "e1scrn.h"
#include "i3err.h"
#include "i3ini.h"

#include <signal.h>
#include <assert.h>
#include <stdio.h>



extern bool vtrmactive;

bool must_handle(int sig)
{
	if (sig >= 32) {
		return 0;
	} else {
		switch (sig)
		{
			// Don't handle the following?
			case SIGURG:
			case SIGSTOP:
			case SIGTSTP:
			case SIGCONT:
			case SIGCHLD:
			case SIGTTIN:
			case SIGTTOU:
			case SIGIO:
			case SIGWINCH:
				return 0;
				break;
		}
	}
	return 1;
}
			
		
void setsig(int sig, void(*handler)(int)) {
	int rc;

	if (sig!=SIGKILL) {
		sigset_t           mask;
		rc = sigfillset(&mask);
		assert(rc==0); // TODO add proper error handling

		struct sigaction   old;
		struct sigaction   action;
		memset(&action, 0, sizeof(action));
		action.sa_handler = handler;
		action.sa_mask    = mask;
		action.sa_flags   = 0;

		// printf("setting up sig %d\n", sig);
		rc = sigaction(sig, &action, &old);
		if (rc == -1) {
			perror("sigaction: ");
			exit(1); 
		}

		if ((old.sa_flags & SA_SIGINFO)==0 && old.sa_handler==SIG_IGN) {
			// If previous handler was ignore, then we'll ignore as well. 
			rc = sigaction(sig, &action, &old);
		}
	}
}
	

Hidden Procedure oops(int sig, int m) {
	signal(sig, SIG_DFL); /* Don't call handler recursive -- just die... */
#ifdef sigmask /* 4.2 BSD */
	sigsetmask(0); /* Don't block signals in handler -- just die... */
#endif
	putmess(m); /* implies fflush */
	crashend();
	putmess(MESS(3900, "*** abc: killed by signal\n"));
#ifndef NDEBUG
	if (vtrmactive)
		endterm(); /* resets terminal modes; doesn't belong here !!! */
	kill(getpid(), sig);
#else
	immexit(-1);
#endif
}

Hidden void burp(int sig) {
	oops(sig, MESS(3901, "*** Oops, I feel suddenly (BURP!) indisposed. I'll call it a day. Sorry.\n"));
	return;
}

Hidden void aog(int sig) {
	oops(sig, MESS(3902, "*** Oops, an act of God has occurred compelling me to discontinue service.\n"));
	return; // shouldn't get here. 
}

Visible bool intrptd= No;

Hidden void intsig(int sig) {   /* sig == SIGINT */
	intrptd= Yes;
	return; 
}

Hidden void fpesig(int sig) { /* sig == SIGFPE */
	signal(SIGFPE, SIG_IGN);
	fpe_signal();
	return;
}

Visible Procedure initsig(void) {
	int i;
	// printf("Initializing %d signals\n", (int)NSIG);
	for (i = 1; i<=NSIG; ++i)
		if (must_handle(i)) setsig(i, burp);
	VOID setsig(SIGINT,  intsig);
	VOID setsig(SIGTRAP, burp);
	VOID setsig(SIGQUIT, aog);
	VOID setsig(SIGTERM, aog);
	VOID setsig(SIGFPE,  fpesig);
}


