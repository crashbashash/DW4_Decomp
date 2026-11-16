/* CRI SJUNI: an SJ whose four lines are lists of chunks, the list nodes drawn from a pool in the caller's
 * work area. The upper-case entry points take the SJ critical section around the lower-case bodies. */
#include "dw4/cri/sfdsj.h"

#define SJUNI_MAX_OBJ 64
#define SJUNI_NLINE 4
#define SJ_ERR_PRM (-3)

enum SjUniMode {
    SJUNI_MODE_SEPARATE = 0,
    SJUNI_MODE_JOIN = 1   /* a chunk that continues a line's end chunk is merged into it */
};

typedef void (*SjErrFunc)(void *obj, int code);

typedef struct SjUniNode SjUniNode;
struct SjUniNode {
    SjUniNode *next;
    int reserved;
    SfdSjChunk ck;
};

typedef struct SjUniObj SjUniObj;

typedef struct SjUniVtbl {
    void *reserved[3];
    void (*destroy)(SjUniObj *sj);
    const char *(*getUuid)(SjUniObj *sj);
    void (*reset)(SjUniObj *sj);
    void (*getChunk)(SjUniObj *sj, unsigned int line, int nbyte, SfdSjChunk *ck);
    void (*ungetChunk)(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
    void (*putChunk)(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
    int (*getNumData)(SjUniObj *sj, unsigned int line);
    int (*isGetChunk)(SjUniObj *sj, unsigned int line, int nbyte, int *rbyte);
    void (*entryErrFunc)(SjUniObj *sj, SjErrFunc func, void *obj);
} SjUniVtbl;

struct SjUniObj {
    SjUniVtbl *vtbl;
    signed char used;
    signed char mode;
    const char *uuid;
    SjUniNode *pool;
    int npool;
    SjUniNode *free;
    SjUniNode *lines[SJUNI_NLINE];
    SjErrFunc err;
    void *errobj;
};

void *memset(void *dst, int value, unsigned int size);

void SJCRS_Lock(void);
void SJCRS_Unlock(void);
void SJERR_CallErr(const char *message);
void SJ_SplitChunk(SfdSjChunk *ck, int nbyte, SfdSjChunk *head, SfdSjChunk *rest);

void SJUNI_Destroy(SjUniObj *sj);
const char *SJUNI_GetUuid(SjUniObj *sj);
void SJUNI_EntryErrFunc(SjUniObj *sj, SjErrFunc func, void *obj);
void SJUNI_Reset(SjUniObj *sj);
int SJUNI_GetNumData(SjUniObj *sj, unsigned int line);
void SJUNI_GetChunk(SjUniObj *sj, unsigned int line, int nbyte, SfdSjChunk *ck);
void SJUNI_PutChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
void SJUNI_UngetChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
int SJUNI_IsGetChunk(SjUniObj *sj, unsigned int line, int nbyte, int *rbyte);

static SjUniVtbl sjuni_vtbl = {
    {0, 0, 0},
    SJUNI_Destroy, SJUNI_GetUuid, SJUNI_Reset, SJUNI_GetChunk, SJUNI_UngetChunk,
    SJUNI_PutChunk, SJUNI_GetNumData, SJUNI_IsGetChunk, SJUNI_EntryErrFunc
};
static int sjuni_init_cnt = 0;
static SjUniObj sjuni_obj[SJUNI_MAX_OBJ] = {0};
static const char sjuni_uuid[16] = "\xa3\x4f\x53\x2e\x97\xaf\xd2\x11\xa5\x27\x00\x60\x08\x94\x48\xbc";


void sjuni_Init(void);
void sjuni_Finish(void);
SjUniObj *sjuni_Create(int mode, char *work, int wksize);
void sjuni_Destroy(SjUniObj *sj);
const char *sjuni_GetUuid(SjUniObj *sj);
void sjuni_EntryErrFunc(SjUniObj *sj, SjErrFunc func, void *obj);
void sjuni_Reset(SjUniObj *sj);
int sjuni_GetNumData(SjUniObj *sj, unsigned int line);
void sjuni_GetChunk(SjUniObj *sj, unsigned int line, int nbyte, SfdSjChunk *ck);
void sjuni_PutChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
void sjuni_UngetChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck);
int sjuni_IsGetChunk(SjUniObj *sj, unsigned int line, int nbyte, int *rbyte);
int sjuni_GetNumChunk(SjUniObj *sj, int line);
int sjuni_GetNumFreeNode(SjUniObj *sj);

void SJUNI_Error(void *obj, int code)
{
    SJERR_CallErr("SJUNI Error");
}

void SJUNI_Init(void)
{
    SJCRS_Lock();
    sjuni_Init();
    SJCRS_Unlock();
}

void sjuni_Init(void)
{
    if (sjuni_init_cnt == 0) {
        memset(sjuni_obj, 0, sizeof(sjuni_obj));
    }
    sjuni_init_cnt += 1;
}

void SJUNI_Finish(void)
{
    SJCRS_Lock();
    sjuni_Finish();
    SJCRS_Unlock();
}

void sjuni_Finish(void)
{
    if (--sjuni_init_cnt == 0) {
        memset(sjuni_obj, 0, sizeof(sjuni_obj));
    }
}

SjUniObj *SJUNI_Create(int mode, char *work, int wksize)
{
    SjUniObj *sj;

    SJCRS_Lock();
    sj = sjuni_Create(mode, work, wksize);
    SJCRS_Unlock();
    return sj;
}

SjUniObj *sjuni_Create(int mode, char *work, int wksize)
{
    SjUniObj *sj;
    int i;

    for (i = 0; i < SJUNI_MAX_OBJ; i++) {
        if (sjuni_obj[i].used == 0) {
            break;
        }
    }
    if (i == SJUNI_MAX_OBJ) {
        return 0;
    }
    sj = &sjuni_obj[i];
    sj->used = 1;
    sj->vtbl = &sjuni_vtbl;
    sj->mode = mode;
    sj->uuid = sjuni_uuid;
    sj->pool = (SjUniNode *)work;
    sj->npool = wksize / (int)sizeof(SjUniNode);
    sj->err = SJUNI_Error;
    sj->errobj = sj;
    sjuni_Reset(sj);
    return sj;
}

void SJUNI_Destroy(SjUniObj *sj)
{
    SJCRS_Lock();
    sjuni_Destroy(sj);
    SJCRS_Unlock();
}

void sjuni_Destroy(SjUniObj *sj)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090261 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090262 : Specified handle is invalid.");
        return;
    }
    memset(sj, 0, sizeof(*sj));
    sj->used = 0;
}

const char *SJUNI_GetUuid(SjUniObj *sj)
{
    const char *uuid;

    SJCRS_Lock();
    uuid = sjuni_GetUuid(sj);
    SJCRS_Unlock();
    return uuid;
}

const char *sjuni_GetUuid(SjUniObj *sj)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090263 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090264 : Specified handle is invalid.");
        return 0;
    }
    return sj->uuid;
}

void SJUNI_EntryErrFunc(SjUniObj *sj, SjErrFunc func, void *obj)
{
    SJCRS_Lock();
    sjuni_EntryErrFunc(sj, func, obj);
    SJCRS_Unlock();
}

void sjuni_EntryErrFunc(SjUniObj *sj, SjErrFunc func, void *obj)
{
    if (sj == 0) {
        SJERR_CallErr("E2004090265 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090266 : Specified handle is invalid.");
        return;
    }
    sj->err = func;
    sj->errobj = obj;
}

void SJUNI_Reset(SjUniObj *sj)
{
    SJCRS_Lock();
    sjuni_Reset(sj);
    SJCRS_Unlock();
}

/* Links the node pool into one free list and empties every line. */
void sjuni_Reset(SjUniObj *sj)
{
    SjUniNode *pool;
    int i;

    if (sj == 0) {
        SJERR_CallErr("E2004090267 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090268 : Specified handle is invalid.");
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

int SJUNI_GetNumData(SjUniObj *sj, unsigned int line)
{
    int n;

    SJCRS_Lock();
    n = sjuni_GetNumData(sj, line);
    SJCRS_Unlock();
    return n;
}

int sjuni_GetNumData(SjUniObj *sj, unsigned int line)
{
    SjUniNode *node;
    int n;

    if (sj == 0) {
        SJERR_CallErr("E2004090269 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090270 : Specified handle is invalid.");
        return 0;
    }
    if (line >= SJUNI_NLINE) {
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        return 0;
    }
    n = 0;
    for (node = sj->lines[line]; node != 0; node = node->next) {
        n += node->ck.len;
    }
    return n;
}

void SJUNI_GetChunk(SjUniObj *sj, unsigned int line, int nbyte, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjuni_GetChunk(sj, line, nbyte, ck);
    SJCRS_Unlock();
}

/* Takes a line's first chunk whole; in join mode a longer one is split and its rest stays queued. */
void sjuni_GetChunk(SjUniObj *sj, unsigned int line, int nbyte, SfdSjChunk *ck)
{
    SfdSjChunk head;
    SfdSjChunk rest;
    SjUniNode *node;

    if (sj == 0) {
        SJERR_CallErr("E2004090271 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090272 : Specified handle is invalid.");
        return;
    }
    if (line >= SJUNI_NLINE) {
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
    } else {
        node = sj->lines[line];
        if (node != 0) {
            head = node->ck;
            if (nbyte >= head.len) {
                *ck = head;
                sj->lines[line] = node->next;
                node->next = sj->free;
                sj->free = node;
                return;
            }
            if (sj->mode == SJUNI_MODE_JOIN) {
                SJ_SplitChunk(&head, nbyte, &head, &rest);
                *ck = head;
                node->ck = rest;
                return;
            }
        }
    }
    ck->data = 0;
    ck->len = 0;
}

void SJUNI_PutChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjuni_PutChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* Appends a chunk to a line's end; in join mode a chunk that continues the end chunk lengthens it. */
void sjuni_PutChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck)
{
    SjUniNode **link;
    SjUniNode *node;
    SjUniNode *next;

    if (sj == 0) {
        SJERR_CallErr("E2004090273 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090274 : Specified handle is invalid.");
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
    if (sj->mode == SJUNI_MODE_JOIN && node != 0 && node->ck.data + node->ck.len == ck->data) {
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

void SJUNI_UngetChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck)
{
    SJCRS_Lock();
    sjuni_UngetChunk(sj, line, ck);
    SJCRS_Unlock();
}

/* Gives a chunk back to the head of a line; in join mode one that ends where the head chunk starts is
 * merged into it. */
void sjuni_UngetChunk(SjUniObj *sj, unsigned int line, SfdSjChunk *ck)
{
    SjUniNode *node;

    if (sj == 0) {
        SJERR_CallErr("E2004090275 : NULL pointer is specified.");
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090276 : Specified handle is invalid.");
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
    node = sj->lines[line];
    if (sj->mode == SJUNI_MODE_JOIN && node != 0 && ck->data + ck->len == node->ck.data) {
        node->ck.data = ck->data;
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
    node->next = sj->lines[line];
    sj->lines[line] = node;
}

int SJUNI_IsGetChunk(SjUniObj *sj, unsigned int line, int nbyte, int *rbyte)
{
    int ret;

    SJCRS_Lock();
    ret = sjuni_IsGetChunk(sj, line, nbyte, rbyte);
    SJCRS_Unlock();
    return ret;
}

int sjuni_IsGetChunk(SjUniObj *sj, unsigned int line, int nbyte, int *rbyte)
{
    SfdSjChunk ck;

    if (sj == 0) {
        SJERR_CallErr("E2004090277 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090278 : Specified handle is invalid.");
        return 0;
    }
    *rbyte = 0;
    if (line >= SJUNI_NLINE) {
        if (sj->err != 0) {
            sj->err(sj->errobj, SJ_ERR_PRM);
        }
        return 0;
    }
    if (sj->lines[line] == 0) {
        return 0;
    }
    ck = sj->lines[line]->ck;
    *rbyte = ck.len;
    if (sj->mode == SJUNI_MODE_JOIN) {
        if (ck.len >= nbyte) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return ck.len == nbyte;
    }
}

int SJUNI_GetNumChunk(SjUniObj *sj, int line)
{
    int n;

    SJCRS_Lock();
    n = sjuni_GetNumChunk(sj, line);
    SJCRS_Unlock();
    return n;
}

int sjuni_GetNumChunk(SjUniObj *sj, int line)
{
    SjUniNode *node;
    int n;

    if (sj == 0) {
        SJERR_CallErr("E2004090279 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090280 : Specified handle is invalid.");
        return 0;
    }
    n = 0;
    for (node = sj->lines[line]; node != 0; node = node->next) {
        n++;
    }
    return n;
}

int SJUNI_GetNumFreeNode(SjUniObj *sj)
{
    int n;

    SJCRS_Lock();
    n = sjuni_GetNumFreeNode(sj);
    SJCRS_Unlock();
    return n;
}

int sjuni_GetNumFreeNode(SjUniObj *sj)
{
    SjUniNode *node;
    int n;

    if (sj == 0) {
        SJERR_CallErr("E2004090281 : NULL pointer is specified.");
        return 0;
    }
    if (sj->used == 0) {
        SJERR_CallErr("E2004090282 : Specified handle is invalid.");
        return 0;
    }
    n = 0;
    for (node = sj->free; node != 0; node = node->next) {
        n++;
    }
    return n;
}
