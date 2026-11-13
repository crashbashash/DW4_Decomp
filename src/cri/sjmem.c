/* CRI SJMEM: a stream joint over a memory block the caller owns. Its data line hands out the block
 * front to back; nothing is ever free to put back. Every entry point takes SJCRS around the work. */
#include "dw4/cri/sfdsj.h"

#define SJMEM_MAX_OBJ 32

/* stream joint lines */
enum {
    SJ_LIN_FREE = 0,
    SJ_LIN_DATA = 1
};

/* the code a stream joint hands its error callback for a line it does not have */
#define SJ_ERR_ILLEGAL_LINE (-3)

typedef void (*SjErrFunc)(void *obj, int code);

typedef struct SjMem {
    SfdSjVtbl *vtbl;    /* 0x00 */
    int used;           /* 0x04 */
    const void *uuid;   /* 0x08 */
    int ndata;          /* 0x0c: bytes left to read */
    int rpos;           /* 0x10: read offset into buf */
    char *buf;          /* 0x14 */
    int bsize;          /* 0x18 */
    SjErrFunc errfn;    /* 0x1c */
    void *errobj;       /* 0x20 */
} SjMem;

void *memset(void *dst, int value, unsigned int size);
void SJERR_CallErr(const char *message);
void SJCRS_Lock(void);
void SJCRS_Unlock(void);

extern SfdSjVtbl sjmem_vtbl;
extern int sjmem_init_cnt;
extern SjMem sjmem_obj[SJMEM_MAX_OBJ];
extern const char sjmem_uuid[];
extern char SJMEM_Error[];
extern char E2004090231_NULL_pointer_is_specified[];
extern char E2004090232_Specified_handle_is_invalid[];
extern char E2004090233_NULL_pointer_is_specified[];
extern char E2004090234_Specified_handle_is_invalid[];
extern char E2004090235_NULL_pointer_is_specified[];
extern char E2004090236_Specified_handle_is_invalid[];
extern char E2004090237_NULL_pointer_is_specified[];
extern char E2004090238_Specified_handle_is_invalid[];
extern char E2004090241_NULL_pointer_is_specified[];
extern char E2004090242_Specified_handle_is_invalid[];
extern char E2004090243_NULL_pointer_is_specified[];
extern char E2004090244_Specified_handle_is_invalid[];
extern char E2004090245_NULL_pointer_is_specified[];
extern char E2004090246_Specified_handle_is_invalid[];
extern char E2004090247_NULL_pointer_is_specified[];
extern char E2004090248_Specified_handle_is_invalid[];

void sjmem_Reset(SjMem *sj);

void sjmem_Error(void *obj, int code)
{
    SJERR_CallErr(SJMEM_Error);
}

void sjmem_Init(void);

void SJMEM_Init(void)
{
    SJCRS_Lock();
    sjmem_Init();
    SJCRS_Unlock();
}

void sjmem_Init(void)
{
    if (sjmem_init_cnt == 0) {
        memset(sjmem_obj, 0, sizeof(sjmem_obj));
    }
    sjmem_init_cnt++;
}

void sjmem_Finish(void);

void SJMEM_Finish(void)
{
    SJCRS_Lock();
    sjmem_Finish();
    SJCRS_Unlock();
}

void sjmem_Finish(void)
{
    if (--sjmem_init_cnt == 0) {
        memset(sjmem_obj, 0, sizeof(sjmem_obj));
    }
}

SjMem *sjmem_Create(char *buf, int bsize);

SjMem *SJMEM_Create(char *buf, int bsize)
{
    SjMem *sj;

    SJCRS_Lock();
    sj = sjmem_Create(buf, bsize);
    SJCRS_Unlock();
    return sj;
}

SjMem *sjmem_Create(char *buf, int bsize)
{
    SjMem *sj;
    int i;

    for (i = 0; i < SJMEM_MAX_OBJ; i++) {
        if (sjmem_obj[i].used == 0) {
            break;
        }
    }
    if (i == SJMEM_MAX_OBJ) {
        return 0;
    }
    sj = &sjmem_obj[i];
    sj->used = 1;
    sj->vtbl = &sjmem_vtbl;
    sj->buf = buf;
    sj->bsize = bsize;
    sj->uuid = sjmem_uuid;
    sj->errfn = sjmem_Error;
    sj->errobj = sj;
    sjmem_Reset(sj);
    return sj;
}

void sjmem_Destroy(SjMem *sj);

void SJMEM_Destroy(SjMem *sj)
{
    SJCRS_Lock();
    sjmem_Destroy(sj);
    SJCRS_Unlock();
}

void sjmem_Destroy(SjMem *sj)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090231_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090232_Specified_handle_is_invalid);
        return;
    }
    memset(sj, 0, sizeof(*sj));
    sj->used = 0;
}

const void *sjmem_GetUuid(SjMem *sj);

const void *SJMEM_GetUuid(SjMem *sj)
{
    const void *uuid;

    SJCRS_Lock();
    uuid = sjmem_GetUuid(sj);
    SJCRS_Unlock();
    return uuid;
}

const void *sjmem_GetUuid(SjMem *sj)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090233_NULL_pointer_is_specified);
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090234_Specified_handle_is_invalid);
        return 0;
    }
    return sj->uuid;
}

void sjmem_EntryErrFunc(SjMem *sj, SjErrFunc errfn, void *errobj);

void SJMEM_EntryErrFunc(SjMem *sj, SjErrFunc errfn, void *errobj)
{
    SJCRS_Lock();
    sjmem_EntryErrFunc(sj, errfn, errobj);
    SJCRS_Unlock();
}

void sjmem_EntryErrFunc(SjMem *sj, SjErrFunc errfn, void *errobj)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090235_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090236_Specified_handle_is_invalid);
        return;
    }
    sj->errfn = errfn;
    sj->errobj = errobj;
}

void SJMEM_Reset(SjMem *sj)
{
    SJCRS_Lock();
    sjmem_Reset(sj);
    SJCRS_Unlock();
}

void sjmem_Reset(SjMem *sj)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090237_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090238_Specified_handle_is_invalid);
        return;
    }
    sj->ndata = sj->bsize;
    sj->rpos = 0;
}

int SJMEM_GetNumData(SjMem *sj, int line)
{
    if (line == SJ_LIN_DATA) {
        return sj->ndata;
    }
    if (line != SJ_LIN_FREE) {
        if (sj->errfn != 0) {
            sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
        }
    }
    return 0;
}

void sjmem_GetChunk(SjMem *sj, int line, int nbyte, SfdSjChunk *ck);

void SJMEM_GetChunk(SjMem *sj, int line, int nbyte, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjmem_GetChunk(sj, line, nbyte, ck);
    SJCRS_Unlock();
}

void sjmem_GetChunk(SjMem *sj, int line, int nbyte, SfdSjChunk *ck)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090241_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090242_Specified_handle_is_invalid);
        return;
    }
    if (line == SJ_LIN_FREE) {
        ck->len = 0;
        ck->data = 0;
        return;
    }
    if (line == SJ_LIN_DATA) {
        ck->len = (sj->ndata < nbyte) ? sj->ndata : nbyte;
        ck->data = sj->buf + sj->rpos;
        sj->rpos += ck->len;
        sj->ndata -= ck->len;
        return;
    }
    ck->len = 0;
    ck->data = 0;
    if (sj->errfn != 0) {
        sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
    }
}

void sjmem_PutChunk(SjMem *sj, int line, SfdSjChunk *ck);

void SJMEM_PutChunk(SjMem *sj, int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjmem_PutChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* A memory joint takes nothing back: a chunk put on either line is dropped. */
void sjmem_PutChunk(SjMem *sj, int line, SfdSjChunk *ck)
{
    if (sj == 0) {
        SJERR_CallErr(E2004090243_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090244_Specified_handle_is_invalid);
        return;
    }
    if (ck->len > 0 && ck->data != 0 && line != SJ_LIN_FREE && line != SJ_LIN_DATA) {
        ck->len = 0;
        ck->data = 0;
        if (sj->errfn != 0) {
            sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
        }
    }
}

void sjmem_UngetChunk(SjMem *sj, int line, SfdSjChunk *ck);

void SJMEM_UngetChunk(SjMem *sj, int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjmem_UngetChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* Only the chunk last read off the data line can go back; anything else is reported. */
void sjmem_UngetChunk(SjMem *sj, int line, SfdSjChunk *ck)
{
    int rpos;

    if (sj == 0) {
        SJERR_CallErr(E2004090245_NULL_pointer_is_specified);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090246_Specified_handle_is_invalid);
        return;
    }
    if (ck->len <= 0 || ck->data == 0) {
        return;
    }
    if (line == SJ_LIN_FREE) {
        if (sj->errfn != 0) {
            sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
        }
    } else if (line == SJ_LIN_DATA) {
        rpos = sj->rpos - ck->len;
        if (rpos < 0) {
            rpos = 0;
        }
        sj->rpos = rpos;
        sj->ndata = (sj->bsize < sj->ndata + ck->len) ? sj->bsize : sj->ndata + ck->len;
        if (rpos != ck->data - sj->buf) {
            if (sj->errfn != 0) {
                sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
            }
        }
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->errfn != 0) {
            sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
        }
    }
}

int sjmem_IsGetChunk(SjMem *sj, int line, int nbyte, int *rbyte);

int SJMEM_IsGetChunk(SjMem *sj, int line, int nbyte, int *rbyte)
{
    int ok;

    SJCRS_Lock();
    ok = sjmem_IsGetChunk(sj, line, nbyte, rbyte);
    SJCRS_Unlock();
    return ok;
}

int sjmem_IsGetChunk(SjMem *sj, int line, int nbyte, int *rbyte)
{
    int n;

    if (sj == 0) {
        SJERR_CallErr(E2004090247_NULL_pointer_is_specified);
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr(E2004090248_Specified_handle_is_invalid);
        return 0;
    }
    switch (line) {
    case SJ_LIN_FREE:
        n = 0;
        break;
    case SJ_LIN_DATA:
        n = sj->ndata < nbyte ? sj->ndata : nbyte;
        break;
    default:
        n = 0;
        if (sj->errfn != 0) {
            sj->errfn(sj->errobj, SJ_ERR_ILLEGAL_LINE);
        }
        break;
    }
    *rbyte = n;
    return n == nbyte;
}

char *SJMEM_GetBufPtr(SjMem *sj)
{
    return sj->buf;
}

int SJMEM_GetBufSize(SjMem *sj)
{
    return sj->bsize;
}
