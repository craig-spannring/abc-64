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

struct gdb_hostile_queue {
	HEADER;
	nodeptr q_data;
	queue   q_link;
};
struct queue {
	literal type;
	reftype refcnt;
	intlet  len FILLER_FIELD;
	nodeptr q_data;
	queue   q_link;
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static struct gdb_hostile_queue old_unused5[0];
static struct queue             new_unused5[0];
STATIC_CHECK(sizeof(old_unused5[0]) == sizeof(new_unused5[0]));
STATIC_CHECK(offsetof(struct gdb_hostile_queue, type)
	     == offsetof(struct queue, type));
STATIC_CHECK(offsetof(struct gdb_hostile_queue, refcnt)
	     == offsetof(struct queue, refcnt));
STATIC_CHECK(offsetof(struct gdb_hostile_queue, len)
	     == offsetof(struct queue, len));
STATIC_CHECK(offsetof(struct gdb_hostile_queue, q_data)
	     == offsetof(struct queue, q_data));
STATIC_CHECK(offsetof(struct gdb_hostile_queue, q_link)
	     == offsetof(struct queue, q_link));
#pragma GCC diagnostic pop

#define Qnil ((queue) Vnil)
#ifdef lint
Visible queue qcopy();
Visible Procedure qrelease();
#else
#define qcopy(q) ((queue)copy((value)q))
#define qrelease(q) release((value)q)
#endif
#define emptyqueue(q) (!(q))

nodeptr queuebehead(queue *pq);

#ifdef __cplusplus
}
#endif


#endif
