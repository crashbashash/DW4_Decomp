/* sifrpc.c - libkernl's SIF RPC layer (libkernl.a sifrpc.o): the EE's clients of IOP servers, its own
 * servers the IOP calls, and the packet pools both sides' commands travel in. */
#include "dw4/sony/sif.h"
#include "dw4/eekernel.h"
#include "dw4/eekernel_gp.h"

#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))
#define RPC_PACKETS 32
/* the alarm that retries a reply the IOP could not take yet */
#define RETRY_CLOCK 0x800
/* the SIF register and the software register that say the IOP's RPC layer is up */
#define SIF_SYSREG_RPCINIT 0x80000002
#define SIF_SREG_RPCINIT 0
/* sceSifCallRpc mode: the caller has already written its buffers back from the data cache */
#define SIF_RPCM_NOWBDC 0x02

typedef struct {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

/* A packet of the client pool: the RPC header, then the request of whichever command it carries. */
typedef struct {
    sceSifRpcPktHeader rpch;
    union {
        sceSifRpcBindReq bind;
        sceSifRpcCallReq call;
        sceSifRpcOtherDataReq rdata;
        char body[SIF_CMD_PACKET_SIZE - sizeof(sceSifRpcPktHeader)];
    } req;
} sceSifRpcPacket;

typedef unsigned int (*AlarmHandler)(int id, unsigned int scheduled, unsigned int actual, void *arg);

int DIntr(void);
int EIntr(void);
int iSetTimerAlarm(unsigned long clock, AlarmHandler handler, void *arg);
unsigned int sceSifSetDma(sceSifDmaData *transfers, int count);
int sceSifGetReg(unsigned int reg);
int sceSifSetReg(unsigned int reg, int value);

static int _sceSifInitCheck = 0;
static sceSifRpcPacket _packet_buffer[RPC_PACKETS] __attribute__((aligned(64)));
static sceSifRpcRendPkt _free_buffer[RPC_PACKETS];
static sceSifRpcRendPkt _free_buffer2[RPC_PACKETS];
static sceSifRpcState _data_table;

static void _request_end(sceSifRpcRendPkt *rend, sceSifRpcState *state);
static void _request_bind(sceSifRpcBindPkt *bind, sceSifRpcState *state);
static void _request_call(sceSifRpcCallPkt *call);
static void _request_rdata(sceSifRpcOtherDataPkt *request, sceSifRpcState *state);

void sceSifInitRpc(unsigned int mode)
{
    sceSifCmdHdr *packet;

    DIntr();
    if (_sceSifInitCheck) {
        EIntr();
        return;
    }
    _sceSifInitCheck = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    _data_table.pkt_table = UNCACHED(_packet_buffer);
    _data_table.pkt_table_len = RPC_PACKETS;
    _data_table.unused1 = 0;
    _data_table.unused2 = 0;
    _data_table.rdata_table = UNCACHED(_free_buffer);
    _data_table.rdata_table_len = RPC_PACKETS;
    _data_table.client_table = UNCACHED(_free_buffer2);
    _data_table.client_table_len = RPC_PACKETS;
    _data_table.rdata_table_idx = 0;
    _data_table.pid = 1;
    sceSifAddCmdHandler(SIF_CMD_RPC_END, (sceSifCmdHandler)_request_end, &_data_table);
    sceSifAddCmdHandler(SIF_CMD_RPC_BIND, (sceSifCmdHandler)_request_bind, &_data_table);
    sceSifAddCmdHandler(SIF_CMD_RPC_CALL, (sceSifCmdHandler)_request_call, &_data_table);
    sceSifAddCmdHandler(SIF_CMD_RPC_RDATA, (sceSifCmdHandler)_request_rdata, &_data_table);
    EIntr();
    if (sceSifGetReg(SIF_SYSREG_RPCINIT)) {
        return;
    }
    packet = (sceSifCmdHdr *)&_packet_buffer[1];
    packet->opt = 1;
    sceSifSendCmd(SIF_CMD_INIT_CMD, packet, sizeof(sceSifCmdHdr), 0, 0, 0);
    while (!sceSifGetSreg(SIF_SREG_RPCINIT)) {
    }
    sceSifSetReg(SIF_SYSREG_RPCINIT, 1);
}

void sceSifExitRpc(void)
{
    sceSifExitCmd();
    _sceSifInitCheck = 0;
}

static void *_sceRpcGetPacket(sceSifRpcState *state)
{
    sceSifRpcPacket *packet;
    int i;
    unsigned int pid;

    DIntr();
    packet = state->pkt_table;
    for (i = 0; i < state->pkt_table_len; i++, packet++) {
        if (!(packet->rpch.rec_id & SIF_RPC_PKT_USED)) {
            packet->rpch.rec_id = (i << 16) | SIF_RPC_PKT_CLIENT | SIF_RPC_PKT_USED;
            state->pid++;
            if (state->pid == 1) {
                state->pid++;
                pid = 1;
            } else {
                pid = state->pid;
            }
            packet->rpch.pkt_addr = packet;
            packet->rpch.rpc_id = pid;
            EIntr();
            return packet;
        }
    }
    EIntr();
    return 0;
}

static void _sceRpcFreePacket(sceSifRpcPktHeader *packet)
{
    packet->rpc_id = 0;
    packet->rec_id &= ~SIF_RPC_PKT_USED;
}

static sceSifRpcRendPkt *_sceRpcGetFPacket(sceSifRpcState *state)
{
    sceSifRpcRendPkt *rend;

    state->rdata_table_idx %= state->rdata_table_len;
    rend = &state->rdata_table[state->rdata_table_idx];
    state->rdata_table_idx++;
    return rend;
}

static sceSifRpcRendPkt *_sceRpcGetFPacket2(sceSifRpcState *state, int index)
{
    if (index < 0 || index >= state->client_table_len) {
        return _sceRpcGetFPacket(state);
    }
    return &state->client_table[index];
}

/* The IOP's reply to a bind, call or other-data request. */
static void _request_end(sceSifRpcRendPkt *rend, sceSifRpcState *state)
{
    sceSifClientData *client;
    void *gp;

    switch (rend->cid) {
    case SIF_CMD_RPC_CALL:
        client = (sceSifClientData *)rend->client;
        if (client->func) {
            gp = SetGp(client->gp);
            client->func(client->para);
            SetGp(gp);
        }
        break;
    case SIF_CMD_RPC_BIND:
        client = (sceSifClientData *)rend->client;
        client->serve = rend->req.bind.serve;
        client->buff = rend->req.bind.buff;
        break;
    case 0x8000000b: /* matching construct: case sweep — an empty third case orders the switch compares */
        break;
    }
    client = (sceSifClientData *)rend->client;
    if (client->rpcd.tid >= 0) {
        iSignalSema(client->rpcd.tid);
    }
    _sceRpcFreePacket(client->rpcd.paddr);
    client->rpcd.paddr = 0;
}

static unsigned int _alarm_rdata(int id, unsigned int scheduled, unsigned int actual, void *arg)
{
    sceSifRpcRendPkt *rend = arg;

    return isceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_CMD_PACKET_SIZE, (void *)rend->req.rdata.src,
                          (void *)rend->req.rdata.dest, rend->req.rdata.size)
               ? 0
               : RETRY_CLOCK;
}

/* The IOP asks for data from EE memory: send it with the reply. */
static void _request_rdata(sceSifRpcOtherDataPkt *request, sceSifRpcState *state)
{
    sceSifRpcRendPkt *rend;

    if (request->rpch.rec_id & SIF_RPC_PKT_CLIENT) {
        rend = _sceRpcGetFPacket2(state, request->rpch.rec_id >> 16);
    } else {
        rend = _sceRpcGetFPacket(state);
    }
    rend->pkt_addr = (unsigned int)request->rpch.pkt_addr;
    rend->client = (unsigned int)request->req.recv;
    rend->cid = SIF_CMD_RPC_RDATA;
    rend->req.rdata.src = request->req.src;
    rend->req.rdata.dest = request->req.dest;
    rend->req.rdata.size = request->req.size;
    if (!isceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_CMD_PACKET_SIZE, (void *)request->req.src,
                        (void *)request->req.dest, request->req.size)) {
        iSetTimerAlarm(RETRY_CLOCK, _alarm_rdata, rend);
    }
}

int sceSifGetOtherData(sceSifReceiveData *rd, void *src, void *dest, int size, unsigned int mode)
{
    struct SemaParam param;
    sceSifRpcPacket *packet;

    packet = _sceRpcGetPacket(&_data_table);
    if (packet == 0) {
        return -1;
    }
    rd->rpcd.paddr = packet;
    rd->rpcd.pid = packet->rpch.rpc_id;
    packet->req.rdata.src = (unsigned int)src;
    packet->req.rdata.dest = (unsigned int)dest;
    packet->req.rdata.size = size;
    packet->rpch.pkt_addr = packet;
    packet->req.rdata.recv = rd;
    if (!(mode & SIF_RPCM_NOWAIT)) {
        param.initCount = 0;
        param.maxCount = 1;
        rd->rpcd.tid = CreateSema(&param);
        if (rd->rpcd.tid < 0) {
            _sceRpcFreePacket(&packet->rpch);
            return -3;
        }
        if (!sceSifSendCmd(SIF_CMD_RPC_RDATA, packet, SIF_CMD_PACKET_SIZE, 0, 0, 0)) {
            _sceRpcFreePacket(&packet->rpch);
            DeleteSema(rd->rpcd.tid);
            return -2;
        }
        WaitSema(rd->rpcd.tid);
        DeleteSema(rd->rpcd.tid);
        return 0;
    }
    rd->rpcd.tid = -1;
    if (!sceSifSendCmd(SIF_CMD_RPC_RDATA, packet, SIF_CMD_PACKET_SIZE, 0, 0, 0)) {
        _sceRpcFreePacket(&packet->rpch);
        return -2;
    }
    return 0;
}

static sceSifServeData *_search_svdata(unsigned int sid, sceSifRpcState *state)
{
    sceSifQueueData *queue;
    sceSifServeData *serve;

    for (queue = state->active_queue; queue != 0; queue = queue->next) {
        for (serve = queue->link; serve != 0; serve = serve->link) {
            if (serve->command == sid) {
                return serve;
            }
        }
    }
    return 0;
}

static unsigned int _alarm_bind(int id, unsigned int scheduled, unsigned int actual, void *arg)
{
    return isceSifSendCmd(SIF_CMD_RPC_END, arg, SIF_CMD_PACKET_SIZE, 0, 0, 0) ? 0 : RETRY_CLOCK;
}

/* The IOP asks to bind to an EE server: answer with the server, retrying from an alarm while the
 * send fails. */
static void _request_bind(sceSifRpcBindPkt *bind, sceSifRpcState *state)
{
    sceSifRpcRendPkt *rend;
    sceSifServeData *serve;

    rend = _sceRpcGetFPacket(state);
    rend->pkt_addr = (unsigned int)bind->rpch.pkt_addr;
    rend->client = (unsigned int)bind->req.client;
    rend->cid = SIF_CMD_RPC_BIND;
    serve = _search_svdata(bind->req.sid, state);
    if (serve == 0) {
        rend->req.bind.serve = 0;
        rend->req.bind.buff = 0;
    } else {
        rend->req.bind.serve = serve;
        rend->req.bind.buff = serve->buff;
    }
    if (!isceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_CMD_PACKET_SIZE, 0, 0, 0)) {
        iSetTimerAlarm(RETRY_CLOCK, _alarm_bind, rend);
    }
}

int sceSifBindRpc(sceSifClientData *client, unsigned int sid, unsigned int mode)
{
    struct SemaParam param;
    sceSifRpcPacket *packet;

    client->command = 0;
    client->serve = 0;
    packet = _sceRpcGetPacket(&_data_table);
    if (packet == 0) {
        return -1;
    }
    client->rpcd.paddr = packet;
    client->rpcd.pid = packet->rpch.rpc_id;
    packet->req.bind.sid = sid;
    packet->rpch.pkt_addr = packet;
    packet->req.bind.client = client;
    if (!(mode & SIF_RPCM_NOWAIT)) {
        param.initCount = 0;
        param.maxCount = 1;
        client->rpcd.tid = CreateSema(&param);
        if (client->rpcd.tid < 0) {
            _sceRpcFreePacket(&packet->rpch);
            return -3;
        }
        if (!sceSifSendCmd(SIF_CMD_RPC_BIND, packet, SIF_CMD_PACKET_SIZE, 0, 0, 0)) {
            _sceRpcFreePacket(&packet->rpch);
            DeleteSema(client->rpcd.tid);
            return -2;
        }
        WaitSema(client->rpcd.tid);
        DeleteSema(client->rpcd.tid);
        return 0;
    }
    client->rpcd.tid = -1;
    if (!sceSifSendCmd(SIF_CMD_RPC_BIND, packet, SIF_CMD_PACKET_SIZE, 0, 0, 0)) {
        _sceRpcFreePacket(&packet->rpch);
        return -2;
    }
    return 0;
}

/* The IOP calls an EE server: queue the request and wake the serving thread if it sleeps. */
static void _request_call(sceSifRpcCallPkt *call)
{
    sceSifServeData *serve = call->req.serve;
    sceSifQueueData *queue = serve->base;

    if (queue->start == 0) {
        queue->start = serve;
    } else {
        ((sceSifServeData *)queue->end)->next = serve;
    }
    queue->end = serve;
    serve->paddr = (unsigned int)call->rpch.pkt_addr;
    serve->client = call->req.client;
    serve->fno = call->req.fno;
    serve->size = call->req.ssize;
    serve->receive = call->req.receive;
    serve->rsize = call->req.rsize;
    serve->rmode = call->req.rmode;
    serve->rid = call->rpch.rec_id;
    if (queue->key >= 0 && queue->active == 0) {
        iWakeupThread(queue->key);
    }
}

int sceSifCallRpc(sceSifClientData *client, unsigned int fno, unsigned int mode, void *send, int ssize,
                  void *receive, int rsize, sceSifEndFunc end_function, void *end_param)
{
    struct SemaParam param;
    sceSifRpcPacket *packet;

    packet = _sceRpcGetPacket(&_data_table);
    if (packet == 0) {
        return -1;
    }
    client->rpcd.paddr = packet;
    client->rpcd.pid = packet->rpch.rpc_id;
    client->func = end_function;
    client->para = end_param;
    client->gp = GetGp();
    packet->req.call.fno = fno;
    packet->req.call.ssize = ssize;
    packet->req.call.receive = (unsigned int)receive;
    packet->req.call.rsize = rsize;
    packet->rpch.pkt_addr = packet;
    packet->req.call.serve = client->serve;
    packet->req.call.client = client;
    if (!(mode & SIF_RPCM_NOWBDC)) {
        if (send == receive) {
            sceSifWriteBackDCache(send, ssize < rsize ? rsize : ssize);
        } else {
            if (ssize > 0) {
                sceSifWriteBackDCache(send, ssize);
            }
            if (rsize > 0) {
                sceSifWriteBackDCache(receive, rsize);
            }
        }
    }
    if (mode & SIF_RPCM_NOWAIT) {
        if (end_function == 0) {
            packet->req.call.rmode = 0;
        } else {
            packet->req.call.rmode = 1;
        }
        client->rpcd.tid = -1;
        if (sceSifSendCmd(SIF_CMD_RPC_CALL, packet, SIF_CMD_PACKET_SIZE, send, client->buff, ssize)) {
            return 0;
        }
        _sceRpcFreePacket(&packet->rpch);
        return -2;
    }
    param.initCount = 0;
    param.maxCount = 1;
    client->rpcd.tid = CreateSema(&param);
    if (client->rpcd.tid < 0) {
        _sceRpcFreePacket(&packet->rpch);
        return -3;
    }
    packet->req.call.rmode = 1;
    if (!sceSifSendCmd(SIF_CMD_RPC_CALL, packet, SIF_CMD_PACKET_SIZE, send, client->buff, ssize)) {
        DeleteSema(client->rpcd.tid);
        _sceRpcFreePacket(&packet->rpch);
        return -2;
    }
    WaitSema(client->rpcd.tid);
    DeleteSema(client->rpcd.tid);
    return 0;
}

int sceSifCheckStatRpc(sceSifRpcData *rpcd)
{
    sceSifRpcPktHeader *packet = rpcd->paddr;

    if (packet == 0 || rpcd->pid != packet->rpc_id || !(packet->rec_id & SIF_RPC_PKT_USED)) {
        return 0;
    }
    return 1;
}

void sceSifSetRpcQueue(sceSifQueueData *queue, int key)
{
    sceSifQueueData *last;

    DIntr();
    queue->key = key;
    queue->active = 0;
    queue->link = 0;
    queue->start = 0;
    queue->end = 0;
    queue->next = 0;
    if (_data_table.active_queue == 0) {
        _data_table.active_queue = queue;
    } else {
        last = _data_table.active_queue;
        while (last->next != 0) {
            last = last->next;
        }
        last->next = queue;
    }
    EIntr();
}

void sceSifRegisterRpc(sceSifServeData *serve, unsigned int command, sceSifRpcFunc func, void *buff,
                       sceSifRpcFunc cfunc, void *cbuff, sceSifQueueData *queue)
{
    sceSifServeData *last;

    DIntr();
    serve->next = 0;
    serve->link = 0;
    serve->command = command;
    serve->func = func;
    serve->buff = buff;
    serve->cfunc = cfunc;
    serve->cbuff = cbuff;
    serve->base = queue;
    if (queue->link == 0) {
        queue->link = serve;
    } else {
        for (last = queue->link; last->link != 0; last = last->link) {
        }
        last->link = serve;
    }
    EIntr();
}

sceSifServeData *sceSifRemoveRpc(sceSifServeData *serve, sceSifQueueData *queue)
{
    sceSifServeData *s;

    DIntr();
    s = queue->link;
    if (s == serve) {
        queue->link = s->link;
    } else {
        while (s != 0) {
            if (s->link == serve) {
                s->link = serve->link;
                break;
            }
            s = s->link;
        }
    }
    EIntr();
    return s;
}

sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *queue)
{
    sceSifQueueData *q;

    DIntr();
    if ((q = _data_table.active_queue) == queue) {
        _data_table.active_queue = q->next;
    } else {
        while (q != 0) {
            if (q->next == queue) {
                q->next = queue->next;
                break;
            }
            q = q->next;
        }
    }
    EIntr();
    return q;
}

sceSifServeData *sceSifGetNextRequest(sceSifQueueData *queue)
{
    sceSifServeData *serve;

    DIntr();
    serve = queue->start;
    if (serve == 0) {
        queue->active = 0;
    } else {
        queue->active = 1;
        queue->start = serve->next;
    }
    EIntr();
    return serve;
}

/* Run a queued request and send the result back: through sceSifSendCmd when the caller asked for
 * rmode, otherwise as one DMA chain of the result and the reply packet. */
void sceSifExecRequest(sceSifServeData *serve)
{
    sceSifDmaData dmat[2];
    int size = 0;
    void *rec;
    sceSifRpcRendPkt *rend;
    int n;
    int delay;
    unsigned int id;

    rec = serve->func(serve->fno, serve->buff, serve->size);
    if (rec) {
        size = serve->rsize;
    }
    if (serve->size > 0) {
        sceSifWriteBackDCache(serve->buff, serve->size);
    }
    if (size > 0) {
        sceSifWriteBackDCache(rec, size);
    }
    DIntr();
    if (serve->rid & SIF_RPC_PKT_CLIENT) {
        rend = _sceRpcGetFPacket2(&_data_table, serve->rid >> 16);
    } else {
        rend = _sceRpcGetFPacket(&_data_table);
    }
    EIntr();
    rend->cid = SIF_CMD_RPC_CALL;
    rend->client = (unsigned int)serve->client;
    if (serve->rmode) {
        while (!sceSifSendCmd(SIF_CMD_RPC_END, rend, SIF_CMD_PACKET_SIZE, rec, (void *)serve->receive, size)) {
        }
        return;
    }
    rend->rpc_id = 0;
    rend->rec_id = 0;
    n = 0;
    if (size > 0) {
        n = 1;
        dmat[0].data = (unsigned int)rec;
        dmat[0].addr = serve->receive;
        dmat[0].size = size;
        dmat[0].mode = 0;
    }
    dmat[n].data = (unsigned int)rend;
    dmat[n].addr = serve->paddr;
    dmat[n].size = SIF_CMD_PACKET_SIZE;
    dmat[n].mode = 0;
    n++;
    do {
        id = sceSifSetDma(dmat, n);
        if (!id) {
            delay = 0x100000;
            while (delay--) {
            }
        }
    } while (!id);
}

void sceSifRpcLoop(sceSifQueueData *queue)
{
    sceSifServeData *serve;

    for (;;) {
        while ((serve = sceSifGetNextRequest(queue)) != 0) {
            sceSifExecRequest(serve);
        }
        SleepThread();
    }
}
