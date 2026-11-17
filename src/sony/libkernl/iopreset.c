/* iopreset.c - resetting and rebooting the IOP over SIF. */

#include "dw4/sony/sif.h"
#include "dw4/sony/sifdev.h"
#include "dw4/sony/libkernl.h"

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

void sceSifStopDma(void);

static SifResetPacket resetPacket __attribute__((aligned(64)));

int sceSifResetIop(const char *arg, int mode)
{
    sceSifDmaData dma;
    unsigned int dest;
    int i;
    sceSifExecNotifyHandler(0, 0);
    sceSifExecNotifyHandler(1, 0);
    sceSifStopDma();
    dest = sceSifGetReg(SIF_REG_MAINADDR);
    resetPacket.mode = mode;
    for (i = 0; arg[i] != 0; i++) {
        resetPacket.arg[i] = arg[i];
    }
    resetPacket.dest = 0;
    resetPacket.dsize = 0;
    resetPacket.psize = sizeof(SifResetPacket);
    resetPacket.size = i;
    resetPacket.cid = SIF_CMD_RESET;
    dma.data = (unsigned int)&resetPacket;
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
