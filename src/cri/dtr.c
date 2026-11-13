typedef struct SjObj SjObj;

typedef struct SjChunk {
    char *data;
    int len;
} SjChunk;

typedef struct SjVtbl {
    char pad0[24];
    void (*GetChunk)(SjObj *sj, int line, int nbyte, SjChunk *ck);
    void (*UngetChunk)(SjObj *sj, int line, SjChunk *ck);
    void (*PutChunk)(SjObj *sj, int line, SjChunk *ck);
} SjVtbl;

struct SjObj {
    SjVtbl *vtbl;
};

typedef struct SifDmaData {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} SifDmaData;

typedef struct DtrObj {
    signed char used;       /* 0x00 */
    signed char stat;       /* 0x01 */
    signed char transfer;   /* 0x02 */
    char pad3;
    SjObj *sjs;             /* 0x04 */
    SjObj *sjd;             /* 0x08 */
    SjChunk cks;            /* 0x0c */
    SjChunk ckd;            /* 0x14 */
    SifDmaData dma;         /* 0x1c */
    unsigned int dmaid;     /* 0x2c */
    int f48;                /* 0x30 */
    int f52;                /* 0x34 */
    int unit;               /* 0x38 */
    int total;              /* 0x3c */
} DtrObj;

extern int DAT_004a930c;
extern DtrObj DAT_004a9310[32];

extern char DAT_004eff50[];
extern char DAT_004eff70[];
extern char DAT_004eff98[];
extern char DAT_004effc8[];
extern char DAT_004efff0[];
extern char DAT_004f0018[];
extern char DAT_004f0040[];
extern char DAT_004f0058[];
extern char DAT_004f0068[];

void *memset(void *dst, int value, unsigned int n);
void ADXMSG_PrintErr(const char *format, ...);
void SJ_SplitChunk(SjChunk *ck, int nbyte, SjChunk *ck1, SjChunk *ck2);
void SyncDCache(char *start, char *end);
int sceSifDmaStat(unsigned int id);
unsigned int sceSifSetDma(SifDmaData *sdd, int len);
void SJCRS_Lock(void);
void SJCRS_Unlock(void);
void DTX_ExecServer(void);

void FUN_002729e8(DtrObj *dtr)
{
    SjChunk cks;
    SjChunk cks2;
    SjChunk ckd;
    SjChunk ckd2;
    int n;
    if (dtr->stat != 1) {
        return;
    }
    if (dtr->transfer == 1) {
        dtr->sjs->vtbl->PutChunk(dtr->sjs, 0, &dtr->cks);
        dtr->cks.data = 0;
        dtr->cks.len = 0;
        dtr->sjd->vtbl->PutChunk(dtr->sjd, 1, &dtr->ckd);
        dtr->ckd.data = 0;
        dtr->ckd.len = 0;
        dtr->total += dtr->cks.len;
        dtr->transfer = 0;
        if (dtr->cks.len != 0) {
            ADXMSG_PrintErr(DAT_004eff50);
            for (;;) {
            }
        }
    }
    if (dtr->transfer != 0) {
        return;
    }
    dtr->sjs->vtbl->GetChunk(dtr->sjs, 1, 0x7fffffff, &cks);
    dtr->sjd->vtbl->GetChunk(dtr->sjd, 0, 0x7fffffff, &ckd);
    n = cks.len < ckd.len ? cks.len : ckd.len;
    n = n / dtr->unit * dtr->unit;
    SJ_SplitChunk(&cks, n, &cks, &cks2);
    dtr->sjs->vtbl->UngetChunk(dtr->sjs, 1, &cks2);
    SJ_SplitChunk(&ckd, n, &ckd, &ckd2);
    dtr->sjd->vtbl->UngetChunk(dtr->sjd, 0, &ckd2);
    if (n <= 0) {
        return;
    }
    if (cks.len & 63) {
        ADXMSG_PrintErr(DAT_004eff70);
        ADXMSG_PrintErr(DAT_004eff98, cks.data, ckd.data, cks.len);
        for (;;) {
        }
    }
    if ((int)cks.data & 63) {
        ADXMSG_PrintErr(DAT_004effc8);
        ADXMSG_PrintErr(DAT_004eff98, cks.data, ckd.data, cks.len);
        for (;;) {
        }
    }
    if ((int)ckd.data & 63) {
        ADXMSG_PrintErr(DAT_004efff0);
        ADXMSG_PrintErr(DAT_004eff98, cks.data, ckd.data, cks.len);
        for (;;) {
        }
    }
    SyncDCache(cks.data, cks.data + cks.len - 1);
    dtr->dma.data = (unsigned int)cks.data & 0x0fffffff;
    dtr->dma.addr = (unsigned int)ckd.data;
    dtr->dma.size = cks.len;
    dtr->dma.mode = 0;
    dtr->dmaid = sceSifSetDma(&dtr->dma, 1);
    if (dtr->dmaid == 0) {
        ADXMSG_PrintErr(DAT_004f0018);
        dtr->sjs->vtbl->UngetChunk(dtr->sjs, 1, &cks);
        dtr->sjd->vtbl->UngetChunk(dtr->sjd, 0, &ckd);
        return;
    }
    dtr->cks = cks;
    dtr->ckd = ckd;
    dtr->transfer = 1;
}

signed char FUN_00272d58(DtrObj *dtr)
{
    return dtr->stat;
}

void DTR_ExecServer(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (DAT_004a9310[i].stat == 1 && DAT_004a9310[i].transfer == 1) {
            if (sceSifDmaStat(DAT_004a9310[i].dmaid) >= 0) {
                return;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (DAT_004a9310[i].used == 1) {
            FUN_002729e8(&DAT_004a9310[i]);
        }
    }
    DTX_ExecServer();
}

void FUN_00272e20(void)
{
    ADXMSG_PrintErr(DAT_004f0040, DAT_004a930c);
    if (DAT_004a930c == 0) {
        memset(DAT_004a9310, 0, sizeof(DAT_004a9310));
    }
    DAT_004a930c++;
    ADXMSG_PrintErr(DAT_004f0058);
}

void FUN_00272e88(void)
{
    DAT_004a930c--;
}

DtrObj *FUN_00272ea0(SjObj *sjs, SjObj *sjd)
{
    DtrObj *dtr;
    int i;
    SJCRS_Lock();
    for (i = 0; i < 32; i++) {
        dtr = &DAT_004a9310[i];
        if (dtr->used == 0) {
            break;
        }
    }
    if (i == 32) {
        ADXMSG_PrintErr(DAT_004f0068, 32, 32);
        dtr = 0;
    } else {
        memset(dtr, 0, sizeof(DtrObj));
        /* matching construct: statement-order sweep — the int store of 1 before the byte store */
        dtr->stat = 0;
        dtr->unit = 64;
        dtr->sjs = sjs;
        dtr->sjd = sjd;
        dtr->transfer = 0;
        dtr->f48 = 1;
        dtr->used = 1;
        dtr->f52 = 0;
    }
    SJCRS_Unlock();
    return dtr;
}

void DTR_Destroy(DtrObj *dtr)
{
    SJCRS_Lock();
    dtr->used = 0;
    SJCRS_Unlock();
}

void FUN_00272fb8(DtrObj *dtr)
{
    dtr->total = 0;
    dtr->stat = 1;
}

void DTR_Stop(DtrObj *dtr)
{
    dtr->stat = 0;
    if (dtr->transfer == 1) {
        while (sceSifDmaStat(dtr->dmaid) >= 0) {
        }
        dtr->sjs->vtbl->PutChunk(dtr->sjs, 0, &dtr->cks);
        dtr->cks.data = 0;
        dtr->cks.len = 0;
        dtr->sjd->vtbl->PutChunk(dtr->sjd, 1, &dtr->ckd);
        dtr->ckd.data = 0;
        dtr->ckd.len = 0;
        dtr->total += dtr->cks.len;
        dtr->transfer = 0;
    }
}
