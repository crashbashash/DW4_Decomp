#include "dw4/cri/sndf.h"
#include "dw4/sony/sifdev.h"
#include "dw4/cri/cri_sndf.h"

int SNDF_Finish(void)
{
    int var_a0;

    var_a0 = -1;
    if (DAT_004bb104 != 0) {
        DAT_004bb104 = 0;
        var_a0 = 0;
    }
    return var_a0;
}

int SNDF_Start(void)
{
    int result = -1;
    int req[1];

    if (DAT_004bb104 != 0) {
        sndf_ctx = &DAT_00572a00;
        sndf_CallRpc(0x100, 0, 0, 8);
        result = DAT_00570c00[0];
        sndf_ctx->base = DAT_00570c00[1];
        memset(&sndf_status, 0, 0x1240);
        memset(&DAT_00570d00, 0, 0xA40);
        if (result == 0) {
            req[0] = (int)&sndf_status;
            sndf_ctx->handle = sndf_CallRpc(0x1600, req, 1, 4);
        }
        FUN_00280e38();
        if (result == 0) {
            DAT_004bb108 = 1;
        }
    }
    return result;
}

void FUN_00280e38(void)
{
    unsigned int i;

    sndf_ctx->count = 0;
    sndf_ctx->writeIndex = 0;
    sndf_ctx->readIndex = 0;
    sndf_ctx->sending = 0;
    sndf_ctx->busy = 0;
    sndf_ctx->mode = 1;
    sndf_ctx->f2736 = 0;
    sndf_ctx->f5020 = 0;
    sndf_ctx->notify = 0;
    sndf_ctx->open = 1;
    for (i = 0; i < 32; i++) {
        sndf_ctx->channelOn[i] = 0;
        sndf_ctx->state[i] = 0;
        sndf_ctx->f2972[i] = 0;
        sndf_ctx->error[i] = 0;
        sndf_ctx->f3228[i] = 0xFF;
    }
    for (i = 0; i < 128; i++) {
        sndf_ctx->ring[i].kind = 0;
    }
}

int FUN_00280f10(void)
{
    int temp_v0;
    int var_a0;

    var_a0 = -1;
    if (DAT_004bb108 != 0) {
        temp_v0 = sndf_CallRpc(0x200, 0, 0, 4);
        DAT_004bb108 = 0;
        var_a0 = temp_v0;
    }
    return var_a0;
}

int SNDF_SetPortSizes(SndfTables *tables)
{
    SndfTables request;
    int result;
    int i;

    sndf_ctx->busy = 1;
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

int FUN_00281018(int arg, int extra)
{
    int status;

    if (sndf_ctx->open == 0) {
        return -30;
    }
    SNDF_StartTransfer(arg, extra);
    do {
        FUN_00281df0(arg);
        status = SNDF_GetTransferStatus(arg);
    } while (status == 1);
    if (status == 2) {
        status = 0;
    }
    return status;
}

int SNDF_StartTransfer(unsigned int channel, SndfBank *bank)
{
    SifDmaData dma;
    int start;
    int result;
    unsigned int id;
    unsigned int largest;
    unsigned int waveSize;

    if (bank == 0) {
        return -128;
    }
    if (sndf_ctx->f3228[channel] != 255) {
        return -20;
    }
    SyncDCache((char *)bank, (char *)bank + bank->size - 1);
    if (channel >= 32) {
        return -1;
    }
    if (sndf_ctx->busy == 0) {
        return -4;
    }
    result = FUN_00281420(channel, &start, &sndf_ctx->transfers[channel].spuAddr);
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
    dma.addr = start;
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
    sndf_ctx->state[channel] = 1;
    sndf_ctx->f2972[channel] = 0;
    sndf_ctx->f3228[channel] = channel & 0xFF;
    waveSize = bank->waveSize;
    sndf_ctx->transfers[channel].data = (char *)bank + bank->waveOffset;
    sndf_ctx->transfers[channel].remaining = waveSize;
    if (waveSize < sndf_ctx->transfers[channel].bufferSize) {
        sndf_ctx->transfers[channel].bufferSize = waveSize;
    }
    sndf_ctx->transfers[channel].state = 1;
    return result;
}

int FUN_00281300(unsigned int channel, int value)
{
    int request[1];
    int result;

    if (channel >= 32) {
        return -1;
    }
    request[0] = value;
    result = sndf_CallRpc(channel | 0x800, request, 1, 4);
    if (result == 0) {
        sndf_ctx->channelOn[channel] = 1;
    }
    return result;
}

int FUN_00281368(unsigned int channel)
{
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = sndf_CallRpc(channel | 0xA00, 0, 0, 4);
    if (result == 0) {
        sndf_ctx->channelOn[channel] = 1;
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
        sndf_ctx->channelOn[channel] = 0;
    }
    return result;
}

int FUN_00281420(unsigned int channel, int *start, int *size)
{
    int result = 0;
    int tblOffset = 0;
    int pcmOffset = 0;
    unsigned int i;

    if (channel >= 32) {
        return -1;
    }
    if (sndf_ctx->tables.tblSize[channel] != 0 && sndf_ctx->tables.pcmSize[channel] != 0) {
        if (sndf_ctx->channelOn[channel] == 0) {
            for (i = 0; i < channel; i++) {
                tblOffset += sndf_ctx->tables.tblSize[i];
                pcmOffset += sndf_ctx->tables.pcmSize[i];
            }
            *start = sndf_ctx->base + tblOffset;
            *size = pcmOffset + 0x20000;
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

int FUN_00281660(unsigned int channel, int index, int kind)
{
    if (channel >= 32) {
        return -128;
    }
    switch (kind) {
    case 0xB0270000:
        return sndf_status.params[sndf_status.programs[channel][index].index].a;
    case 0xB02A0000:
        return sndf_status.params[sndf_status.programs[channel][index].index].b - 64;
    }
    return -128;
}

int FUN_002816f8(unsigned int channel)
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

void FUN_00281770(void)
{
    sndf_CallRpc(0xE00, 0, 0, 4);
}

void FUN_00281798(void)
{
    sndf_CallRpc(0xFB00, 0, 0, 4);
}

int FUN_002817c0(void)
{
    return sndf_status.f4;
}

void FUN_002817d0(int *arg0, int *arg1)
{
    int i;

    sndf_CallRpc(0xFE00, 0, 0, 0x80);
    for (i = 0; i < 32; i++) {
        *arg0++ = DAT_00570c00[i];
        *arg1++ = DAT_00570c00[i + 32];
    }
}

void FUN_00281840(unsigned char *arg0, unsigned char *arg1)
{
    sndf_CallRpc(0xFC00, 0, 0, 8);
    *arg0 = DAT_00570c00[0];
    *arg1 = DAT_00570c00[1];
}

void FUN_00281898(int *arg0, int *arg1, int *arg2, int *arg3)
{
    sndf_CallRpc(0xFD00, 0, 0, 0x10);
    *arg0 = DAT_00570c00[0];
    *arg1 = DAT_00570c00[1];
    *arg2 = DAT_00570c00[2];
    *arg3 = DAT_00570c00[3];
}

void FUN_00281918(int *arg0, int *arg1)
{
    *arg0 = sndf_status.f0;
    *arg1 = sndf_status.f9;
}

void FUN_00281938(void)
{
    sndf_CallRpc(0xF900, 0, 0, 4);
}

void FUN_00281960(void (*notify)(int a, int b))
{
    sndf_ctx->notify = notify;
    sndf_CallRpc(0x1700, 0, 0, 4);
}

int FUN_00281990(void)
{
    return sndf_status.f8;
}

int FUN_002819a0(int id)
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

    if (DAT_004bb100 == 0) {
        DAT_004bb100 = 1;
        for (i = 0; i < n; i++) {
            DAT_00570c00[i] = *args++;
        }
        sceSifCallRpc(&DAT_00571750, cmd, 0, DAT_00570c00, n * 4, DAT_00570c00, size, 0, 0);
        DAT_004bb100 = 0;
        return DAT_00570c00[0];
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
    error = sndf_ctx->error[channel];
    if (error != 0) {
        sndf_ctx->error[channel] = 0;
        result = (error != -256) ? error : 3;
    } else if (sndf_ctx->state[channel] == 1) {
        result = 1;
    } else if (sndf_ctx->state[channel] == 2) {
        sndf_ctx->state[channel] = 0;
        result = 2;
    }
    return result;
}

void FUN_00281d80(SndfMessage *message)
{
    SndfMessage copy;
    int *src = message->word;
    int *dst = copy.word;
    int i;

    for (i = 0; i < 4; i++) {
        *dst++ = *src++;
    }
    if (sndf_ctx->notify != 0 && copy.word[2] != 0) {
        sndf_ctx->notify(copy.word[1], copy.word[2]);
    }
    DAT_00571700 = 0;
    __asm__ ("sync");
    __asm__ ("ei");
}

/* Moves the next block of a channel's pending upload to its IOP buffer and on to SPU memory,
 * then frees the buffer once the whole bank has gone. */
void FUN_00281df0(unsigned int channel)
{
    SifDmaData dma;
    unsigned int id;

    if (sndf_ctx->state[channel] == 1 && sndf_ctx->f2972[channel] == 0
        && (sndf_ctx->open = sceSdRemote(1, 0x80F0, DAT_004bb110, 0)) == 1) {
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
            sceSdRemote(1, 0x80D0, DAT_004bb110, 0, sndf_ctx->transfers[channel].iopBuffer,
                        sndf_ctx->transfers[channel].spuAddr, sndf_ctx->transfers[channel].bufferSize);
            sndf_ctx->transfers[channel].spuAddr += sndf_ctx->transfers[channel].bufferSize;
            sndf_ctx->transfers[channel].data += sndf_ctx->transfers[channel].bufferSize;
            sndf_ctx->transfers[channel].remaining -= sndf_ctx->transfers[channel].bufferSize;
            if (sndf_ctx->transfers[channel].remaining == 0) {
                sndf_ctx->transfers[channel].state = 2;
            }
        } else if (sndf_ctx->transfers[channel].state == 2) {
            sceSifFreeIopHeap(sndf_ctx->transfers[channel].iopBuffer);
            sndf_ctx->error[channel] = FUN_00281368(channel);
            sndf_ctx->state[channel] = 2;
            sndf_ctx->f3228[channel] = 0xFF;
        }
    }
}

void SNDF_ExecServer(void)
{
    unsigned int i;
    SndfContext *ctx;

    InvalidDCache((char *)&sndf_status, (char *)&sndf_status + 4671);
    if (sndf_status.f1 == 0) {
        memcpy(sndf_ctx->slots, sndf_status.slots, sizeof(sndf_status.slots));
        sndf_status.f1 = 1;
    }
    if (sndf_ctx->count != 0 && DAT_00570d00.count == 0) {
        do {
            ctx = sndf_ctx;
            DAT_00570d00.ring[DAT_00570d00.count].kind = ctx->ring[ctx->readIndex].kind;
            DAT_00570d00.ring[DAT_00570d00.count].arg = ctx->ring[ctx->readIndex].arg;
            DAT_00570d00.ring[DAT_00570d00.count].a = ctx->ring[ctx->readIndex].a;
            DAT_00570d00.ring[DAT_00570d00.count].b = ctx->ring[ctx->readIndex].b;
            DAT_00570d00.ring[DAT_00570d00.count].c = ctx->ring[ctx->readIndex].c;
            DAT_00570d00.ring[DAT_00570d00.count].d = ctx->ring[ctx->readIndex].d;
            if (++DAT_00570d00.count >= 128) {
                break;
            }
            ctx->ring[ctx->readIndex].kind = 0;
            ctx->ring[ctx->readIndex].c = 0;
            ctx->readIndex = (ctx->readIndex + 1) & 0x7F;
            sndf_ctx->count--;
        } while (sndf_ctx->count != 0);
    }
    if (sceSifCheckStatRpc(&DAT_00571778) == 0) {
        SyncDCache((char *)&DAT_00570d00, (char *)&DAT_00570d00 + 2623);
        sceSifCallRpc(&DAT_00571778, 0x8000, 1, &DAT_00570d00, 2624, &DAT_00571740, 16, FUN_00281d80,
                      &DAT_00571740);
    }
    i = 0;
    if (sndf_ctx->f5020 != 0) {
        for (i = 0; i < 32; i++) {
            if ((sndf_ctx->f2972[i] & 3) == 1 && sndf_ctx->state[i] == 1) {
                sndf_ctx->error[i] = sndf_ctx->f5020(i);
            }
        }
        i = 0;
    }
    do {
        FUN_00281df0(i++);
    } while (i < 32);
}

