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

void SJRBF_SetFlowCnt(SjRbfObj *sj, int line, int k, int cnt)
{
    sj->flowcnt[line][k] = cnt;
}
