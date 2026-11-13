#include "dw4/cri/sfdsj.h"

enum { SJ_LIN_FREE = 0, SJ_LIN_DATA = 1 };
#define SJ_ERR_PRM (-3)

/* CRI SJRBF: a ring-buffer SJ with an extra area past the end that mirrors its start, 64 bytes. */
typedef struct SjRbfObj {
    SfdSjVtbl *vtbl;            /* 0x00 */
    int used;                   /* 0x04 */
    void *uuid;                 /* 0x08 */
    int ndata;                  /* 0x0c */
    int nfree;                  /* 0x10 */
    int wpos;                   /* 0x14: free line position */
    int rpos;                   /* 0x18: data line position */
    char *buf;                  /* 0x1c */
    int bsize;                  /* 0x20 */
    int xsize;                  /* 0x24 */
    int flowcnt[2][2];          /* 0x28: per line, bytes taken [0] and put [1] */
    void (*err)(void *obj, int code); /* 0x38 */
    void *errobj;               /* 0x3c */
} SjRbfObj;

void SJERR_CallErr(const char *message);
extern char E2004090215_NULL_pointer_is_specified[];
extern char E2004090216_Specified_handle_is_invalid[];
extern char E2004090220_Illegal_buffer_size[];

/* Gives back the tail of the last chunk taken from a line; it must end at the line's position. */
void SJRBF_UngetChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    int pos;

    if (sj == 0) {
        SJERR_CallErr(E2004090215_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090216_Specified_handle_is_invalid);
        return;
    }
    if (sj->bsize == 0) {
        SJERR_CallErr(E2004090220_Illegal_buffer_size);
        return;
    }
    if (ck->len <= 0 || ck->data == 0) {
        return;
    }
    if (line == SJ_LIN_FREE) {
        pos = (sj->wpos + sj->bsize - ck->len) % sj->bsize;
        if (pos == (ck->data - sj->buf) % sj->bsize) {
            sj->wpos = pos;
            sj->nfree += ck->len;
        } else if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        sj->flowcnt[SJ_LIN_FREE][0] -= ck->len;
    } else if (line == SJ_LIN_DATA) {
        pos = (sj->rpos + sj->bsize - ck->len) % sj->bsize;
        if (pos == (ck->data - sj->buf) % sj->bsize) {
            sj->rpos = pos;
            sj->ndata += ck->len;
        } else if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        sj->flowcnt[SJ_LIN_DATA][0] -= ck->len;
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
}
