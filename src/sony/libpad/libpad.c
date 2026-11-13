typedef struct sceSifRpcData {
    void *paddr;
    unsigned int pid;
    int tid;
    unsigned int mode;
} sceSifRpcData;

typedef struct sceSifClientData {
    sceSifRpcData rpcd;
    unsigned int command;
    void *buff;
    void *cbuff;
    void (*end_function)(void *);
    void *end_param;
    void *serve;
} sceSifClientData;

typedef struct sceSifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

/* One frame of the pad state padman.irx DMAs to the EE; the caller's 64-byte aligned area holds two,
   and the one with the higher frame count is the current one. */
typedef struct PadDmaData {
    unsigned char data[32];
    unsigned int actDirData[2];
    unsigned int actAlignData[2];
    unsigned char combData[4][4];
    unsigned char actData[4][4];
    unsigned short modeTable[4];
    int frame;
    int findPadRetries;
    int length;
    unsigned char modeConfig;
    unsigned char modeCurId;
    unsigned char model;
    unsigned char buttonDataReady;
    unsigned char nrOfModes;
    unsigned char modeCurOffs;
    unsigned char nrOfCombs;
    unsigned char nrOfActuators;
    unsigned char reserved[4];
    unsigned char state;
    unsigned char reqState;
    unsigned char currentTask;
    unsigned char reserved2[6];
    unsigned char buttonMask[4];
    unsigned char reserved3[3];
} PadDmaData;

/* A command the EE DMAs straight into padman.irx's pair of command buffers; the count tells a new one
   apart and its low bit picks the buffer. */
typedef struct PadIopCommand {
    int count;
    int command;
    int size;
    unsigned char data[20];
} PadIopCommand;

typedef struct PadPortState {
    PadDmaData *padData;
    PadIopCommand *command;
    PadIopCommand *iopCommand;
    int dmaId;
    int open;
    int reserved[2];
} PadPortState;

/* padman.irx's RPC servers */
#define PAD_SERVER 0x80000100
#define PAD_EXT_SERVER 0x80000101

/* commands of the PAD_SERVER RPC (function 1) */
#define PAD_RPC_OPEN 1
#define PAD_RPC_SET_MAIN_MODE 6
#define PAD_RPC_SET_ACT_ALIGN 8
#define PAD_RPC_SET_BUTTON_INFO 10
#define PAD_RPC_SET_VREF_PARAM 11
#define PAD_RPC_GET_PORT_MAX 12
#define PAD_RPC_GET_SLOT_MAX 13
#define PAD_RPC_CLOSE 14
#define PAD_RPC_END 15
#define PAD_RPC_INIT 16
#define PAD_RPC_GET_MOD_VERSION 18
#define PAD_RPC_SET_WARNING_LEVEL 20

/* commands sent with _send_to_iop */
#define PAD_IOP_SET_ACT_DIRECT 1

#define PAD_STATE_EXECCMD 5
#define PAD_STATE_STABLE 6
#define PAD_RSTAT_FAILED 1
#define PAD_RSTAT_BUSY 2
#define PAD_TASK_STABLE 1

#define PAD_MODECURID 1
#define PAD_MODECUREXID 2
#define PAD_MODECUROFFS 3
#define PAD_MODETABLE 4

#define LIBPAD_VERSION_MAJOR 4
#define LIBPAD_VERSION_MINOR 0

int sceSifBindRpc(sceSifClientData *client, unsigned int rpc_number, int mode);
int sceSifCallRpc(sceSifClientData *client, int rpc_number, int mode, void *send, int ssize, void *receive,
                  int rsize, void (*end_function)(void *), void *end_param);
int sceSifDmaStat(unsigned int id);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
int scePrintf(const char *format, ...);
void SyncDCache(void *start, void *end);
int DIntr(void);
int EIntr(void);
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int n);
char *strcpy(char *dst, const char *src);

int scePadGetModVersion(void);
int padPortInit(int mode);
int scePadSetReqState(int port, int slot, int state);
int scePadSetButtonInfo(int port, int slot, int info);
int scePadGetButtonMask(int port, int slot);

static sceSifClientData padClient[2];
static PadPortState padState[2][4];
static PadIopCommand padCommand[2][4] __attribute__((aligned(64)));
static int padRpcBuffer[32] __attribute__((aligned(64)));

/* The file's first strings are named rather than written here: "libpad: sceSifSetDma faild\n",
   "libpad: Module version mismatch \n" and "[libpad.a = %d.%d, padman.irx = %d.%d]\n". Among them sits
   "libpad: tPadDma Structure Invalid\n", which nothing in the linked file prints. */
extern char sifSetDmaFailedMessage[];
extern char versionMismatchMessage[];
extern char versionReportFormat[];

char libpadVersion[16] = "PsIIlibpad  2800";
int padInitialised = 0;
int padDebugPrint = 1;

int _send_to_iop(int port, int slot)
{
    sceSifDmaData dma[16];
    PadIopCommand *command;
    PadIopCommand *dst;
    unsigned int id;
    int count;

    command = padState[port][slot].command;
    if (padState[port][slot].dmaId != 0) {
        if (sceSifDmaStat(padState[port][slot].dmaId) >= 0) {
            if (padDebugPrint) scePrintf(sifSetDmaFailedMessage);
            return 0;
        }
    }
    count = command->count + 1;
    dst = padState[port][slot].iopCommand + (count & 1);
    command->count = count;
    SyncDCache(command, (char *)command + 31);
    dma[0].addr = (unsigned int)dst;
    dma[0].data = (unsigned int)command;
    dma[0].size = 32;
    dma[0].mode = 0;
    id = sceSifSetDma(dma, 1);
    if (id == 0) {
        if (padDebugPrint) scePrintf(sifSetDmaFailedMessage);
        return 0;
    }
    padState[port][slot].dmaId = id;
    return 1;
}

int scePadInit(int mode)
{
    int i;
    int version;

    padInitialised = 1;
    while (1) {
        sceSifBindRpc(&padClient[0], PAD_SERVER, 0);
        if (padClient[0].serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        sceSifBindRpc(&padClient[1], PAD_EXT_SERVER, 0);
        if (padClient[1].serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    version = scePadGetModVersion();
    if (version >> 8 != LIBPAD_VERSION_MAJOR) {
        if (padDebugPrint) {
            scePrintf(versionMismatchMessage);
            scePrintf(versionReportFormat, LIBPAD_VERSION_MAJOR, LIBPAD_VERSION_MINOR,
                      version >> 8, version & 0xff);
        }
        return 0;
    }
    return padPortInit(mode);
}

int padPortInit(int mode)
{
    int i;

    for (i = 0; i < 4; i++) {
        padState[0][i].open = 0;
        padState[0][i].reserved[1] = 0;
        padState[0][i].reserved[0] = 0;
        padState[1][i].open = 0;
        padState[1][i].reserved[1] = 0;
        padState[1][i].reserved[0] = 0;
    }
    padRpcBuffer[0] = PAD_RPC_INIT;
    padRpcBuffer[4] = 0;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    return padRpcBuffer[3];
}

int scePadEnd(void)
{
    int result;

    padRpcBuffer[0] = PAD_RPC_END;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    result = padRpcBuffer[3];
    if (result == 1) padInitialised = 0;
    return result;
}

/* `area` is the caller's 64-byte aligned pair of pad frames, which padman.irx fills from then on; its
   answer carries the address of its own pair of command buffers. */
int scePadPortOpen(int port, int slot, void *area)
{
    PadDmaData *pad;
    int i;

    if ((unsigned int)area & 0x3f) {
        if (padDebugPrint) scePrintf("libpad: buffer addr is not 64 byte align. %08x\n", area);
        return 0;
    }
    if (padState[port][slot].open == 1) {
        if (padDebugPrint) scePrintf("libpad: pad port is already open [%d][%d]\n", port, slot);
        return 0;
    }
    pad = area;
    for (i = 0; i < 2; i++, pad++) {
        pad->frame = 0;
        pad->state = PAD_STATE_EXECCMD;
        pad->reqState = PAD_RSTAT_BUSY;
        pad->buttonDataReady = 0;
        memset(pad->data, 0xff, 32);
        pad->length = 0;
    }
    padRpcBuffer[0] = PAD_RPC_OPEN;
    padRpcBuffer[1] = port;
    padRpcBuffer[2] = slot;
    padRpcBuffer[4] = (int)area;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    padState[port][slot].open = 1;
    padState[port][slot].padData = area;
    padState[port][slot].iopCommand = *(PadIopCommand **)&padRpcBuffer[5];
    padState[port][slot].command = &padCommand[port][slot];
    padState[port][slot].command->count = 0;
    padState[port][slot].dmaId = 0;
    return padRpcBuffer[3];
}

int scePadPortClose(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    padRpcBuffer[0] = PAD_RPC_CLOSE;
    padRpcBuffer[1] = port;
    padRpcBuffer[2] = slot;
    padRpcBuffer[4] = 1;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    padState[port][slot].open = 0;
    return padRpcBuffer[3];
}

PadDmaData *padGetDmaStr(int port, int slot)
{
    PadDmaData *pad;

    int current;

    pad = padState[port][slot].padData;
    SyncDCache(pad, (char *)pad + 255);
    current = pad[0].frame < pad[1].frame;
    return pad + current;
}

int scePadGetFrameCount(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    return padGetDmaStr(port, slot)->frame;
}

int scePadRead(int port, int slot, unsigned char *rdata)
{
    PadDmaData frame;
    PadDmaData *pad;
    int interrupts;

    if (padState[port][slot].open == 0) return 0;
    interrupts = DIntr();
    pad = &frame;
    *pad = *padGetDmaStr(port, slot);
    memcpy(rdata, pad->data, pad->length);
    if (interrupts == 1) EIntr();
    return pad->length;
}

int scePadGetState(int port, int slot)
{
    PadDmaData *pad;

    if (padState[port][slot].open == 0) return 99;
    pad = padGetDmaStr(port, slot);
    if (pad->state == PAD_STATE_STABLE) {
        if (pad->reqState == PAD_RSTAT_BUSY) return PAD_STATE_EXECCMD;
    }
    return pad->state;
}

char *padStateString[] = {"DISCONNECT", "", "FINDCTP1", "", "", "EXECCMD", "STABLE", "ERROR"};
char *padReqStateString[] = {"COMPLETE", "FAILED", "BUSY"};

void scePadStateIntToStr(unsigned int state, char *str)
{
    if (state < 8) {
        strcpy(str, padStateString[state]);
        return;
    }
    strcpy(str, "");
}

int scePadSetReqState(int port, int slot, int state)
{
    if (padState[port][slot].open == 0) return 0;
    padGetDmaStr(port, slot)->reqState = state;
    return 1;
}

int scePadGetReqState(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    return padGetDmaStr(port, slot)->reqState;
}

void scePadReqIntToStr(unsigned int state, char *str)
{
    if (state < 4) {
        strcpy(str, padReqStateString[state]);
        return;
    }
    strcpy(str, "");
}

/* `term` -1 asks for the count, otherwise `offs` 1..4 picks one of the combination's four bytes. */
int scePadInfoComb(int port, int slot, int term, int offs)
{
    PadDmaData *pad;

    if (padState[port][slot].open == 0) return 0;
    pad = padGetDmaStr(port, slot);
    if (pad->currentTask != PAD_TASK_STABLE) return 0;
    if (pad->modeConfig < 2) return 0;
    if (term >= pad->nrOfCombs) return 0;
    if (term == -1) return pad->nrOfCombs;
    switch (offs) {
    case 1:
        return pad->combData[term][0];
    case 2:
        return pad->combData[term][1];
    case 3:
        return pad->combData[term][2];
    case 4:
        return pad->combData[term][3];
    }
    return 0;
}

/* `actuator` -1 asks for the count, otherwise `cmd` -1..2 picks one of the actuator's four bytes. */
int scePadInfoAct(int port, int slot, int actuator, int cmd)
{
    PadDmaData *pad;

    if (padState[port][slot].open == 0) return 0;
    pad = padGetDmaStr(port, slot);
    if (pad->currentTask != PAD_TASK_STABLE) return 0;
    if (pad->modeConfig < 2) return 0;
    if (actuator == -1) return pad->nrOfActuators;
    if (actuator >= pad->nrOfActuators) return 0;
    switch (cmd) {
    case -1:
        return pad->actData[actuator][0];
    case 0:
        return pad->actData[actuator][1];
    case 1:
        return pad->actData[actuator][2];
    case 2:
        return pad->actData[actuator][3];
    }
    return 0;
}

int scePadInfoMode(int port, int slot, int term, int offs)
{
    PadDmaData *pad;

    if (padState[port][slot].open == 0) return 0;
    pad = padGetDmaStr(port, slot);
    if (pad->currentTask != PAD_TASK_STABLE) return 0;
    if (pad->reqState == PAD_RSTAT_BUSY) return 0;
    switch (term) {
    case PAD_MODECURID:
        if (pad->modeCurId == 0xf3) return 0;
        return pad->modeCurId >> 4;
    case PAD_MODECUREXID:
        if (pad->modeConfig == 1) return 0;
        return pad->modeTable[pad->modeCurOffs];
    case PAD_MODECUROFFS:
        if (pad->modeConfig == 1) return 0;
        return pad->modeCurOffs;
    case PAD_MODETABLE:
        if (pad->modeConfig == 1) return 0;
        if (offs == -1) return pad->nrOfModes;
        if (offs < pad->nrOfModes) return pad->modeTable[offs];
        return 0;
    }
    return 0;
}

int scePadSetMainMode(int port, int slot, int offs, int lock)
{
    padRpcBuffer[0] = PAD_RPC_SET_MAIN_MODE;
    padRpcBuffer[1] = port;
    padRpcBuffer[2] = slot;
    padRpcBuffer[3] = offs;
    padRpcBuffer[4] = lock;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    if (padRpcBuffer[5] == 1) scePadSetReqState(port, slot, PAD_RSTAT_BUSY);
    return padRpcBuffer[5];
}

int scePadSetActDirect(int port, int slot, const unsigned char *data)
{
    int i;
    PadIopCommand *command;

    if (padGetDmaStr(port, slot)->currentTask != PAD_TASK_STABLE) return 0;
    command = padState[port][slot].command;
    for (i = 0; i < 6; i++) command->data[i] = data[i];
    command->command = PAD_IOP_SET_ACT_DIRECT;
    command->size = 6;
    if (_send_to_iop(port, slot) != 1) return 0;
    return 1;
}

int scePadSetActAlign(int port, int slot, const unsigned char *data)
{
    int i;
    int *buffer;
    unsigned char *align;

    buffer = padRpcBuffer;
    buffer[0] = PAD_RPC_SET_ACT_ALIGN;
    buffer[1] = port;
    buffer[2] = slot;
    align = (unsigned char *)&buffer[3];
    for (i = 0; i < 6; i++) align[i] = data[i];
    if (sceSifCallRpc(&padClient[0], 1, 0, buffer, 128, buffer, 128, 0, 0) < 0) return 0;
    if (buffer[5] == 1) scePadSetReqState(port, slot, PAD_RSTAT_BUSY);
    return buffer[5];
}

int scePadGetButtonMask(int port, int slot)
{
    PadDmaData *pad;

    if (padState[port][slot].open == 0) return 0;
    pad = padGetDmaStr(port, slot);
    if (pad->currentTask != PAD_TASK_STABLE) return 0;
    if (pad->modeConfig < 2) return 0;
    if (pad->model < 2) return 0;
    return pad->buttonMask[0] + ((unsigned long)pad->buttonMask[1] << 8) +
           ((unsigned long)pad->buttonMask[2] << 16) + ((unsigned long)pad->buttonMask[3] << 24);
}

int scePadSetButtonInfo(int port, int slot, int info)
{
    padRpcBuffer[0] = PAD_RPC_SET_BUTTON_INFO;
    padRpcBuffer[1] = port;
    padRpcBuffer[2] = slot;
    padRpcBuffer[3] = info;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    if (padRpcBuffer[4] == 1) scePadSetReqState(port, slot, PAD_RSTAT_BUSY);
    return padRpcBuffer[4];
}

/* The twelve pressure-sensitive buttons report pressure when all of the mask's low 18 bits are set. */
int scePadInfoPressMode(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    return scePadGetButtonMask(port, slot) == 0x3ffff;
}

int scePadEnterPressMode(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    return scePadSetButtonInfo(port, slot, 0xfff);
}

int scePadExitPressMode(int port, int slot)
{
    if (padState[port][slot].open == 0) return 0;
    return scePadSetButtonInfo(port, slot, 0);
}

typedef struct PadVrefParam {
    unsigned char param[12];
} PadVrefParam;

int scePadSetVrefParam(int port, int slot, const PadVrefParam *param)
{
    int *buffer;

    buffer = padRpcBuffer;
    buffer[0] = PAD_RPC_SET_VREF_PARAM;
    buffer[1] = port;
    buffer[2] = slot;
    *(PadVrefParam *)&buffer[3] = *param;
    if (sceSifCallRpc(&padClient[0], 1, 0, buffer, 128, buffer, 128, 0, 0) < 0) return 0;
    if (buffer[7] == 1) scePadSetReqState(port, slot, PAD_RSTAT_BUSY);
    return buffer[7];
}

int scePadGetPortMax(void)
{
    padRpcBuffer[0] = PAD_RPC_GET_PORT_MAX;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    return padRpcBuffer[3];
}

int scePadGetSlotMax(int port)
{
    padRpcBuffer[0] = PAD_RPC_GET_SLOT_MAX;
    padRpcBuffer[1] = port;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    return padRpcBuffer[3];
}

int scePadGetModVersion(void)
{
    padRpcBuffer[0] = PAD_RPC_GET_MOD_VERSION;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    return padRpcBuffer[3];
}

int scePadSetWarningLevel(int level)
{
    padRpcBuffer[0] = PAD_RPC_SET_WARNING_LEVEL;
    padRpcBuffer[1] = level;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuffer, 128, padRpcBuffer, 128, 0, 0) < 0) return 0;
    return padRpcBuffer[2];
}
