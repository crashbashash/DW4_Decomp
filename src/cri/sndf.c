#include "dw4/cri/sndf.h"
#include <string.h>
#include "dw4/sony/sif.h"
#include "dw4/sony/sifdev.h"
#include "dw4/sony/libkernl.h"
#include "dw4/sony/libsdr.h"
#include "dw4/cri/cri_sndf.h"

/* sdrdrv's remote calls (Sony sdrcmd.h) */
#define rSdVoiceTrans 0x80D0
#define rSdVoiceTransStatus 0x80F0

/* The RPC server ids of SNDFI.IRX: 'SNDF' takes the commands, 'SFSV' the per-frame server call. */
#define SNDF_RPC_CMD_ID 0x534E4446
#define SNDF_RPC_SVR_ID 0x53465356

/* The word holding the "SNDF Ver.2.09c" string's address; only SNDF_Init reads it (build-string-reads). It
 * stays out of sndf.h: the engine's unity headers include that, and the approval count reads every `volatile`
 * a unit's text reaches. */
extern char *const volatile sndf_version;

int SNDF_Init(SndfInitParam *prm)
{
    int wait;
    int result;
    int arg[4];

    sndf_rpc_init_flag = 1;
    sndf_version;  /* the build string is referenced, never used */
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&sndf_cmd_client, SNDF_RPC_CMD_ID, 0) < 0) {
            while (1) {
            }
        }
        wait = 10000;
        while (wait--) {
        }
        if (sndf_cmd_client.serve != 0)
            break;
    }
    while (1) {
        if (sceSifBindRpc(&sndf_svr_client, SNDF_RPC_SVR_ID, 0) < 0) {
            while (1) {
            }
        }
        wait = 10000;
        while (wait--) {
        }
        if (sndf_svr_client.serve != 0)
            break;  /* braces here add a word of loop padding */
    }
    arg[0] = prm->iopWorkSize;
    arg[1] = (int)prm->iopWork;
    arg[2] = prm->initSound;
    arg[3] = prm->dmaChannel;
    sndf_dma_channel = prm->dmaChannel;
    result = sndf_CallRpc(0x1300, arg, 4, 4);
    if (result == 0) {
        sndf_initialized = 1;
    }
    return result;
}

int SNDF_Finish(void)
{
    int result;

    result = -1;
    if (sndf_initialized != 0) {
        sndf_initialized = 0;
        result = 0;
    }
    return result;
}

int SNDF_Start(void)
{
    int result = -1;
    int req[1];

    if (sndf_initialized != 0) {
        sndf_ctx = &sndf_context;
        sndf_CallRpc(0x100, 0, 0, 8);
        result = sndf_rpc_buf[0];
        sndf_ctx->iopBase = sndf_rpc_buf[1];
        memset(&sndf_status, 0, sizeof(sndf_status));
        memset(&sndf_svr_sendbuf, 0, sizeof(sndf_svr_sendbuf));
        if (result == 0) {
            req[0] = (int)&sndf_status;
            sndf_ctx->statusResult = sndf_CallRpc(0x1600, req, 1, 4);
        }
        sndf_InitContext();
        if (result == 0) {
            sndf_started = 1;
        }
    }
    return result;
}

void sndf_InitContext(void)
{
    unsigned int i;

    sndf_ctx->count = 0;
    sndf_ctx->writeIndex = 0;
    sndf_ctx->readIndex = 0;
    sndf_ctx->sending = 0;
    sndf_ctx->sizesSet = 0;
    sndf_ctx->mode = 1;
    sndf_ctx->reserved = 0;
    sndf_ctx->transferFunc = 0;
    sndf_ctx->eventFunc = 0;
    sndf_ctx->transIdle = 1;
    for (i = 0; i < 32; i++) {
        sndf_ctx->portOpen[i] = 0;
        sndf_ctx->transferState[i] = 0;
        sndf_ctx->transferMode[i] = 0;
        sndf_ctx->transferResult[i] = 0;
        sndf_ctx->transferPort[i] = 0xFF;
    }
    for (i = 0; i < 128; i++) {
        sndf_ctx->ring[i].kind = 0;
    }
}

int SNDF_Stop(void)
{
    int reply;
    int result;

    result = -1;
    if (sndf_started != 0) {
        reply = sndf_CallRpc(0x200, 0, 0, 4);
        sndf_started = 0;
        result = reply;
    }
    return result;
}

int SNDF_SetPortSizes(SndfTables *tables)
{
    SndfTables request;
    int result;
    int i;

    sndf_ctx->sizesSet = 1;
    for (i = 0; i < 32; i++) {
        request.tblSize[i] = tables->tblSize[i];
        request.pcmSize[i] = tables->pcmSize[i];
    }
    result = sndf_CallRpc(0x300, (int *)&request, 64, 4);
    if (result == 0) {
        for (i = 0; i < 32; i++) {
            sndf_ctx->tables.tblSize[i] = tables->tblSize[i];
            sndf_ctx->tables.pcmSize[i] = tables->pcmSize[i];
        }
    }
    return result;
}

int SNDF_LoadBank(unsigned int channel, SndfBank *bank)
{
    int status;

    if (sndf_ctx->transIdle == 0) {
        return -30;
    }
    SNDF_StartTransfer(channel, bank);
    do {
        sndf_ExecTransfer(channel);
        status = SNDF_GetTransferStatus(channel);
    } while (status == 1);
    if (status == 2) {
        status = 0;
    }
    return status;
}

int SNDF_StartTransfer(unsigned int channel, SndfBank *bank)
{
    sceSifDmaData dma;
    int tblAddr;
    int result;
    unsigned int id;
    unsigned int largest;
    unsigned int waveSize;

    if (bank == 0) {
        return -128;
    }
    if (sndf_ctx->transferPort[channel] != 255) {
        return -20;
    }
    SyncDCache(bank, (char *)bank + bank->size - 1);
    if (channel >= 32) {
        return -1;
    }
    if (sndf_ctx->sizesSet == 0) {
        return -4;
    }
    result = sndf_GetPortArea(channel, &tblAddr, &sndf_ctx->transfers[channel].spuAddr);
    if (result < 0) {
        return result;
    }
    if (sndf_ctx->tables.tblSize[channel] < bank->headerSize) {
        return -6;
    }
    if (sndf_ctx->tables.pcmSize[channel] < bank->waveSize) {
        return -6;
    }
    dma.data = (unsigned int)bank;
    dma.addr = tblAddr;
    dma.size = bank->headerSize;
    dma.mode = 0;
    id = sceSifSetDma(&dma, 1);
    while (sceSifDmaStat(id) >= 0) {
    }
    sndf_ctx->transfers[channel].bufferSize = 0x8000;
    largest = sceSifQueryMaxFreeMemSize();
    if (largest != -1) {
        if (sndf_ctx->transfers[channel].bufferSize < (largest >> 6) << 6) {
            sndf_ctx->transfers[channel].bufferSize = (largest >> 6) << 6;
        }
    }
    if (sndf_ctx->transfers[channel].bufferSize > 0xFFFFF) {
        sndf_ctx->transfers[channel].bufferSize = 0x100000;
    }
    sndf_ctx->transfers[channel].iopBuffer = sceSifAllocIopHeap(sndf_ctx->transfers[channel].bufferSize);
    if (sndf_ctx->transfers[channel].iopBuffer == 0) {
        return -10;
    }
    sndf_ctx->transferState[channel] = 1;
    sndf_ctx->transferMode[channel] = 0;
    sndf_ctx->transferPort[channel] = channel & 0xFF;
    waveSize = bank->waveSize;
    sndf_ctx->transfers[channel].data = (char *)bank + bank->waveOffset;
    sndf_ctx->transfers[channel].remaining = waveSize;
    if (waveSize < sndf_ctx->transfers[channel].bufferSize) {
        sndf_ctx->transfers[channel].bufferSize = waveSize;
    }
    sndf_ctx->transfers[channel].state = 1;
    return result;
}

int SNDF_LoadIopBank(unsigned int channel, int iopAddr)
{
    int request[1];
    int result;

    if (channel >= 32) {
        return -1;
    }
    request[0] = iopAddr;
    result = sndf_CallRpc(channel | 0x800, request, 1, 4);
    if (result == 0) {
        sndf_ctx->portOpen[channel] = 1;
    }
    return result;
}

int SNDF_OpenPort(unsigned int channel)
{
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = sndf_CallRpc(channel | 0xA00, 0, 0, 4);
    if (result == 0) {
        sndf_ctx->portOpen[channel] = 1;
    }
    return result;
}

int SNDF_FreePort(unsigned int channel)
{
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = sndf_CallRpc(channel | 0x700, 0, 0, 4);
    if (result == 0) {
        sndf_ctx->portOpen[channel] = 0;
    }
    return result;
}

int sndf_GetPortArea(unsigned int channel, int *tblAddr, int *spuAddr)
{
    int result = 0;
    int tblOffset = 0;
    int pcmOffset = 0;
    unsigned int i;

    if (channel >= 32) {
        return -1;
    }
    if (sndf_ctx->tables.tblSize[channel] != 0 && sndf_ctx->tables.pcmSize[channel] != 0) {
        if (sndf_ctx->portOpen[channel] == 0) {
            for (i = 0; i < channel; i++) {
                tblOffset += sndf_ctx->tables.tblSize[i];
                pcmOffset += sndf_ctx->tables.pcmSize[i];
            }
            *tblAddr = sndf_ctx->iopBase + tblOffset;
            *spuAddr = pcmOffset + 0x20000;
        } else {
            result = -3;
        }
    } else {
        result = -2;
    }
    return result;
}

int SNDF_SendSysMessage(unsigned int message)
{
    switch (message) {
    case 0xA0000100:
    case 0xA0000200:
    case 0xA0000300:
    case 0xA0000400:
        break;
    default:
        return -2;
    }
    return sndf_SendMessage(SWAP32_A(message));
}

int SNDF_GetControl(unsigned int channel, int kind)
{
    if (channel >= 32) {
        return -128;
    }
    switch (kind) {
    case 0xA0040000:
        return sndf_status.controls[channel * SNDF_CONTROL_SIZE + 10];
    case 0xA0100000:
        return sndf_status.controls[channel * SNDF_CONTROL_SIZE + 11];
    case 0xA0090000:
        if ((sndf_status.mask >> channel) & 1) {
            return 0;
        }
    case 0xA00A0000:
        return sndf_status.controls[channel * SNDF_CONTROL_SIZE + 9];
    case 0x100:
        return sndf_status.voiceCount[channel];
    }
    return -128;
}

int SNDF_GetCtrlChange(unsigned int channel, int part, int kind)
{
    if (channel >= 32) {
        return -128;
    }
    switch (kind) {
    case 0xB0270000:
        return sndf_status.params[sndf_status.programs[channel][part].index].a;
    case 0xB02A0000:
        return sndf_status.params[sndf_status.programs[channel][part].index].b - 64;
    }
    return -128;
}

int SNDF_GetPlayStatus(unsigned int channel)
{
    int result = 0;
    int i;
    SndfStatus *status;
    SndfStream *streams;

    if (channel >= 32) {
        return -1;
    }
    status = &sndf_status;
    streams = status->streams;
    for (i = 0; i < 16; i++) {
        if ((streams[i].flags & 0x80) && streams[i].channel == (unsigned char)channel) {
            result = 256;
            if (streams[i].flags & 1) {
                result = 257;
            }
            break;
        }
    }
    return result;
}

int SNDF_GetEvent(void)
{
    return sndf_CallRpc(0xE00, 0, 0, 4);
}

int SNDF_GetErrorMessage(void)
{
    return sndf_CallRpc(0xFB00, 0, 0, 4);
}

int SNDF_GetProcTime(void)
{
    return sndf_status.procTime;
}

void SNDF_GetPortSizes(int *tblSize, int *pcmSize)
{
    int i;

    sndf_CallRpc(0xFE00, 0, 0, 0x80);
    for (i = 0; i < 32; i++) {
        *tblSize++ = sndf_rpc_buf[i];
        *pcmSize++ = sndf_rpc_buf[i + 32];
    }
}

void SNDF_GetEffect(unsigned char *bank, unsigned char *preset)
{
    sndf_CallRpc(0xFC00, 0, 0, 8);
    *bank = sndf_rpc_buf[0];
    *preset = sndf_rpc_buf[1];
}

void SNDF_GetVoiceCount(int *first, int *second, int *third, int *fourth)
{
    sndf_CallRpc(0xFD00, 0, 0, 0x10);
    *first = sndf_rpc_buf[0];
    *second = sndf_rpc_buf[1];
    *third = sndf_rpc_buf[2];
    *fourth = sndf_rpc_buf[3];
}

void SNDF_GetQueueCount(int *eeQueued, int *iopQueued)
{
    *eeQueued = sndf_status.msgQueued;
    *iopQueued = sndf_status.iopMsgQueued;
}

void SNDF_ClearQueue(void)
{
    sndf_CallRpc(0xF900, 0, 0, 4);
}

void SNDF_SetCallback(void (*func)(int arg, int event))
{
    sndf_ctx->eventFunc = func;
    sndf_CallRpc(0x1700, 0, 0, 4);
}

int SNDF_GetOutputMode(void)
{
    return sndf_status.outputMode;
}

int SNDF_GetSoundStatus(int id)
{
    int result = 0;
    int i = id - 1;

    if ((unsigned int)i < 24) {
        if (sndf_ctx->slots[i].used == 1) {
            if (sndf_ctx->slots[i].playing != 0) {
                result = 1;
            }
        } else {
            result = -1;
        }
    } else {
        result = -2;
    }
    return result;
}

int sndf_CallRpc(int cmd, int *args, int n, int size)
{
    int i;

    if (sndf_rpc_busy == 0) {
        sndf_rpc_busy = 1;
        for (i = 0; i < n; i++) {
            sndf_rpc_buf[i] = *args++;
        }
        sceSifCallRpc(&sndf_cmd_client, cmd, 0, sndf_rpc_buf, n * 4, sndf_rpc_buf, size, 0, 0);
        sndf_rpc_busy = 0;
        return sndf_rpc_buf[0];
    }
    return -0x100;
}

int sndf_PushCommand(unsigned short kind, unsigned short arg, int a, int b, int c, int d)
{
    SndfContext *ctx = sndf_ctx;
    int result = 0;

    if ((signed char)ctx->count >= 0 && ctx->ring[ctx->writeIndex].kind == 0) {
        ctx->ring[ctx->writeIndex].kind = kind;
        ctx->ring[ctx->writeIndex].arg = arg;
        ctx->ring[ctx->writeIndex].a = a;
        ctx->ring[ctx->writeIndex].b = b;
        ctx->ring[ctx->writeIndex].c = c;
        ctx->ring[ctx->writeIndex].d = d;
        ctx->writeIndex = (ctx->writeIndex + 1) & 0x7F;
        sndf_ctx->count++;
    } else {
        result = -1;
    }
    return result;
}

int SNDF_SeqCommand(unsigned int cmd, unsigned char id, int value)
{
    SndfContext *ctx = sndf_ctx;
    int result = 0;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if (id != 0) {
        if (cmd == 7) {
            result = sndf_status.ports[id].state;
        } else {
            switch (cmd) {
            case 1:
                result = sndf_PushCommand(2, 0xFFFF, 1, id, value | 0x80000000, 0);
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                result = sndf_PushCommand(2, 0xFFFF, cmd, id, value, 0);
                break;
            case 8:
                result = sndf_PushCommand(2, 0xFFFF, 8, id, value / 100 + 64, ((value % 100) << 6) / 100 + 64);
                break;
            }
        }
    } else {
        result = -10;
    }
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_GetTransferStatus(unsigned int channel)
{
    int result = 0;
    int error;

    if (channel >= 32) {
        return -1;
    }
    error = sndf_ctx->transferResult[channel];
    if (error != 0) {
        sndf_ctx->transferResult[channel] = 0;
        result = (error != -256) ? error : 3;
    } else if (sndf_ctx->transferState[channel] == 1) {
        result = 1;
    } else if (sndf_ctx->transferState[channel] == 2) {
        sndf_ctx->transferState[channel] = 0;
        result = 2;
    }
    return result;
}

void sndf_SvrCallback(void *reply)
{
    SndfMessage copy;
    int *src = ((SndfMessage *)reply)->word;
    int *dst = copy.word;
    int i;

    for (i = 0; i < 4; i++) {
        *dst++ = *src++;
    }
    if (sndf_ctx->eventFunc != 0 && copy.word[2] != 0) {
        sndf_ctx->eventFunc(copy.word[1], copy.word[2]);
    }
    sndf_svr_busy = 0;
    __asm__ ("sync");
    __asm__ ("ei");
}

/* Moves the next block of a channel's pending upload to its IOP buffer and on to SPU memory,
 * then frees the buffer once the whole bank has gone. */
void sndf_ExecTransfer(unsigned int channel)
{
    sceSifDmaData dma;
    unsigned int id;

    if (sndf_ctx->transferState[channel] == 1 && sndf_ctx->transferMode[channel] == 0
        && (sndf_ctx->transIdle = sceSdRemote(1, rSdVoiceTransStatus, sndf_dma_channel, 0)) == 1) {
        if (sndf_ctx->transfers[channel].state == 1) {
            if (sndf_ctx->transfers[channel].remaining < sndf_ctx->transfers[channel].bufferSize) {
                sndf_ctx->transfers[channel].bufferSize = sndf_ctx->transfers[channel].remaining;
            }
            dma.data = (unsigned int)sndf_ctx->transfers[channel].data;
            dma.addr = (unsigned int)sndf_ctx->transfers[channel].iopBuffer;
            dma.size = sndf_ctx->transfers[channel].bufferSize;
            dma.mode = 0;
            id = sceSifSetDma(&dma, 1);
            while (sceSifDmaStat(id) >= 0) {
            }
            sceSdRemote(1, rSdVoiceTrans, sndf_dma_channel, 0, sndf_ctx->transfers[channel].iopBuffer,
                        sndf_ctx->transfers[channel].spuAddr, sndf_ctx->transfers[channel].bufferSize);
            sndf_ctx->transfers[channel].spuAddr += sndf_ctx->transfers[channel].bufferSize;
            sndf_ctx->transfers[channel].data += sndf_ctx->transfers[channel].bufferSize;
            sndf_ctx->transfers[channel].remaining -= sndf_ctx->transfers[channel].bufferSize;
            if (sndf_ctx->transfers[channel].remaining == 0) {
                sndf_ctx->transfers[channel].state = 2;
            }
        } else if (sndf_ctx->transfers[channel].state == 2) {
            sceSifFreeIopHeap(sndf_ctx->transfers[channel].iopBuffer);
            sndf_ctx->transferResult[channel] = SNDF_OpenPort(channel);
            sndf_ctx->transferState[channel] = 2;
            sndf_ctx->transferPort[channel] = 0xFF;
        }
    }
}

void SNDF_ExecServer(void)
{
    unsigned int i;
    SndfContext *ctx;

    InvalidDCache(&sndf_status, (char *)&sndf_status + sizeof(sndf_status) - 1);
    if (sndf_status.slotsRead == 0) {
        memcpy(sndf_ctx->slots, sndf_status.slots, sizeof(sndf_status.slots));
        sndf_status.slotsRead = 1;
    }
    if (sndf_ctx->count != 0 && sndf_svr_sendbuf.count == 0) {
        do {
            ctx = sndf_ctx;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].kind = ctx->ring[ctx->readIndex].kind;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].arg = ctx->ring[ctx->readIndex].arg;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].a = ctx->ring[ctx->readIndex].a;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].b = ctx->ring[ctx->readIndex].b;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].c = ctx->ring[ctx->readIndex].c;
            sndf_svr_sendbuf.ring[sndf_svr_sendbuf.count].d = ctx->ring[ctx->readIndex].d;
            if (++sndf_svr_sendbuf.count >= 128) {
                break;
            }
            ctx->ring[ctx->readIndex].kind = 0;
            ctx->ring[ctx->readIndex].c = 0;
            ctx->readIndex = (ctx->readIndex + 1) & 0x7F;
            sndf_ctx->count--;
        } while (sndf_ctx->count != 0);
    }
    if (sceSifCheckStatRpc(&sndf_svr_client.rpcd) == 0) {
        SyncDCache(&sndf_svr_sendbuf, (char *)&sndf_svr_sendbuf + sizeof(sndf_svr_sendbuf) - 1);
        sceSifCallRpc(&sndf_svr_client, 0x8000, SIF_RPCM_NOWAIT, &sndf_svr_sendbuf, sizeof(sndf_svr_sendbuf),
                      &sndf_svr_recvbuf, sizeof(sndf_svr_recvbuf), sndf_SvrCallback, &sndf_svr_recvbuf);
    }
    i = 0;
    if (sndf_ctx->transferFunc != 0) {
        for (i = 0; i < 32; i++) {
            if ((sndf_ctx->transferMode[i] & 3) == 1 && sndf_ctx->transferState[i] == 1) {
                sndf_ctx->transferResult[i] = sndf_ctx->transferFunc(i);
            }
        }
        i = 0;
    }
    do {
        sndf_ExecTransfer(i++);
    } while (i < 32);
}
