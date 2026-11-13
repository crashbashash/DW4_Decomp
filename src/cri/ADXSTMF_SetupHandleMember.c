/* CRI ADXSTM: one file stream read through cvFs into an SJ, 96 bytes. */
#include "dw4/cri/sfdsj.h"

typedef struct AdxStmObj {
    signed char used;           /* 0x00 */
    signed char stat;           /* 0x01 */
    signed char rdflg;          /* 0x02: a cvFs read is in flight */
    signed char rtrycnt;        /* 0x03: failed reads in a row */
    SfdSj *sj;                  /* 0x04 */
    int fd;                     /* 0x08: cvFs handle */
    int fofst;                  /* 0x0c: first sector of the range */
    int fsize;                  /* 0x10: bytes */
    int fsctsz;                 /* 0x14: sectors */
    int maxrdsz;                /* 0x18: bytes taken from the SJ per read */
    int minrdsz;                /* 0x1c: free bytes needed before a read */
    int rdsct;                  /* 0x20: sectors in the current read */
    SfdSjChunk rdck;            /* 0x24 */
    int reqrdsct;               /* 0x2c: sector limit of one read */
    int eos;                    /* 0x30: sector that fires the eos callback */
    int rdbyte;                 /* 0x34 */
    void (*eosfunc)(void *obj); /* 0x38 */
    void *eosobj;               /* 0x3c */
    int buflen;                 /* 0x40: SJ capacity */
    signed char pause;          /* 0x44 */
    signed char busy;           /* 0x45 */
    signed char close_req;      /* 0x46 */
    signed char open_req;       /* 0x47 */
    signed char stop_req;       /* 0x48 */
    signed char opened;         /* 0x49 */
    signed char rtflg;          /* 0x4a: real-time handle */
    char pad75[5];
    int pad80;
    int pad84;
    int curpos;                 /* 0x58: next sector to read */
    int maxsct;                 /* 0x5c: 0xFFFFF = no limit */
} AdxStmObj;

#define ADXSTM_SCT_LEN 2048

enum { ADXSTM_STAT_STOP = 1 };

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

/* matching construct: brute-force store-order search (AdxGrpB) — field stores ordered sj/fsize/fsctsz first, buflen/maxrdsz/minrdsz tail */
void ADXSTMF_SetupHandleMember(AdxStmObj *stm, int fd, int fofst, int fsize, SfdSj *sj)
{
    int nsct;
    int n;

    ADXCRS_Lock();
    stm->sj = sj;
    nsct = fsize / ADXSTM_SCT_LEN;
    stm->fsize = fsize;
    stm->fd = fd;
    nsct += (fsize - nsct * ADXSTM_SCT_LEN) > 0;
    stm->fsctsz = nsct;
    stm->fofst = fofst;
    stm->reqrdsct = 0x200;
    stm->maxsct = 0xFFFFF;
    stm->eos = nsct;
    stm->stat = ADXSTM_STAT_STOP;
    stm->rdflg = 0;
    stm->curpos = 0;
    if (sj != 0) {
        n = sj->vtbl->getNumData(sj, 0);
        n += sj->vtbl->getNumData(sj, 1);
        stm->buflen = n;
        stm->maxrdsz = n;
        stm->minrdsz = n;
    }
    stm->used = 1;
    stm->pause = 0;
    ADXCRS_Unlock();
}
