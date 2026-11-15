/* CRI SJRBF: a ring-buffer SJ whose buffer carries an extra area past its end that mirrors its start, so a
 * chunk can run over the wrap point. The upper-case entry points take the SJ critical section around the
 * lower-case bodies. */
#include "dw4/cri/sfdsj.h"

#define SJRBF_MAX_OBJ 256
#define SJ_ERR_PRM (-3)

enum SjLine {
    SJ_LIN_FREE = 0,
    SJ_LIN_DATA = 1
};

enum SjFlow {
    SJ_FLOW_GET = 0,
    SJ_FLOW_PUT = 1
};

typedef void (*SjErrFunc)(void *obj, int code);

typedef struct SjRbfObj SjRbfObj;

typedef struct SjRbfVtbl {
    void *reserved[3];
    void (*destroy)(SjRbfObj *sj);
    const char *(*getUuid)(SjRbfObj *sj);
    void (*reset)(SjRbfObj *sj);
    void (*getChunk)(SjRbfObj *sj, int line, int nbyte, SfdSjChunk *ck);
    void (*ungetChunk)(SjRbfObj *sj, int line, SfdSjChunk *ck);
    void (*putChunk)(SjRbfObj *sj, int line, SfdSjChunk *ck);
    int (*getNumData)(SjRbfObj *sj, int line);
    int (*isGetChunk)(SjRbfObj *sj, int line, int nbyte, int *rbyte);
    void (*entryErrFunc)(SjRbfObj *sj, SjErrFunc func, void *obj);
} SjRbfVtbl;

struct SjRbfObj {
    const SjRbfVtbl *vtbl;
    int used;
    const char *uuid;
    int ndata;
    int nfree;
    int wpos;   /* the free line's position */
    int rpos;   /* the data line's position */
    char *buf;
    int bsize;
    int xsize;
    int flowcnt[2][2];  /* per line, bytes got and put */
    SjErrFunc err;
    void *errobj;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void *memset(void *dst, int value, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);

void SJCRS_Lock(void);
void SJCRS_Unlock(void);
void SJERR_CallErr(const char *message);

void SJRBF_Destroy(SjRbfObj *sj);
const char *SJRBF_GetUuid(SjRbfObj *sj);
void SJRBF_EntryErrFunc(SjRbfObj *sj, SjErrFunc func, void *obj);
void SJRBF_Reset(SjRbfObj *sj);
int SJRBF_GetNumData(SjRbfObj *sj, int line);
void SJRBF_GetChunk(SjRbfObj *sj, int line, int nbyte, SfdSjChunk *ck);
void SJRBF_PutChunk(SjRbfObj *sj, int line, SfdSjChunk *ck);
void SJRBF_UngetChunk(SjRbfObj *sj, int line, SfdSjChunk *ck);
int SJRBF_IsGetChunk(SjRbfObj *sj, int line, int nbyte, int *rbyte);

static SjRbfVtbl sjrbf_vtbl = {
    {0, 0, 0},
    SJRBF_Destroy, SJRBF_GetUuid, SJRBF_Reset, SJRBF_GetChunk, SJRBF_UngetChunk,
    SJRBF_PutChunk, SJRBF_GetNumData, SJRBF_IsGetChunk, SJRBF_EntryErrFunc
};
static int sjrbf_init_cnt = 0;
static SjRbfObj sjrbf_obj[SJRBF_MAX_OBJ] = {0};
static const char sjrbf_uuid[16] = "\x81\x9e\x9a\x3b\xbb\x0d\xd2\x11\xa6\xbf" "DEST";

void sjrbf_Init(void);
void sjrbf_Finish(void);
SjRbfObj *sjrbf_Create(char *buf, int bsize, int xsize);
void sjrbf_Destroy(SjRbfObj *sj);
void sjrbf_Reset(SjRbfObj *sj);
void sjrbf_GetChunk(SjRbfObj *sj, int line, int nbyte, SfdSjChunk *ck);
void sjrbf_PutChunk(SjRbfObj *sj, int line, SfdSjChunk *ck);
void sjrbf_UngetChunk(SjRbfObj *sj, int line, SfdSjChunk *ck);
int sjrbf_IsGetChunk(SjRbfObj *sj, int line, int nbyte, int *rbyte);

void sjrbf_Error(void *obj, int code)
{
    SJERR_CallErr("SJRBF Error");
}

void SJRBF_Init(void)
{
    SJCRS_Lock();
    sjrbf_Init();
    SJCRS_Unlock();
}

void sjrbf_Init(void)
{
    if (sjrbf_init_cnt == 0) {
        memset(sjrbf_obj, 0, sizeof(sjrbf_obj));
    }
    sjrbf_init_cnt += 1;
}

void SJRBF_Finish(void)
{
    SJCRS_Lock();
    sjrbf_Finish();
    SJCRS_Unlock();
}

void sjrbf_Finish(void)
{
    if (--sjrbf_init_cnt == 0) {
        memset(sjrbf_obj, 0, sizeof(sjrbf_obj));
    }
}

SjRbfObj *SJRBF_Create(char *buf, int bsize, int xsize)
{
    SjRbfObj *sj;

    SJCRS_Lock();
    sj = sjrbf_Create(buf, bsize, xsize);
    SJCRS_Unlock();
    return sj;
}

SjRbfObj *sjrbf_Create(char *buf, int bsize, int xsize)
{
    SjRbfObj *sj;
    int i;

    for (i = 0; i < SJRBF_MAX_OBJ; i++) {
        if (sjrbf_obj[i].used == 0) {
            break;
        }
    }
    sj = 0;
    if (i != SJRBF_MAX_OBJ) {
        sj = &sjrbf_obj[i];
        sj->used = 1;
        sj->vtbl = &sjrbf_vtbl;
        sj->buf = buf;
        sj->bsize = bsize;
        sj->xsize = xsize;
        sj->uuid = sjrbf_uuid;
        sj->err = sjrbf_Error;
        sj->errobj = sj;
        sjrbf_Reset(sj);
    }
    return sj;
}

void SJRBF_Destroy(SjRbfObj *sj)
{
    SJCRS_Lock();
    sjrbf_Destroy(sj);
    SJCRS_Unlock();
}

void sjrbf_Destroy(SjRbfObj *sj)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090201 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090202 : Specified handle is invalid.");
        return;
    }
    memset(sj, 0, sizeof(*sj));
    sj->used = 0;
}

const char *SJRBF_GetUuid(SjRbfObj *sj)
{
    return sj->uuid;
}

void SJRBF_EntryErrFunc(SjRbfObj *sj, SjErrFunc func, void *obj)
{
    sj->err = func;
    sj->errobj = obj;
}

void SJRBF_Reset(SjRbfObj *sj)
{
    SJCRS_Lock();
    sjrbf_Reset(sj);
    SJCRS_Unlock();
}

void sjrbf_Reset(SjRbfObj *sj)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090207 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090208 : Specified handle is invalid.");
        return;
    }
    sj->nfree = sj->bsize;
    sj->ndata = 0;
    sj->wpos = 0;
    sj->rpos = 0;
    sj->flowcnt[SJ_LIN_FREE][SJ_FLOW_GET] = 0;
    sj->flowcnt[SJ_LIN_FREE][SJ_FLOW_PUT] = 0;
    sj->flowcnt[SJ_LIN_DATA][SJ_FLOW_GET] = 0;
    sj->flowcnt[SJ_LIN_DATA][SJ_FLOW_PUT] = 0;
}

int SJRBF_GetNumData(SjRbfObj *sj, int line)
{
    if (line == SJ_LIN_DATA) {
        return sj->ndata;
    }
    if (line == SJ_LIN_FREE) {
        return sj->nfree;
    }
    if (sj->err != 0) {
        sj->err(sj->errobj, SJ_ERR_PRM);
    }
    return 0;
}

void SJRBF_GetChunk(SjRbfObj *sj, int line, int nbyte, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjrbf_GetChunk(sj, line, nbyte, ck);
    SJCRS_Unlock();
}

/* Takes up to nbyte from a line; a chunk may run into the extra area past the buffer's end. */
void sjrbf_GetChunk(SjRbfObj *sj, int line, int nbyte, SfdSjChunk *ck)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090211 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090212 : Specified handle is invalid.");
        return;
    }
    if (sj->bsize == 0) {
        SJERR_CallErr("E2004090219 : Illegal buffer size.");
        return;
    }
    if (line == SJ_LIN_FREE) {
        ck->len = MIN(MIN(sj->nfree, sj->bsize - sj->wpos + sj->xsize), nbyte);
        ck->data = sj->buf + sj->wpos;
        sj->wpos = (sj->wpos + ck->len) % sj->bsize;
        sj->nfree -= ck->len;
        sj->flowcnt[SJ_LIN_FREE][SJ_FLOW_GET] += ck->len;
    } else if (line == SJ_LIN_DATA) {
        ck->len = MIN(MIN(sj->ndata, sj->bsize - sj->rpos + sj->xsize), nbyte);
        ck->data = sj->buf + sj->rpos;
        sj->rpos = (sj->rpos + ck->len) % sj->bsize;
        sj->ndata -= ck->len;
        sj->flowcnt[SJ_LIN_DATA][SJ_FLOW_GET] += ck->len;
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
}

void SJRBF_PutChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjrbf_PutChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* Data put back is copied into the extra area, and data past the end to the start, so the mirror stays
 * whole. */
void sjrbf_PutChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    int ofs;
    int n;

    if (sj == 0) {
        SJERR_CallErr("E2004090213 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090214 : Specified handle is invalid.");
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
        sj->flowcnt[SJ_LIN_DATA][SJ_FLOW_PUT] += ck->len;
    } else if (line == SJ_LIN_FREE) {
        sj->nfree += ck->len;
        sj->flowcnt[SJ_LIN_FREE][SJ_FLOW_PUT] += ck->len;
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
}

void SJRBF_UngetChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjrbf_UngetChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* Gives back the tail of the last chunk got from a line; it must end at the line's position. */
void sjrbf_UngetChunk(SjRbfObj *sj, int line, SfdSjChunk *ck)
{
    int pos;

    if (sj == 0) {
        SJERR_CallErr("E2004090215 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090216 : Specified handle is invalid.");
        return;
    }
    if (sj->bsize == 0) {
        SJERR_CallErr("E2004090220 : Illegal buffer size.");
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
        sj->flowcnt[SJ_LIN_FREE][SJ_FLOW_GET] -= ck->len;
    } else if (line == SJ_LIN_DATA) {
        pos = (sj->rpos + sj->bsize - ck->len) % sj->bsize;
        if (pos == (ck->data - sj->buf) % sj->bsize) {
            sj->rpos = pos;
            sj->ndata += ck->len;
        } else if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        sj->flowcnt[SJ_LIN_DATA][SJ_FLOW_GET] -= ck->len;
    } else {
        ck->len = 0;
        ck->data = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
}

int SJRBF_IsGetChunk(SjRbfObj *sj, int line, int nbyte, int *rbyte)
{
    int ret;

    SJCRS_Lock();
    ret = sjrbf_IsGetChunk(sj, line, nbyte, rbyte);
    SJCRS_Unlock();
    return ret;
}

/* Reports in *rbyte how much a GetChunk of nbyte would give, and whether that is all of it. */
int sjrbf_IsGetChunk(SjRbfObj *sj, int line, int nbyte, int *rbyte)
{
    int n;

    if (sj == 0) {
        SJERR_CallErr("E2004090217 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090218 : Specified handle is invalid.");
        return 0;
    }
    if (line == SJ_LIN_FREE) {
        n = sj->bsize - sj->wpos + sj->xsize;
        n = MIN(sj->nfree, n);
        n = MIN(n, nbyte);
    } else if (line == SJ_LIN_DATA) {
        n = sj->bsize - sj->rpos + sj->xsize;
        n = MIN(sj->ndata, n);
        n = MIN(n, nbyte);
    } else {
        n = 0;
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    }
    *rbyte = n;
    return n == nbyte;
}

char *SJRBF_GetBufPtr(SjRbfObj *sj)
{
    return sj->buf;
}

int SJRBF_GetBufSize(SjRbfObj *sj)
{
    return sj->bsize;
}

int SJRBF_GetXtrSize(SjRbfObj *sj)
{
    return sj->xsize;
}

void SJRBF_SetFlowCnt(SjRbfObj *sj, int line, int flow, int cnt)
{
    sj->flowcnt[line][flow] = cnt;
}

int SJRBF_GetFlowCnt(SjRbfObj *sj, int line, int flow)
{
    return sj->flowcnt[line][flow];
}
