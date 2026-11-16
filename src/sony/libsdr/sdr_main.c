#include "dw4/eekernel_gp.h"
#include "dw4/sony/sif.h"
#include "dw4/libkernl.h"

typedef struct sceSifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

typedef char *ArgList;
#define ARGS_START(args, last) ((args) = (ArgList)__builtin_next_arg(last) - (8 - __builtin_args_info(0)) * 8)
#define ARGS_NEXT(args, type) ((args) += 8, *(type *)((args) - 8))

typedef struct {
    unsigned short func;
    unsigned short entry;
    unsigned int value;
} SdBatch;

#define SD_REMOTE_SERVER 0x80000701

/* sdrcmd.h command ids sdr.irx dispatches on */
#define rSdSetEffectAttr 0x8130
#define rSdGetEffectAttr 0x8140
#define rSdSetTransIntrHandler 0x8160
#define rSdSetSpu2IntrHandler 0x8170
#define rSdSetEffectMode 0x81a0
#define rSdSetEffectModeParams 0x81b0
#define rSdProcBatch2 0x81c0
#define rSdProcBatchEx2 0x81d0
#define rSdUserCommand0 0x9000
#define rSdUserCommandF 0x90f0

unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
int sceSifDmaStat(unsigned int id);

/* the IOP interrupt callbacks and their gp: libsdr's callback-thread file owns them */
extern void *_sce_sdr_transIntr0Hdr, *_sce_sdr_transIntr1Hdr, *_sce_sdr_spu2IntrHdr;
extern void *_sce_sdr_transIntr0Arg, *_sce_sdr_transIntr1Arg, *_sce_sdr_spu2IntrArg;
extern void *_sce_sdr_transIntr0Gp, *_sce_sdr_transIntr1Gp, *_sce_sdr_spu2IntrGp;

static sceSifEndFunc sceSdEndFunc = 0;
static void *sceSdEndGp = 0;
char libsdrVersion[16] = "PsIIlibsdr  2800";

static unsigned int sbuff[16] __attribute__((aligned(64)));
static sceSifClientData sceSd_gCd;

int sceSdRemoteInit(void)
{
    int i;

    sceSifInitRpc(0);
    do {
        if (sceSifBindRpc(&sceSd_gCd, SD_REMOTE_SERVER, 0) < 0) {
            scePrintf("sceSdRemoteInit() RPC bind error!\n");
            return -1;
        }
        i = 10000;
        while (i--)
            ;
    } while (sceSd_gCd.serve == 0);
    sceSdEndFunc = 0;
    sceSdEndGp = 0;
    FlushCache(0);
    return 0;
}

int sceSdTransToIOP(unsigned int src, unsigned int dest, int size, int wait)
{
    static sceSifDmaData transData;
    unsigned int id;

    if (wait == 0) return -1;
    transData.data = src;
    transData.addr = dest;
    transData.size = size;
    transData.mode = 0;
    id = sceSifSetDma(&transData, 1);
    if (id == 0) return -1;
    if (wait == 1) {
        while (sceSifDmaStat(id) >= 0)
            ;
    }
    return 0;
}

sceSifEndFunc sceSdCallBack(sceSifEndFunc func)
{
    sceSifEndFunc prev = sceSdEndFunc;

    sceSdEndFunc = func;
    sceSdEndGp = GetGp();
    return prev;
}

int sceSdRemote(int block, ...)
{
    int ret, i;
    unsigned int mode, command;
    ArgList args;
    sceSifEndFunc end = 0;
    int previous;
    void *gp = 0;

    ARGS_START(args, block);
    mode = block;
    command = ARGS_NEXT(args, int);
    sbuff[0] = (int)sbuff;
    for (i = 1; i < 7; i++) {
        sbuff[i] = ARGS_NEXT(args, int);
    }
    if (mode == 0) {
        mode = 1;
        end = sceSdEndFunc;
    } else {
        mode = 0;
    }
    previous = 0;
    if (command == rSdSetTransIntrHandler) {
        if (sbuff[1] == 0) {
            previous = (int)_sce_sdr_transIntr0Hdr;
            _sce_sdr_transIntr0Hdr = (void *)sbuff[2];
            _sce_sdr_transIntr0Arg = (void *)sbuff[3];
            _sce_sdr_transIntr0Gp = GetGp();
        } else {
            previous = (int)_sce_sdr_transIntr1Hdr;
            _sce_sdr_transIntr1Hdr = (void *)sbuff[2];
            _sce_sdr_transIntr1Arg = (void *)sbuff[3];
            _sce_sdr_transIntr1Gp = GetGp();
        }
    } else if (command == rSdSetSpu2IntrHandler) {
        previous = (int)_sce_sdr_spu2IntrHdr;
        _sce_sdr_spu2IntrHdr = (void *)sbuff[1];
        _sce_sdr_spu2IntrArg = (void *)sbuff[2];
        _sce_sdr_spu2IntrGp = GetGp();
    }
    ret = 0;
    if (command == rSdSetEffectAttr || command == rSdSetEffectMode || command == rSdSetEffectModeParams) {
        if (end != 0) gp = SetGp(sceSdEndGp);
        sceSifCallRpc(&sceSd_gCd, command | sbuff[1], mode, (void *)sbuff[2], 64, sbuff, 64,
                     end, (void *)sbuff[0]);
        if (end != 0) (void)SetGp(gp);
        ret = sbuff[0];
    } else if (command == rSdGetEffectAttr) {
        if (end != 0) gp = SetGp(sceSdEndGp);
        sceSifCallRpc(&sceSd_gCd, command | sbuff[1], mode, &sbuff[0], 64, (void *)sbuff[2],
                     64, end, (void *)sbuff[2]);
        if (end != 0) (void)SetGp(gp);
    } else if (command == rSdProcBatch2 || command == rSdProcBatchEx2) {
        SdBatch *batch;
        unsigned int results;
        int resultsSize;

        batch = (SdBatch *)sbuff[1];
        batch[0].entry = sbuff[2];
        if (command == rSdProcBatchEx2) {
            batch[0].value = sbuff[5];
        }
        results = sbuff[3];
        resultsSize = sbuff[4];
        if (sbuff[3] == 0) {
            results = (unsigned int)&ret;
            resultsSize = 4;
        }
        if (end != 0) gp = SetGp(sceSdEndGp);
        sceSifCallRpc(&sceSd_gCd, command, mode, (void *)sbuff[1],
                     (int)(sizeof(SdBatch) * (sbuff[2] + 1)), (void *)results, resultsSize, end,
                     (void *)sbuff);
        if (end != 0) (void)SetGp(gp);
        if (sbuff[3] != 0) {
            ret = (int)*(unsigned int *)sbuff[3];
        }
    } else if (command >= rSdUserCommand0 && command <= rSdUserCommandF) {
        if (end != 0) gp = SetGp(sceSdEndGp);
        sceSifCallRpc(&sceSd_gCd, command, mode, (void *)sbuff[1], (int)sbuff[2], &sbuff[0], 16,
                     end, &sbuff[0]);
        if (end != 0) (void)SetGp(gp);
        ret = sbuff[0];
    } else {
        if (end != 0) gp = SetGp(sceSdEndGp);
        sceSifCallRpc(&sceSd_gCd, command, mode, &sbuff[0], 64, &sbuff[0], 16, end, &sbuff[0]);
        if (end != 0) (void)SetGp(gp);
        ret = sbuff[0];
    }
    switch (command) {
    case rSdSetTransIntrHandler:
    case rSdSetSpu2IntrHandler:
        ret = previous;
        break;
    }
    return ret;
}
