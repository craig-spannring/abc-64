/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1986. */

#ifndef QUEU_h_28464c453e1e455b29fec9422c76f353
#define QUEU_h_28464c453e1e455b29fec9422c76f353

#ifdef __cplusplus
extern "C" {
#endif

/*
 * B editor -- Definitions for queues of nodes.
 */

typedef struct queue *queue;

struct queue {
	HEADER;
	node q_data;
	queue q_link;
};

#define Qnil ((queue) Vnil)
#ifdef lint
Visible queue qcopy();
Visible Procedure qrelease();
#else
#define qcopy(q) ((queue)copy((value)q))
#define qrelease(q) release((value)q)
#endif
#define emptyqueue(q) (!(q))

node queuebehead();

#ifdef __cplusplus
}
#endif


#endif
