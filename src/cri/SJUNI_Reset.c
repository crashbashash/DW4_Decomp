#include "dw4/cri/sfdsj.h"

#define SJUNI_NLINE 4
#define SJ_ERR_PRM (-3)

/* A chunk queued on an SJUNI line. */
typedef struct SjUniNode SjUniNode;
struct SjUniNode {
    SjUniNode *next;    /* 0x00 */
    int pad4;
    SfdSjChunk ck;      /* 0x08 */
};

/* CRI SJUNI: an SJ whose lines are lists of chunks drawn from a node pool. */
typedef struct SjUniObj {
    SfdSjVtbl *vtbl;            /* 0x00 */
    signed char used;           /* 0x04 */
    signed char mode;           /* 0x05: 1 merges a chunk that continues the line's last one */
    char pad6[2];
    void *uuid;                 /* 0x08 */
    SjUniNode *pool;            /* 0x0c */
    int npool;                  /* 0x10 */
    SjUniNode *free;            /* 0x14 */
    SjUniNode *lines[SJUNI_NLINE]; /* 0x18 */
    void (*err)(void *obj, int code); /* 0x28 */
    void *errobj;               /* 0x2c */
} SjUniObj;

void SJERR_CallErr(const char *message);
extern char E2004090267_NULL_pointer_is_specified[];
extern char E2004090268_Specified_handle_is_invalid[];

/* Links the node pool into one free list and empties every line. */
void SJUNI_Reset(SjUniObj *sj)
{
    SjUniNode *pool;
    int i;

    if (sj == 0) {
        SJERR_CallErr(E2004090267_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090268_Specified_handle_is_invalid);
        return;
    }
    pool = sj->pool;
    sj->free = pool;
    for (i = 0; i < sj->npool - 1; i++) {
        pool[i].ck.len = 0;
        pool[i].ck.data = 0;
        pool[i].next = &pool[i + 1];
    }
    pool[i].next = 0;
    pool[i].ck.data = 0;
    pool[i].ck.len = 0;
    for (i = SJUNI_NLINE - 1; i >= 0; i--) {
        sj->lines[i] = 0;
    }
}
