/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef BMEM_h_2282670dac9633c717ceb6650539e29c
#define BMEM_h_2282670dac9633c717ceb6650539e29c

#ifdef __cplusplus
extern "C" {
#endif

/* B memory management */

typedef char *ptr;
#define Nil ((ptr) 0)

ptr getmem(unsigned syze);
ptr savestr(char *s);
#define freestr(s) (freemem((ptr)(s)))

#ifdef MEMTRACE
typedef unsigned long address;	/* for PC and symbol table (on a tahoe) */
#define F_ALLOC 'A'
#define F_FREE  'F'
#endif

	struct bufadm {char *buf;  /* point to start of active portion of string */
		       char *pbuf; /* end of string? */
		       char *end; /* end of allocation */ };
typedef struct bufadm bufadm;

#ifdef __cplusplus
}
#endif


#endif
