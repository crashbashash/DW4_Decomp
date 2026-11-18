#include <string.h>
#include "dw4/cri/sj.h"
#include "dw4/cri/dtr.h"
#include "dw4/cri/dtx.h"
#include "dw4/cri/adxmsg.h"
#include "dw4/sony/libkernl.h"
#include "dw4/sony/sif.h"

struct DtrObj {
    signed char used;       /* 0x00 */
    signed char stat;       /* 0x01 */
    signed char transfer;   /* 0x02 */
    char rsv;               /* 0x03 */
    SfdSj *sjs;             /* 0x04 */
    SfdSj *sjd;             /* 0x08 */
    SfdSjChunk cks;            /* 0x0c */
    SfdSjChunk ckd;            /* 0x14 */
    sceSifDmaData dma;      /* 0x1c */
    unsigned int dmaid;     /* 0x2c */
    int srclin;              /* 0x30 */
    int dstlin;              /* 0x34 */
    int unit;               /* 0x38 */
    int total;              /* 0x3c */
};

const char *dtr_build = "\nDTR Ver.1.06 Build:Oct  6 2004 11:47:40\n";
int dtr_init_cnt = 0;
DtrObj dtr_obj[32] = {0};

void DTR_ExecHndl(DtrObj *dtr)
{
    SfdSjChunk cks;
    SfdSjChunk cks2;
    SfdSjChunk ckd;
    SfdSjChunk ckd2;
    int n;
    if (dtr->stat != 1) {
        return;
    }
    if (dtr->transfer == 1) {
        dtr->sjs->vtbl->putChunk(dtr->sjs, 0, &dtr->cks);
        dtr->cks.data = 0;
        dtr->cks.len = 0;
        dtr->sjd->vtbl->putChunk(dtr->sjd, 1, &dtr->ckd);
        dtr->ckd.data = 0;
        dtr->ckd.len = 0;
        dtr->total += dtr->cks.len;
        dtr->transfer = 0;
        if (dtr->cks.len != 0) {
            ADXMSG_PrintErr("DTR_ExecHndl: Internal Error\n");
            for (;;) {
            }
        }
    }
    if (dtr->transfer != 0) {
        return;
    }
    dtr->sjs->vtbl->getChunk(dtr->sjs, 1, 0x7fffffff, &cks);
    dtr->sjd->vtbl->getChunk(dtr->sjd, 0, 0x7fffffff, &ckd);
    n = cks.len < ckd.len ? cks.len : ckd.len;
    n = n / dtr->unit * dtr->unit;
    SJ_SplitChunk(&cks, n, &cks, &cks2);
    dtr->sjs->vtbl->ungetChunk(dtr->sjs, 1, &cks2);
    SJ_SplitChunk(&ckd, n, &ckd, &ckd2);
    dtr->sjd->vtbl->ungetChunk(dtr->sjd, 0, &ckd2);
    if (n <= 0) {
        return;
    }
    if (cks.len & 63) {
        ADXMSG_PrintErr("DTR_ExecHndl: Internal Error len\n");
        ADXMSG_PrintErr("cks.data=%08x, ckd.data=%08x, cks.len=%d\n", cks.data, ckd.data, cks.len);
        for (;;) {
        }
    }
    if ((int)cks.data & 63) {
        ADXMSG_PrintErr("DTR_ExecHndl: Internal Error cks.data\n");
        ADXMSG_PrintErr("cks.data=%08x, ckd.data=%08x, cks.len=%d\n", cks.data, ckd.data, cks.len);
        for (;;) {
        }
    }
    if ((int)ckd.data & 63) {
        ADXMSG_PrintErr("DTR_ExecHndl: Internal Error ckd.data\n");
        ADXMSG_PrintErr("cks.data=%08x, ckd.data=%08x, cks.len=%d\n", cks.data, ckd.data, cks.len);
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
        ADXMSG_PrintErr("E0101701 DTR_ExecHndl: can't use DMA\n");
        dtr->sjs->vtbl->ungetChunk(dtr->sjs, 1, &cks);
        dtr->sjd->vtbl->ungetChunk(dtr->sjd, 0, &ckd);
        return;
    }
    dtr->cks = cks;
    dtr->ckd = ckd;
    dtr->transfer = 1;
}

signed char DTR_GetStat(DtrObj *dtr)
{
    return dtr->stat;
}

void DTR_ExecServer(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (dtr_obj[i].stat == 1 && dtr_obj[i].transfer == 1) {
            if (sceSifDmaStat(dtr_obj[i].dmaid) >= 0) {
                return;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (dtr_obj[i].used == 1) {
            DTR_ExecHndl(&dtr_obj[i]);
        }
    }
    DTX_ExecServer();
}

void DTR_Init(void)
{
    ADXMSG_PrintErr("DTR_Init: in (%d)\n", dtr_init_cnt);
    if (dtr_init_cnt == 0) {
        memset(dtr_obj, 0, sizeof(dtr_obj));
    }
    dtr_init_cnt++;
    ADXMSG_PrintErr("DTR_Init: out\n");
}

void DTR_Finish(void)
{
    dtr_init_cnt--;
}

DtrObj *DTR_Create(SfdSj *sjs, SfdSj *sjd)
{
    DtrObj *dtr;
    int i;
    SJCRS_Lock();
    for (i = 0; i < 32; i++) {
        dtr = &dtr_obj[i];
        if (dtr->used == 0) {
            break;
        }
    }
    if (i == 32) {
        ADXMSG_PrintErr("i:%d DTR_MAX_OBJ:%d\n", 32, 32);
        dtr = 0;
    } else {
        memset(dtr, 0, sizeof(DtrObj));
        /* matching construct: statement-order sweep — the int store of 1 before the byte store */
        dtr->stat = 0;
        dtr->unit = 64;
        dtr->sjs = sjs;
        dtr->sjd = sjd;
        dtr->transfer = 0;
        dtr->srclin = 1;
        dtr->used = 1;
        dtr->dstlin = 0;
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

void DTR_Start(DtrObj *dtr)
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
        dtr->sjs->vtbl->putChunk(dtr->sjs, 0, &dtr->cks);
        dtr->cks.data = 0;
        dtr->cks.len = 0;
        dtr->sjd->vtbl->putChunk(dtr->sjd, 1, &dtr->ckd);
        dtr->ckd.data = 0;
        dtr->ckd.len = 0;
        dtr->total += dtr->cks.len;
        dtr->transfer = 0;
    }
}
