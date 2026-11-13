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
extern char E2004090273_NULL_pointer_is_specified[];
extern char E2004090274_Specified_handle_is_invalid[];

/* Appends a chunk to a line: in mode 1 a chunk that continues the line's last chunk lengthens it,
 * otherwise a node is taken from the free list. */
void SJUNI_PutChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck)
{
    SjUniNode **link;
    SjUniNode *node;
    SjUniNode *next;

    if (sj == 0) {
        SJERR_CallErr(E2004090273_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090274_Specified_handle_is_invalid);
        return;
    }
    if (line >= SJUNI_NLINE) {
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        return;
    }
    if (ck->len <= 0 || ck->data == 0) {
        return;
    }
    link = &sj->lines[line];
    node = 0;
    next = *link;
    if (next != 0) {
        /* matching construct: hand search — a backward goto: retail leaves the walk's head unaligned,
           where ee-gcc aligns the head of every for, while and do loop */
again:
        node = next;
        next = node->next;
        link = &node->next;
        if (next != 0) {
            goto again;
        }
    }
    if (sj->mode == 1 && node != 0 && node->ck.data + node->ck.len == ck->data) {
        node->ck.len += ck->len;
        return;
    }
    node = sj->free;
    if (node == 0) {
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        return;
    }
    sj->free = node->next;
    node->ck = *ck;
    node->next = 0;
    *link = node;
}
