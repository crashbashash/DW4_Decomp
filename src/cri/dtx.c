#include <stdio.h>
#include <string.h>
#include "dw4/support/eekernel.h"
#include "dw4/cri/svm.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/dtx.h"
#include "dw4/cri/adxmsg.h"
#include "dw4/sony/libkernl.h"
#include "dw4/sony/sif.h"

typedef struct DtxPeer {
    char pad0[60];
    int count;
} DtxPeer;

struct DtxObj {
    signed char used;       /* 0x00 */
    signed char state;      /* 0x01 */
    signed char flag;       /* 0x02 */
    char rsv;               /* 0x03 */
    int server;             /* 0x04 */
    int count;              /* 0x08 */
    char *eewk;             /* 0x0c */
    int size;               /* 0x10: wklen - 64 */
    DtxPeer *peer;          /* 0x14: uncached alias of eewk + size */
    int iopwk;              /* 0x18 */
    int wklen;              /* 0x1c */
    DtxCbf recv;            /* 0x20 */
    void *recv_obj;         /* 0x24 */
    DtxCbf send;            /* 0x28 */
    void *send_obj;         /* 0x2c */
    sceSifDmaData dma;      /* 0x30 */
    unsigned int dmaid;     /* 0x40 */
};

extern volatile int dtx_proc_init_flag;
extern int dtx_rpc_id;
extern int dtx_def_rcvcbf_cnt;
extern int dtx_def_sndcbf_cnt;
extern int dtx_exechndl_cnt;
extern int dtx_init_cnt;
extern DtxObj dtx_clnt[16];
extern sceSifClientData dtx_rpc_client;
extern sceSifServeData dtx_sd;
extern sceSifQueueData dtx_qd;
extern char dtx_svrbuf[];
extern void (*dtx_urpc_fn[64])(int object, int *data, unsigned int words);
extern int dtx_urpc_obj[64];
extern int dtx_sbuf[64];
extern int dtx_rbuf[64];

extern char Hello_from_EE_d[];
extern char eewk_is_not_alignment_64_byte[];
extern char iopwk_is_not_alignment_32_byte[];
extern char wklen_d_is_not_64_N[];
extern char illeagal_ID_d[];
extern char DTX_Create_can_t_create_DTX_of_server[];
extern char E0092101_DTX_Init_bind_errr[];


void *dtx_rpc_func(unsigned int command, void *buf, int size)
{
    int *data = buf;

    switch (command) {
    case 0:
    case 1:
        break;
    case 2:
        data[0] = (int)DTX_Create(data[0], (char *)data[1], data[2], data[3]);
        break;
    case 3:
        DTX_Destroy((DtxObj *)data[0]);
        break;
    default:
        if (command - 0x400 < 64 && dtx_urpc_fn[command - 0x400] != 0) {
            dtx_urpc_fn[command - 0x400](dtx_urpc_obj[command - 0x400], data, (unsigned int)size / 4);
        }
        break;
    }
    return data;
}

int dtx_svr_proc(void)
{
    sceSifSetRpcQueue(&dtx_qd, GetThreadId());
    sceSifRegisterRpc(&dtx_sd, dtx_rpc_id, dtx_rpc_func, dtx_svrbuf, 0, 0, &dtx_qd);
    dtx_proc_init_flag = 1;
    sceSifRpcLoop(&dtx_qd);
    return 0;
}

int dtx_create_rmt(unsigned int id, char *eewk, int iopwk, int wklen)
{
    dtx_sbuf[0] = id;
    dtx_sbuf[1] = (int)eewk;
    dtx_sbuf[2] = iopwk;
    dtx_sbuf[3] = wklen;
    sceSifCallRpc(&dtx_rpc_client, 2, 0, dtx_sbuf, 0x10, dtx_rbuf, 4, 0, 0);
    return dtx_rbuf[0];
}

void dtx_destroy_rmt(int server)
{
    dtx_sbuf[0] = server;
    sceSifCallRpc(&dtx_rpc_client, 3, 0, dtx_sbuf, 4, dtx_rbuf, 0, 0, 0);
}

void dtx_def_rcvcbf(void *obj, void *buf, int size)
{
    dtx_def_rcvcbf_cnt++;
}

void dtx_def_sndcbf(void *obj, void *buf, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        ((char *)buf)[i] = 0xAA;
    }
    sprintf(buf, Hello_from_EE_d, dtx_def_sndcbf_cnt);
    dtx_def_sndcbf_cnt++;
}

DtxObj *DTX_Open(unsigned int id)
{
    if (id >= 16) {
        return 0;
    }
    return &dtx_clnt[id];
}

void DTX_Close(DtxObj *dtx)
{
    dtx->recv = 0;
    dtx->recv_obj = 0;
    dtx->send = 0;
    dtx->send_obj = 0;
}

DtxObj *DTX_Create(unsigned int id, char *eewk, int iopwk, int wklen)
{
    DtxObj *dtx;
    int size;
    if ((int)eewk & 63) {
        ADXMSG_PrintErr(eewk_is_not_alignment_64_byte);
        return 0;
    }
    if (iopwk & 31) {
        ADXMSG_PrintErr(iopwk_is_not_alignment_32_byte);
        return 0;
    }
    if (wklen & 63) {
        ADXMSG_PrintErr(wklen_d_is_not_64_N, wklen);
        return 0;
    }
    if (id >= 16) {
        ADXMSG_PrintErr(illeagal_ID_d, id);
        return 0;
    }
    dtx = &dtx_clnt[id];
    if (dtx->used != 0) {
        return 0;
    }
    dtx->server = dtx_create_rmt(id, eewk, iopwk, wklen);
    if (dtx->server == 0) {
        ADXMSG_PrintErr(DTX_Create_can_t_create_DTX_of_server);
        return 0;
    }
    size = wklen - 64;
    dtx->size = size;
    dtx->wklen = wklen;
    dtx->iopwk = iopwk;
    dtx->peer = (DtxPeer *)((int)(eewk + size) | 0x20000000);
    dtx->count = 0;
    dtx->eewk = eewk;
    dtx->state = 0;
    memset(eewk, 0, size);
    SyncDCache(dtx->eewk, dtx->eewk + dtx->size + 63);
    InvalidDCache(dtx->eewk, dtx->eewk + dtx->size + 63);
    /* matching construct: statement-order sweep — order of the final field stores */
    dtx->recv = dtx_def_rcvcbf;
    dtx->send = dtx_def_sndcbf;
    dtx->recv_obj = 0;
    dtx->send_obj = 0;
    dtx->flag = 1;
    dtx->used = 1;
    return dtx;
}

void DTX_Destroy(DtxObj *dtx)
{
    dtx->flag = 0;
    while (dtx->state == 1) {
        DTX_ExecServer();
    }
    dtx_destroy_rmt(dtx->server);
    memset(dtx, 0, sizeof(DtxObj));
}

void DTX_SetRcvCbf(DtxObj *dtx, DtxCbf recv, void *obj)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    dtx->recv = recv;
    dtx->recv_obj = obj;
}

void DTX_SetSndCbf(DtxObj *dtx, DtxCbf send, void *obj)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    dtx->send = send;
    dtx->send_obj = obj;
}

/* matching construct: statement-order sweep of the four DMA stores */
void DTX_ExecHndl(DtxObj *dtx)
{
    dtx_exechndl_cnt++;
    if (dtx->state == 1) {
        if (dtx->count < dtx->peer->count) {
            InvalidDCache(dtx->eewk, dtx->eewk + dtx->size - 1);
            dtx->recv(dtx->recv_obj, dtx->eewk, dtx->size);
            dtx->count = dtx->peer->count;
            dtx->state = 0;
        }
    }
    if (dtx->state == 0 && dtx->flag == 1) {
        if (dtx_send_sw == 1) {
            dtx->send(dtx->send_obj, dtx->eewk, dtx->size);
            dtx->count++;
            dtx->peer->count = dtx->count;
            SyncDCache(dtx->eewk, dtx->eewk + dtx->size - 1);
            InvalidDCache(dtx->eewk, dtx->eewk + dtx->size + 63);
            dtx->dma.data = (unsigned int)dtx->eewk & 0x0fffffff;
            dtx->dma.addr = dtx->iopwk;
            dtx->dma.size = dtx->wklen;
            dtx->dma.mode = 0;
            dtx->dmaid = sceSifSetDma(&dtx->dma, 1);
            dtx->state = 1;
        }
    }
}

/* DTX_Init: the first call binds the RPC client, retrying after a delay until the IOP server answers;
   every call counts one more user. */
void DTX_Init(void)
{
    int i;

    if (dtx_init_cnt == 0) {
        while (1) {
            if (sceSifBindRpc(&dtx_rpc_client, dtx_rpc_id, 0) < 0) {
                ADXMSG_PrintErr(E0092101_DTX_Init_bind_errr);
                while (1) {
                }
            }
            if (dtx_rpc_client.serve != 0) {
                break;
            }
            i = 0x10000;
            while (i--) {
            }
        }
    }
    dtx_init_cnt++;
}

void DTX_Finish(void)
{
    DtxObj *dtx;
    int i;
    if (--dtx_init_cnt == 0) {
        dtx = dtx_clnt;
        for (i = 0; i < 16; i++, dtx++) {
            if (dtx->used == 1) {
                DTX_Destroy(dtx);
            }
        }
    }
}

int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv)
{
    int i;
    SVM_Lock();
    for (i = 0; i < nsend; i++) {
        dtx_sbuf[i] = send[i];
    }
    sceSifCallRpc(&dtx_rpc_client, fno + 1024, 0, dtx_sbuf, nsend * 4, dtx_rbuf, nrecv * 4, 0, 0);
    for (i = 0; i < nrecv; i++) {
        recv[i] = dtx_rbuf[i];
    }
    SVM_Unlock();
    return dtx_rbuf[0];
}

void DTX_ExecServer(void)
{
    DtxObj *dtx;
    int i;
    SJCRS_Lock();
    dtx = dtx_clnt;
    for (i = 0; i < 16; i++, dtx++) {
        if (dtx->used == 1) {
            DTX_ExecHndl(dtx);
        }
    }
    SJCRS_Unlock();
}
