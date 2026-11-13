typedef struct SndfQueueEntry {
    unsigned short kind;
    unsigned short arg;
    int a, b, c, d;
} SndfQueueEntry;

typedef struct SndfSlot {
    unsigned char used;
    unsigned char playing;
    char pad2[2];
} SndfSlot;

typedef struct SndfTables {
    int first[32];
    int second[32];
} SndfTables;

typedef struct SndfTransfer {
    char pad0[2];
    unsigned char state;
    char pad3[5];
    unsigned int bufferSize;
    char pad12[4];
    int iopBuffer;
    char pad20[4];
    int spuAddr;
    char pad28[4];
    unsigned int remaining;
    char pad36[12];
    char *data;
} SndfTransfer;

typedef struct SndfBank {
    char pad0[12];
    int size;
    unsigned int headerSize;
    char pad20[4];
    unsigned int waveSize;
    int waveOffset;
} SndfBank;

typedef struct SifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} SifDmaData;

typedef struct SndfContext {
    char pad0[128];
    unsigned char channelOn[32];
    int base;
    SndfQueueEntry ring[128];
    signed char count;
    unsigned char writeIndex;
    unsigned char readIndex;
    signed char sending;
    unsigned char busy;
    char pad2729[3];
    int mode;
    int f2736;
    int open;
    int handle;
    SndfSlot slots[24];
    int state[32];
    int f2972[32];
    int error[32];
    int f3228[32];
    SndfTransfer transfers[32];
    int f5020;
    void (*notify)(int a, int b);
    SndfTables tables;
} SndfContext;

typedef struct SndfMessage {
    int word[4];
} SndfMessage;

typedef struct SndfVoice {
    char pad0[9];
    unsigned char f9;
    unsigned char f10;
    unsigned char f11;
    char pad12[4];
} SndfVoice;

typedef struct SndfProgram {
    unsigned char index;
    char pad1[3];
} SndfProgram;

typedef struct SndfParam {
    unsigned char a;
    unsigned char b;
    char pad2[2];
} SndfParam;

typedef struct SndfStream {
    unsigned char flags;
    char pad1;
    unsigned char channel;
    char pad3[37];
} SndfStream;

typedef struct SndfPort {
    unsigned char f0;
    unsigned char state;
    unsigned char f2;
    unsigned char f3;
} SndfPort;

typedef struct SndfStatus {
    unsigned char f0;
    char pad1;
    unsigned short mask;
    int f4;
    unsigned char f8;
    unsigned char f9;
    char pad10[2];
    SndfVoice voices[32];
    SndfProgram programs[32][16];
    SndfParam params[64];
    SndfStream streams[16];
    char pad3468[3564 - 3468];
    SndfPort ports[256];
    unsigned char f4588[32];
} SndfStatus;

extern int DAT_004bb100;
extern int DAT_004bb104;
extern int DAT_004bb108;
extern int DAT_004bb110;
extern SndfContext *sndf_ctx;
extern int DAT_004bb118[];
extern int DAT_00570c00[];
extern char DAT_00570d00[];
extern int DAT_00571700;
extern int DAT_00571750[];
extern SndfStatus sndf_status;
extern SndfContext DAT_00572a00;

int sceSifCallRpc();
void memset();
int FUN_00281a00(int cmd, int *args, int n, int size);
void FUN_00280e38(void);
int FUN_00281078();
void SyncDCache(char *start, char *end);
int sceSifDmaStat(unsigned int id);
unsigned int sceSifSetDma(SifDmaData *sdd, int len);
int sceSifQueryMaxFreeMemSize(void);
int sceSifAllocIopHeap(int size);
int sceSifFreeIopHeap(int addr);
int sceSdRemote(int arg, int command, ...);
int FUN_00281420(unsigned int channel, int *start, int *size);
int sndf_PushCommand(unsigned short kind, unsigned short arg, int a, int b, int c, int d);
int FUN_00281cf8(unsigned int channel);
void FUN_00281df0(unsigned int channel);
int sndf_SendMessage(unsigned int message);

#define SWAP32_A(x) (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00) | ((x) >> 24))
#define SWAP32_B(x) (((x) << 24) | ((x) >> 24) | ((((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8)))
#define SWAP32_C(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

int FUN_00280d20(void)
{
    int var_a0;

    var_a0 = -1;
    if (DAT_004bb104 != 0) {
        DAT_004bb104 = 0;
        var_a0 = 0;
    }
    return var_a0;
}

int FUN_00280d48(void)
{
    int result = -1;
    int req[1];

    if (DAT_004bb104 != 0) {
        sndf_ctx = &DAT_00572a00;
        FUN_00281a00(0x100, 0, 0, 8);
        result = DAT_00570c00[0];
        sndf_ctx->base = DAT_00570c00[1];
        memset(&sndf_status, 0, 0x1240);
        memset(DAT_00570d00, 0, 0xA40);
        if (result == 0) {
            req[0] = (int)&sndf_status;
            sndf_ctx->handle = FUN_00281a00(0x1600, req, 1, 4);
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
        temp_v0 = FUN_00281a00(0x200, 0, 0, 4);
        DAT_004bb108 = 0;
        var_a0 = temp_v0;
    }
    return var_a0;
}

int FUN_00280f60(SndfTables *tables)
{
    SndfTables request;
    int result;
    int i;

    sndf_ctx->busy = 1;
    for (i = 0; i < 32; i++) {
        request.first[i] = tables->first[i];
        request.second[i] = tables->second[i];
    }
    result = FUN_00281a00(0x300, (int *)&request, 64, 4);
    if (result == 0) {
        for (i = 0; i < 32; i++) {
            sndf_ctx->tables.first[i] = tables->first[i];
            sndf_ctx->tables.second[i] = tables->second[i];
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
    FUN_00281078(arg, extra);
    do {
        FUN_00281df0(arg);
        status = FUN_00281cf8(arg);
    } while (status == 1);
    if (status == 2) {
        status = 0;
    }
    return status;
}

int FUN_00281300(unsigned int channel, int value)
{
    int request[1];
    int result;

    if (channel >= 32) {
        return -1;
    }
    request[0] = value;
    result = FUN_00281a00(channel | 0x800, request, 1, 4);
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
    result = FUN_00281a00(channel | 0xA00, 0, 0, 4);
    if (result == 0) {
        sndf_ctx->channelOn[channel] = 1;
    }
    return result;
}

int FUN_002813c8(unsigned int channel)
{
    int result;

    if (channel >= 32) {
        return -1;
    }
    result = FUN_00281a00(channel | 0x700, 0, 0, 4);
    if (result == 0) {
        sndf_ctx->channelOn[channel] = 0;
    }
    return result;
}

int FUN_00281420(unsigned int channel, int *start, int *size)
{
    int result = 0;
    int firstSum = 0;
    int secondSum = 0;
    unsigned int i;

    if (channel >= 32) {
        return -1;
    }
    if (sndf_ctx->tables.first[channel] != 0 && sndf_ctx->tables.second[channel] != 0) {
        if (sndf_ctx->channelOn[channel] == 0) {
            for (i = 0; i < channel; i++) {
                firstSum += sndf_ctx->tables.first[i];
                secondSum += sndf_ctx->tables.second[i];
            }
            *start = sndf_ctx->base + firstSum;
            *size = secondSum + 0x20000;
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

void FUN_00281770(void)
{
    FUN_00281a00(0xE00, 0, 0, 4);
}

void FUN_00281798(void)
{
    FUN_00281a00(0xFB00, 0, 0, 4);
}

int FUN_002817c0(void)
{
    return sndf_status.f4;
}

void FUN_002817d0(int *arg0, int *arg1)
{
    int i;

    FUN_00281a00(0xFE00, 0, 0, 0x80);
    for (i = 0; i < 32; i++) {
        *arg0++ = DAT_00570c00[i];
        *arg1++ = DAT_00570c00[i + 32];
    }
}

void FUN_00281840(unsigned char *arg0, unsigned char *arg1)
{
    FUN_00281a00(0xFC00, 0, 0, 8);
    *arg0 = DAT_00570c00[0];
    *arg1 = DAT_00570c00[1];
}

void FUN_00281898(int *arg0, int *arg1, int *arg2, int *arg3)
{
    FUN_00281a00(0xFD00, 0, 0, 0x10);
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
    FUN_00281a00(0xF900, 0, 0, 4);
}

void FUN_00281960(void (*notify)(int a, int b))
{
    sndf_ctx->notify = notify;
    FUN_00281a00(0x1700, 0, 0, 4);
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

int FUN_00281a00(int cmd, int *args, int n, int size)
{
    int i;

    if (DAT_004bb100 == 0) {
        DAT_004bb100 = 1;
        for (i = 0; i < n; i++) {
            DAT_00570c00[i] = *args++;
        }
        sceSifCallRpc(DAT_00571750, cmd, 0, DAT_00570c00, n * 4, DAT_00570c00, size, 0, 0);
        DAT_004bb100 = 0;
        return DAT_00570c00[0];
    }
    return -0x100;
}

int sndf_PushCommand(unsigned short kind, unsigned short arg, int a, int b, int c, int d)
{
    SndfContext *ctx = sndf_ctx;
    int result = 0;

    if (ctx->count >= 0 && ctx->ring[ctx->writeIndex].kind == 0) {
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

int FUN_00281cf8(unsigned int channel)
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

int sndf_SendMessage(unsigned int message)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    ctx->sending = -1;
    if (!(message & 0x80)) {
        sndf_ctx->sending = 0;
        return -2;
    }
    result = sndf_PushCommand(1, 0xFFFF, 0, 0, SWAP32_A(message), 0);
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282490(unsigned int channel, unsigned int message)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    ctx->sending = -1;
    if (!(message & 0x80)) {
        sndf_ctx->sending = 0;
        return -2;
    }
    result = sndf_PushCommand(1, channel, 0, 0, SWAP32_A(message), 0);
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282538(unsigned int channel, unsigned int kind, unsigned int data1, unsigned int data2)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    if (kind - 8 >= 6) {
        return -2;
    }
    if (data1 >= 128) {
        return -2;
    }
    if (data2 >= 128) {
        return -2;
    }
    ctx->sending = -1;
    result = sndf_PushCommand(1, channel, 0, 0, ((kind | 0xA0) << 24) | (data1 << 16) | (data2 << 8), 0);
    sndf_ctx->sending = 0;
    return result;
}

int FUN_002829f0(unsigned int base, unsigned int value)
{
    unsigned int message;
    int result;

    if (base != 0xA4000000) {
        return -2;
    }
    message = (value & 0x7F00) + 0xA4700000;
    result = sndf_SendMessage(SWAP32_C(message));
    if (result != 0) {
        return result;
    }
    message = ((value & 0x7F) << 8) + base;
    return sndf_SendMessage(SWAP32_C(message));
}

int FUN_00282ab8(unsigned int channel, unsigned int base, unsigned int value)
{
    unsigned int chan = (channel & 0xF) << 16;
    unsigned int message;
    int result;

    message = chan + base;
    switch (base) {
    case 0xA5000000:
        message = chan + (value & 0x7F00) + 0xA5700000;
        result = sndf_SendMessage(SWAP32_C(message));
        if (result != 0) {
            return result;
        }
        message = chan + ((value & 0x7F) << 8) + base;
        break;
    case 0xA5100000:
        message += (value & 0x7F) << 8;
        break;
    case 0xA5200000:
    case 0xA7000000:
    case 0xA7100000:
        message += ((value + 64) & 0x7F) << 8;
        break;
    case 0xA6000000:
        message += ((value & 0x7F) << 8) + ((value & 0x80) << 13);
        break;
    default:
        return -2;
    }
    return sndf_SendMessage(SWAP32_C(message));
}

int FUN_00282c20(unsigned int message, int arg)
{
    SndfContext *ctx = sndf_ctx;
    int id = -1;
    int result;
    int i;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((message & 0xFF) >= 0xAE) {
        for (i = 0; i < 24; i++) {
            if (sndf_ctx->slots[i].used == 0) {
                id = i + 1;
                sndf_ctx->slots[i].used = 1;
                break;
            }
        }
    } else {
        id = 0;
    }
    if (id >= 0) {
        result = sndf_PushCommand(3, 0xFFFF, 0xF00, id, message, arg);
    } else {
        result = -2;
    }
    if (result == 0) {
        result = id;
    }
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282d10(int id)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1000, id, 0, 0);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282d88(int id)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1100, id, 0, 0);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282e00(int id, unsigned short angle, unsigned short vol)
{
    SndfContext *ctx = sndf_ctx;
    int result;
    int pan;
    int p;
    int v;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    pan = (angle % 360) >> 1;
    p = pan + 45;
    if (p >= 180) {
        p = pan - 135;
    }
    if (sndf_ctx->mode == 2) {
        p = DAT_004bb118[p];
    }
    v = vol < 256 ? vol : 255;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1200, id, p, v);
    } else {
        result = -1;
    }
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282f70(int id, int value)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1800, id, value / 100 + 64, ((value % 100) << 6) / 100 + 64);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

int FUN_00282ed0(unsigned int channel, unsigned int kind, unsigned int value)
{
    unsigned int message = (channel & 0x3F) + kind;

    switch (kind) {
    case 0xA0000500:
    case 0xA0001500:
        break;
    case 0xA0120000:
        message += (value & 0x7F) << 8;
        break;
    default:
        return -1;
    }
    return FUN_00282c20(SWAP32_A(message), 0);
}
