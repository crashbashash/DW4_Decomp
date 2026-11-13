typedef struct SifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} SifDmaData;

typedef struct SifClientData {
    char pad0[36];
    void *serve;
} SifClientData;

typedef struct DtxPeer {
    char pad0[60];
    int count;
} DtxPeer;

typedef struct DtxObj {
    signed char used;       /* 0x00 */
    signed char state;      /* 0x01 */
    signed char flag;       /* 0x02 */
    char pad3;
    int server;             /* 0x04 */
    int count;              /* 0x08 */
    char *eewk;             /* 0x0c */
    int size;               /* 0x10: wklen - 64 */
    DtxPeer *peer;          /* 0x14: uncached alias of eewk + size */
    int iopwk;              /* 0x18 */
    int wklen;              /* 0x1c */
    void (*recv)(int obj, char *buf, int size);     /* 0x20 */
    int recv_obj;           /* 0x24 */
    void (*send)(int obj, char *buf, int size);     /* 0x28 */
    int send_obj;           /* 0x2c */
    SifDmaData dma;         /* 0x30 */
    unsigned int dmaid;     /* 0x40 */
} DtxObj;

extern volatile int DAT_004a9b18;
extern int dtx_rpc_id;
extern int DAT_004a9b1c;
extern int DAT_004a9b20;
extern int DAT_004a9b24;
extern int DAT_004a9b28;
extern int dtx_init_cnt;
extern DtxObj DAT_004a9b30[16];
extern SifClientData dtx_rpc_client;
extern char DAT_004aa3d8[];
extern char DAT_004aa420[];
extern char DAT_004aa440[];
extern void (*DAT_004aa540[64])(int object, int *data, unsigned int words);
extern int DAT_004aa640[64];
extern int DAT_0056e580[64];
extern int DAT_0056e680[64];

extern char DAT_004f00b0[];
extern char DAT_004f00c8[];
extern char DAT_004f00e8[];
extern char DAT_004f0108[];
extern char DAT_004f0120[];
extern char DAT_004f0138[];
extern char E0092101_DTX_Init_bind_errr[];

void *memset(void *dst, int value, unsigned int n);
int sprintf(char *buffer, const char *format, ...);
void ADXMSG_PrintErr(const char *format, ...);
void FUN_0010b7d8(char *start, char *end);
void FUN_0010b918(char *start, char *end);
unsigned int sceSifSetDma(SifDmaData *sdd, int len);
int sceSifCallRpc(SifClientData *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize,
                 void *end, void *endarg);
int sceSifBindRpc(SifClientData *cd, unsigned int request, unsigned int mode);
int GetThreadId(void);
void sceSifSetRpcQueue(void *queue, int thread_id);
void sceSifRegisterRpc(void *server, int command, void *handler, void *buffer, void *cancel_handler,
                       void *cancel_buffer, void *queue);
void FUN_0010e990(void *queue);
void FUN_0027b2b0(void);
void FUN_0027b2c8(void);
void FUN_0027e1c0(void);
void FUN_0027e1d8(void);

DtxObj *FUN_00273338(unsigned int id, char *eewk, int iopwk, int wklen);
void FUN_002734d0(DtxObj *dtx);
void FUN_00273928(void);

int *FUN_00273078(unsigned int command, int *data, unsigned int size)
{
    switch (command) {
    case 0:
    case 1:
        break;
    case 2:
        data[0] = (int)FUN_00273338(data[0], (char *)data[1], data[2], data[3]);
        break;
    case 3:
        FUN_002734d0((DtxObj *)data[0]);
        break;
    default:
        if (command - 0x400 < 64 && DAT_004aa540[command - 0x400] != 0) {
            DAT_004aa540[command - 0x400](DAT_004aa640[command - 0x400], data, size / 4);
        }
        break;
    }
    return data;
}

int FUN_00273128(void)
{
    sceSifSetRpcQueue(DAT_004aa420, GetThreadId());
    sceSifRegisterRpc(DAT_004aa3d8, dtx_rpc_id, FUN_00273078, DAT_004aa440, 0, 0, DAT_004aa420);
    DAT_004a9b18 = 1;
    FUN_0010e990(DAT_004aa420);
    return 0;
}

int FUN_002731a8(unsigned int id, char *eewk, int iopwk, int wklen)
{
    DAT_0056e580[0] = id;
    DAT_0056e580[1] = (int)eewk;
    DAT_0056e580[2] = iopwk;
    DAT_0056e580[3] = wklen;
    sceSifCallRpc(&dtx_rpc_client, 2, 0, DAT_0056e580, 0x10, DAT_0056e680, 4, 0, 0);
    return DAT_0056e680[0];
}

void FUN_00273218(int server)
{
    DAT_0056e580[0] = server;
    sceSifCallRpc(&dtx_rpc_client, 3, 0, DAT_0056e580, 4, DAT_0056e680, 0, 0, 0);
}

void FUN_00273268(int obj, char *buf, int size)
{
    DAT_004a9b20++;
}

void FUN_00273280(int obj, char *buf, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0xAA;
    }
    sprintf(buf, DAT_004f00b0, DAT_004a9b24);
    DAT_004a9b24++;
}

DtxObj *FUN_002732f0(unsigned int id)
{
    if (id >= 16) {
        return 0;
    }
    return &DAT_004a9b30[id];
}

void FUN_00273320(DtxObj *dtx)
{
    dtx->recv = 0;
    dtx->recv_obj = 0;
    dtx->send = 0;
    dtx->send_obj = 0;
}

DtxObj *FUN_00273338(unsigned int id, char *eewk, int iopwk, int wklen)
{
    DtxObj *dtx;
    int size;
    if ((int)eewk & 63) {
        ADXMSG_PrintErr(DAT_004f00c8);
        return 0;
    }
    if (iopwk & 31) {
        ADXMSG_PrintErr(DAT_004f00e8);
        return 0;
    }
    if (wklen & 63) {
        ADXMSG_PrintErr(DAT_004f0108, wklen);
        return 0;
    }
    if (id >= 16) {
        ADXMSG_PrintErr(DAT_004f0120, id);
        return 0;
    }
    dtx = &DAT_004a9b30[id];
    if (dtx->used != 0) {
        return 0;
    }
    dtx->server = FUN_002731a8(id, eewk, iopwk, wklen);
    if (dtx->server == 0) {
        ADXMSG_PrintErr(DAT_004f0138);
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
    FUN_0010b7d8(dtx->eewk, dtx->eewk + dtx->size + 63);
    FUN_0010b918(dtx->eewk, dtx->eewk + dtx->size + 63);
    /* matching construct: statement-order sweep — order of the final field stores */
    dtx->recv = FUN_00273268;
    dtx->send = FUN_00273280;
    dtx->recv_obj = 0;
    dtx->send_obj = 0;
    dtx->flag = 1;
    dtx->used = 1;
    return dtx;
}

void FUN_002734d0(DtxObj *dtx)
{
    dtx->flag = 0;
    while (dtx->state == 1) {
        FUN_00273928();
    }
    FUN_00273218(dtx->server);
    memset(dtx, 0, sizeof(DtxObj));
}

void FUN_00273538(DtxObj *dtx, void (*recv)(int obj, char *buf, int size), int obj)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    dtx->recv = recv;
    dtx->recv_obj = obj;
}

void FUN_00273548(DtxObj *dtx, void (*send)(int obj, char *buf, int size), int obj)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    dtx->send = send;
    dtx->send_obj = obj;
}

/* matching construct: statement-order sweep of the four DMA stores */
void FUN_00273558(DtxObj *dtx)
{
    DAT_004a9b28++;
    if (dtx->state == 1) {
        if (dtx->count < dtx->peer->count) {
            FUN_0010b918(dtx->eewk, dtx->eewk + dtx->size - 1);
            dtx->recv(dtx->recv_obj, dtx->eewk, dtx->size);
            dtx->count = dtx->peer->count;
            dtx->state = 0;
        }
    }
    if (dtx->state == 0 && dtx->flag == 1) {
        if (DAT_004a9b1c == 1) {
            dtx->send(dtx->send_obj, dtx->eewk, dtx->size);
            dtx->count++;
            dtx->peer->count = dtx->count;
            FUN_0010b7d8(dtx->eewk, dtx->eewk + dtx->size - 1);
            FUN_0010b918(dtx->eewk, dtx->eewk + dtx->size + 63);
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

void FUN_002737a8(void)
{
    DtxObj *dtx;
    int i;
    if (--dtx_init_cnt == 0) {
        dtx = DAT_004a9b30;
        for (i = 0; i < 16; i++, dtx++) {
            if (dtx->used == 1) {
                FUN_002734d0(dtx);
            }
        }
    }
}

int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv)
{
    int i;
    FUN_0027e1c0();
    for (i = 0; i < nsend; i++) {
        DAT_0056e580[i] = send[i];
    }
    sceSifCallRpc(&dtx_rpc_client, fno + 1024, 0, DAT_0056e580, nsend * 4, DAT_0056e680, nrecv * 4, 0, 0);
    for (i = 0; i < nrecv; i++) {
        recv[i] = DAT_0056e680[i];
    }
    FUN_0027e1d8();
    return DAT_0056e680[0];
}

void FUN_00273928(void)
{
    DtxObj *dtx;
    int i;
    FUN_0027b2b0();
    dtx = DAT_004a9b30;
    for (i = 0; i < 16; i++, dtx++) {
        if (dtx->used == 1) {
            FUN_00273558(dtx);
        }
    }
    FUN_0027b2c8();
}
