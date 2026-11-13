/* MWSFD settings and the scratchpad swap: while Sofdec runs its server, the game's scratchpad is
 * parked in mwsfd_spr_save_buf and Sofdec's own scratchpad image is loaded from mwsfd_spr_work_buf. */

#define MWSFD_SPR_SIZE 0x4000
#define MWSFD_SPR_ADDR 0x70000000
#define DMA_CH_FROM_SPR 8
#define DMA_CH_TO_SPR 9

typedef struct DmaChan {
    char pad0[128];
    int sadr; /* 128: scratchpad address of the transfer */
} DmaChan;

/* Called with each new player handle and the scratchpad-swap enable. */
typedef void (*MwsfdCreateCb)(void *ply, int sprEnable);

extern int mwsfd_enable;
extern MwsfdCreateCb mwsfd_create_cb;
extern int mwsfd_spr_swapped;
extern int mwsfd_spr_cpu_copy;
extern char mwsfd_spr_save_buf[MWSFD_SPR_SIZE];
extern char mwsfd_spr_work_buf[MWSFD_SPR_SIZE];

void *memcpy(void *dst, const void *src, unsigned int size);
DmaChan *sceDmaGetChan(int id);
int sceDmaSync(DmaChan *ch, int mode, int timeout);
void sceDmaRecvN(DmaChan *ch, void *data, int qwc);
void sceDmaSendN(DmaChan *ch, void *data, int qwc);
void ADXM_ExecVsyncFrame(void);

void mwsfrsc_InitVal(void);
int MWSFD_GetUseSPR(void);
void mwrsc_WaitSprDmaEnd(void);
int MWSPR_SaveSprMem(int sprOfs, int size, void *dst);
int MWSPR_RestoreSprMem(void *src, int size, int sprOfs);
void MWDMA_WaitEnd(int id);

void MWSFD_InitRsc(void) {
    mwsfrsc_InitVal();
}

void MWSFD_FinishRsc(void) {
    mwsfrsc_InitVal();
}

void MWRSC_SaveRsc(void) {
    int enable = MWSFD_GetUseSPR();
    if (enable == 1 && mwsfd_spr_swapped != enable) {
        mwrsc_WaitSprDmaEnd();
        MWSPR_SaveSprMem(0, MWSFD_SPR_SIZE, mwsfd_spr_save_buf);
        MWDMA_WaitEnd(DMA_CH_FROM_SPR);
        MWSPR_RestoreSprMem(mwsfd_spr_work_buf, MWSFD_SPR_SIZE, 0);
        MWDMA_WaitEnd(DMA_CH_TO_SPR);
        mwsfd_spr_swapped = enable;
    }
}

void MWRSC_RestoreRsc(void) {
    if (MWSFD_GetUseSPR() == 1 && mwsfd_spr_swapped != 0) {
        mwrsc_WaitSprDmaEnd();
        MWSPR_SaveSprMem(0, MWSFD_SPR_SIZE, mwsfd_spr_work_buf);
        MWDMA_WaitEnd(DMA_CH_FROM_SPR);
        MWSPR_RestoreSprMem(mwsfd_spr_save_buf, MWSFD_SPR_SIZE, 0);
        MWDMA_WaitEnd(DMA_CH_TO_SPR);
        mwsfd_spr_swapped = 0;
    }
}

void MWSFD_SetUseSPR(int enable) {
    if (enable == 0) {
        mwsfd_enable = 0;
        return;
    }
    mwsfd_enable = 1;
}

int MWSFD_GetUseSPR(void) {
    return mwsfd_enable;
}

void MWSFD_SetSetSprCbFn(MwsfdCreateCb fn) {
    mwsfd_create_cb = fn;
}

void MWSFD_ExecSetSprCbFn(void *ply) {
    int enable = MWSFD_GetUseSPR();
    if (mwsfd_create_cb != 0) {
        mwsfd_create_cb(ply, enable);
    }
}

void mwsfrsc_InitVal(void) {
    mwsfd_enable = 1;
    mwsfd_create_cb = 0;
    mwsfd_spr_swapped = 0;
    mwsfd_spr_cpu_copy = 0;
}

void mwrsc_WaitSprDmaEnd(void) {
    MWDMA_WaitEnd(DMA_CH_FROM_SPR);
    MWDMA_WaitEnd(DMA_CH_TO_SPR);
}

int MWSPR_SaveSprByCpu(int sprOfs, int size, void *dst);
int MWSPR_SaveSprByDma(int sprOfs, int size, void *dst);

/* matching construct: the copy's result is dropped and the function falls off its end; returning
 * it turns the calls into tail jumps, retail keeps jal + return. */
int MWSPR_SaveSprMem(int sprOfs, int size, void *dst) {
    if (mwsfd_spr_cpu_copy == 0) {
        MWSPR_SaveSprByDma(sprOfs, size, dst);
    } else {
        MWSPR_SaveSprByCpu(sprOfs, size, dst);
    }
}

int MWSPR_SaveSprByCpu(int sprOfs, int size, void *dst) {
    memcpy(dst, (void *)(sprOfs + MWSFD_SPR_ADDR), size);
    return 0;
}

int MWSPR_SaveSprByDma(int sprOfs, int size, void *dst) {
    DmaChan *ch = sceDmaGetChan(DMA_CH_FROM_SPR);
    ch->sadr = sprOfs;
    sceDmaRecvN(ch, dst, size / 16);
    return 0;
}

int MWSPR_RestoreSprByCpu(void *src, int size, int sprOfs);
int MWSPR_RestoreSprByDma(void *src, int size, int sprOfs);

/* matching construct: as MWSPR_SaveSprMem. */
int MWSPR_RestoreSprMem(void *src, int size, int sprOfs) {
    if (mwsfd_spr_cpu_copy == 0) {
        MWSPR_RestoreSprByDma(src, size, sprOfs);
    } else {
        MWSPR_RestoreSprByCpu(src, size, sprOfs);
    }
}

int MWSPR_RestoreSprByCpu(void *src, int size, int sprOfs) {
    memcpy((void *)(sprOfs + MWSFD_SPR_ADDR), src, size);
    return 0;
}

int MWSPR_RestoreSprByDma(void *src, int size, int sprOfs) {
    DmaChan *ch = sceDmaGetChan(DMA_CH_TO_SPR);
    ch->sadr = sprOfs;
    sceDmaSendN(ch, src, size / 16);
    return 0;
}

/* Non-zero: the scratchpad swap copies with memcpy instead of DMA channels 8/9. */
void MWSFD_SetSprCpMode(int on) {
    mwsfd_spr_cpu_copy = on;
}

int MWSFD_GetSprCpMode(void) {
    return mwsfd_spr_cpu_copy;
}

void MWDMA_WaitEnd(int id) {
    DmaChan *ch = sceDmaGetChan(id);
    while (sceDmaSync(ch, 1, 30) != 0) {
    }
}

void MWDMA_GetStat(int id, int *stat) {
    *stat = sceDmaSync(sceDmaGetChan(id), 1, 30);
}

void MWSFD_ExecVsyncFrame(void) {
    ADXM_ExecVsyncFrame();
}

void mwPlySaveRsc(void) {
    MWRSC_SaveRsc();
}

void mwPlyRestoreRsc(void) {
    MWRSC_RestoreRsc();
}

/* Empty hooks: the player calls the first two when it starts a file range and the third from its
 * server's stop path. */
void MWSFSEE_StartFnameSub1(void *ply, int ofst, int nsct) {
}

void MWSFSEE_StartFnameSub2(void *ply, int ofst, int nsct) {
}

void MWSFSEE_ChkSupply(void *ply) {
}
