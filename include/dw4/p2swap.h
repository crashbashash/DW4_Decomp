/* p2swap.h - frame swapping and the GS FINISH queue.
 *
 * A finish function is queued behind the packets submitted so far: the GS FINISH handler calls it once
 * the GS has drawn everything before it. */
#ifndef DW4_P2SWAP_H
#define DW4_P2SWAP_H

typedef struct p2FinishFunc {
    void *memory;                       /* the first record of a pool block keeps the block */
    struct p2FinishFunc *next;
    long long sequence;                 /* the finish predicate of the packet it waits behind */
    void (*func)(struct p2FinishFunc *finish, int arg);
    int arg;
} p2FinishFunc;

#endif
