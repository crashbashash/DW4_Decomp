/* CRI SJX: joins an EE-side SJ line to an IOP-side SJ over DTX. On every exchange the send callback
 * gathers the chunks waiting on each joined line into a list for the IOP, and the receive callback puts
 * back the chunks the IOP returns. */
#include "dw4/cri/sfdsj.h"

#define SJX_MAX_OBJ 32
#define SJX_MAX_SEND 128
#define SJX_EEWK_SIZE 2256
#define SJX_DTX_WKLEN 2176
#define SJX_DTX_ID 0
#define SJX_ALIGN 64

enum SjxRpc {
    SJX_RPC_CREATE = 0,
    SJX_RPC_DESTROY = 1,
    SJX_RPC_START = 3
};

typedef struct SjxObj {
    signed char used;
    unsigned short cnt;
    SfdSj *sj;      /* the EE-side SJ */
    int sjrmt;      /* the IOP-side SJ */
    int line;
    int iopsjx;     /* the IOP's handle for this join */
} SjxObj;

/* One chunk in an exchange list. The EE sends the IOP's handle, the IOP answers with the SjxObj. */
typedef struct SjxEntry {
    signed char busy;
    signed char line;
    unsigned short cnt;
    void *sjx;
    SfdSjChunk ck;
} SjxEntry;

typedef struct SjxList {
    int nentry;
    int reserved[3];
    SjxEntry entry[SJX_MAX_SEND];
} SjxList;

typedef void (*DtxCbf)(void *obj, SjxList *list, int size);

void *memset(void *dst, int value, unsigned int size);
void SJCRS_Lock(void);
void SJCRS_Unlock(void);
void ADXMSG_PrintErr(const char *format, ...);
int sceSifAllocIopHeap(int size);
int sceSifFreeIopHeap(int addr);
void DTX_Init(void);
void DTX_Finish(void);
void *DTX_Create(int id, unsigned int eewk, unsigned int iopwk, int wklen);
void DTX_Destroy(void *dtx);
void DTX_SetRcvCbf(void *dtx, DtxCbf func, void *obj);
void DTX_SetSndCbf(void *dtx, DtxCbf func, void *obj);
int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv);
void DTX_ExecServer(void);

extern int sjx_init_cnt;
extern unsigned int sjx_eewk;
extern int sjx_iopheap;
extern unsigned int sjx_iopwk;
extern SjxObj sjx_obj[SJX_MAX_OBJ];
extern void *sjx_dtx;
extern int sjx_wklen;
extern char sjx_eewkbuf[SJX_EEWK_SIZE];
extern char E0100301_SJX_Init_cant_allocate_IOP_Heap[];
extern char E0100302_SJX_Init_cant_create_DTX[];
extern char E0100401_cant_create_SJX_of_IOP[];

void sjx_RcvCbf(void *obj, SjxList *list, int size)
{
    SjxEntry *entry;
    SfdSj *sj;
    int n;
    int i;

    if (list == 0) {
        for (;;) {
        }
    }
    n = list->nentry;
    SJCRS_Lock();
    for (i = 0; i < n; i++) {
        entry = &list->entry[i];
        if (entry->busy == 0) {
            sj = ((SjxObj *)entry->sjx)->sj;
            sj->vtbl->putChunk(sj, entry->line, &entry->ck);
        }
    }
    SJCRS_Unlock();
}

void sjx_SndCbf(void *obj, SjxList *list, int size)
{
    SjxObj *sjx;
    SjxEntry *entry;
    SfdSjChunk ck;
    int n;
    int i;

    entry = list->entry;
    n = 0;
    SJCRS_Lock();
    sjx = sjx_obj;
    for (i = 0; i < SJX_MAX_OBJ; i++, sjx++) {
        if (sjx->used != 1) {
            continue;
        }
        for (;;) {
            if (n == SJX_MAX_SEND) {
                goto full;
            }
            sjx->sj->vtbl->getChunk(sjx->sj, sjx->line, 0x7fffffff, &ck);
            if (ck.len == 0) {
                break;
            }
            entry[n].busy = 0;
            /* matching construct: hand search — the handle is stored before the line */
            entry[n].sjx = (void *)sjx->iopsjx;
            entry[n].line = sjx->line;
            entry[n].ck = ck;
            entry[n].cnt = sjx->cnt;
            n++;
        }
    }
full:
    SJCRS_Unlock();
    list->nentry = n;
}

void SJX_ExecServer(void)
{
    DTX_ExecServer();
}

void SJX_Init(void)
{
    if (sjx_init_cnt == 0) {
        memset(sjx_eewkbuf, 0, sizeof(sjx_eewkbuf));
        DTX_Init();
        sjx_wklen = SJX_DTX_WKLEN;
        sjx_eewk = ((unsigned int)sjx_eewkbuf + SJX_ALIGN) & -SJX_ALIGN;
        if (sjx_iopheap == 0) {
            sjx_iopheap = sceSifAllocIopHeap(SJX_EEWK_SIZE);
            if (sjx_iopheap == 0) {
                ADXMSG_PrintErr(E0100301_SJX_Init_cant_allocate_IOP_Heap);
                for (;;) {
                }
            }
        }
        sjx_iopwk = (sjx_iopheap + SJX_ALIGN) & -SJX_ALIGN;
        sjx_dtx = DTX_Create(SJX_DTX_ID, sjx_eewk, sjx_iopwk, sjx_wklen);
        if (sjx_dtx == 0) {
            ADXMSG_PrintErr(E0100302_SJX_Init_cant_create_DTX);
            for (;;) {
            }
        }
        DTX_SetRcvCbf(sjx_dtx, sjx_RcvCbf, 0);
        DTX_SetSndCbf(sjx_dtx, sjx_SndCbf, 0);
        DTX_CallUrpc(SJX_RPC_START, 0, 0, 0, 0);
    }
    sjx_init_cnt++;
}

void SJX_Finish(void)
{
    if (--sjx_init_cnt == 0) {
        DTX_Destroy(sjx_dtx);
        sjx_dtx = 0;
        if (sjx_iopheap != 0) {
            sceSifFreeIopHeap(sjx_iopheap);
            sjx_iopheap = 0;
        }
        DTX_Finish();
    }
}

SjxObj *SJX_Create(SfdSj *sj, int sjrmt, int line)
{
    int request[4];
    SjxObj *sjx;
    int i;

    for (i = 0; i < SJX_MAX_OBJ; i++) {
        sjx = &sjx_obj[i];
        if (sjx->used == 0) {
            break;
        }
    }
    if (i == SJX_MAX_OBJ) {
        return 0;
    }
    memset(sjx, 0, sizeof(*sjx));
    sjx->sj = sj;
    sjx->line = line;
    sjx->sjrmt = sjrmt;
    request[0] = (int)sj;
    request[1] = sjrmt;
    request[2] = line;
    request[3] = (int)sjx;
    sjx->iopsjx = DTX_CallUrpc(SJX_RPC_CREATE, request, 4, request, 1);
    if (sjx->iopsjx == 0) {
        ADXMSG_PrintErr(E0100401_cant_create_SJX_of_IOP);
        return 0;
    }
    sjx->used = 1;
    return sjx;
}

void SJX_Destroy(SjxObj *sjx)
{
    int request[1];

    request[0] = sjx->iopsjx;
    DTX_CallUrpc(SJX_RPC_DESTROY, request, 1, 0, 0);
    sjx->used = 0;
}

void SJX_IncCnt(SjxObj *sjx)
{
    sjx->cnt = sjx->cnt + 1;
}
