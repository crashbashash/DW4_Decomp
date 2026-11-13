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
void *memcpy(void *dst, const void *src, unsigned int n);
extern char E2004090213_NULL_pointer_is_specified[];
extern char E2004090214_Specified_handle_is_invalid[];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Puts a chunk on a line: data (copied into the extra area, and from past the end to the start,
 * so the mirror stays whole) or free space. */
void SJRBF_PutChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    int ofs;
    int n;

    if (sj == 0) {
        SJERR_CallErr(E2004090213_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090214_Specified_handle_is_invalid);
        return;
    }
    if (ck->len <= 0 || ck->data == 0) {
        return;
    }
    if (line == SJ_LIN_DATA) {
        ofs = ck->data - sj->buf;
        if (ofs < sj->xsize) {
            memcpy(sj->buf + (sj->bsize + ofs), ck->data, MIN(ck->len, sj->xsize - ofs));
        }
        ofs = ck->data - sj->buf;
        ofs += ck->len;
        if (sj->bsize < ofs) {
            n = MIN(ck->len, ofs - sj->bsize);
            memcpy(sj->buf, sj->buf + (ofs - n), n);
        }
        sj->ndata += ck->len;
        sj->flowcnt[SJ_LIN_DATA][1] += ck->len;
    } else if (line == SJ_LIN_FREE) {
        sj->nfree += ck->len;
        sj->flowcnt[SJ_LIN_FREE][1] += ck->len;
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
}
