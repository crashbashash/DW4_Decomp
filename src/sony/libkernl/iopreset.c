/* iopreset.c - resetting and rebooting the IOP over SIF. */

/* SIF registers */
#define SIF_REG_MAINADDR 0x80000000
#define SIF_REG_MSFLAG 0x80000002
#define SIF_REG_SMFLAG 4

/* SIF_REG_SMFLAG bits */
#define SIF_STAT_SIFINIT 0x10000
#define SIF_STAT_CMDINIT 0x20000
#define SIF_STAT_BOOTEND 0x40000

#define SIF_CMD_RESET 0x80000003
#define SIF_DMA_INT_O 0x04
#define SIF_DMA_ERT 0x40

#define RESET_ARG_MAX 80

typedef struct {
    unsigned int psize : 8;
    unsigned int dsize : 24;
    void *dest;
    int cid;
    unsigned int opt;
    int size;
    int mode;
    char arg[RESET_ARG_MAX];
} __attribute__((aligned(8))) SifResetPacket;

typedef struct {
    void *data;
    void *addr;
    int size;
    int mode;
} sceSifDmaData;

void sceSifExecNotifyHandler(int builtin, void *arg);
void sceSifStopDma(void);
unsigned int sceSifGetReg(unsigned int reg);
void sceSifSetReg(unsigned int reg, unsigned int value);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
void sceSifWriteBackDCache(void *addr, int size);
void sceResetttyinit(void);
int scePrintf(const char *fmt, ...);
void sceSifInitRpc(unsigned int mode);
void sceSifExitRpc(void);

extern SifResetPacket resetPacket;

int sceSifResetIop(const char *arg, int mode)
{
    sceSifDmaData dma;
    void *dest;
    int i;
    sceSifExecNotifyHandler(0, 0);
    sceSifExecNotifyHandler(1, 0);
    sceSifStopDma();
    dest = (void *)sceSifGetReg(SIF_REG_MAINADDR);
    resetPacket.mode = mode;
    for (i = 0; arg[i] != 0; i++) {
        resetPacket.arg[i] = arg[i];
    }
    resetPacket.dest = 0;
    resetPacket.dsize = 0;
    resetPacket.psize = sizeof(SifResetPacket);
    resetPacket.size = i;
    resetPacket.cid = SIF_CMD_RESET;
    dma.data = &resetPacket;
    dma.addr = dest;
    dma.size = sizeof(SifResetPacket);
    dma.mode = SIF_DMA_ERT | SIF_DMA_INT_O;
    sceSifWriteBackDCache(&resetPacket, sizeof(SifResetPacket));
    sceSifSetReg(SIF_REG_SMFLAG, SIF_STAT_BOOTEND);
    if (sceSifSetDma(&dma, 1) != 0) {
        sceSifSetReg(SIF_REG_SMFLAG, SIF_STAT_SIFINIT);
        sceSifSetReg(SIF_REG_SMFLAG, SIF_STAT_CMDINIT);
        sceSifSetReg(SIF_REG_MSFLAG, 0);
        sceSifSetReg(SIF_REG_MAINADDR, 0);
        return 1;
    }
    return 0;
}

int sceSifIsAliveIop(void)
{
    if (sceSifGetReg(SIF_REG_SMFLAG) & SIF_STAT_SIFINIT) {
        return 1;
    }
    return 0;
}

int sceSifSyncIop(void)
{
    if (!(sceSifGetReg(SIF_REG_SMFLAG) & SIF_STAT_BOOTEND)) {
        return 0;
    }
    sceResetttyinit();
    sceSifExecNotifyHandler(1, (void *)1);
    sceSifExecNotifyHandler(0, (void *)1);
    return 1;
}

int sceSifRebootIop(const char *arg)
{
    char param[RESET_ARG_MAX];
    const char *udnl = "rom0:UDNL ";
    const char *p;
    char *d;
    for (p = arg; *p; p++);
    /* "rom0:UDNL ", arg and the terminator must fit the reset argument */
    if ((unsigned int)(p + 11 - arg) > RESET_ARG_MAX) {
        scePrintf("too long parameter '%s'\n", arg);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = param;
    while (*udnl) *d++ = *udnl++;
    while (*arg) *d++ = *arg++;
    *d = 0;
    return sceSifResetIop(param, 0);
}
