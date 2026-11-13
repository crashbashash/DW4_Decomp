#include "dw4/cri/sfdsj.h"

/* CRI SJMEM: an SJ over a caller's memory block, 36 bytes. */
typedef struct SjMemObj {
    SfdSjVtbl *vtbl;        /* 0x00 */
    int used;               /* 0x04 */
    void *uuid;             /* 0x08 */
    int ndata;              /* 0x0c */
    int nfree;              /* 0x10 */
    char *buf;              /* 0x14 */
    int bsize;              /* 0x18 */
    void (*err)(void *obj, int code); /* 0x1c */
    void *errobj;           /* 0x20 */
} SjMemObj;

char *SJMEM_GetBufPtr(SjMemObj *sj)
{
    return sj->buf;
}
