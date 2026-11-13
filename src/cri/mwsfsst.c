/* MWSST: the player's SST input. A caller-supplied table of input callbacks feeds an SJ ring that
 * MWSST_Create builds over a work buffer and binds to the SFD player as the video stream
 * 0xC0 + stmNo; the functions here call through that table for the player's input. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/sfdsj.h"

typedef struct MwsfdInputCbTbl {
    void (*init)(void);                                        /* 0 */
    void (*finish)(void);                                      /* 4 */
    int (*calcWork)(int *size0, int *size1, int *size2);       /* 8 */
    int (*create)(char *work, int size);                       /* 12 */
    void (*destroy)(int hn);                                   /* 16 */
    void (*start)(int hn, SfdSj *sj);                          /* 20 */
    void (*stop)(int hn);                                      /* 24 */
    int (*getStat)(int hn);                                    /* 28 */
    void (*func32)(int hn, int a, int b);                      /* 32 */
    void (*pause)(int hn, int sw);                             /* 36 */
    void (*func40)(int hn, int arg);                           /* 40 */
    int (*func44)(int hn);                                     /* 44 */
} MwsfdInputCbTbl;

/* the installed table and how many times its init ran */
typedef struct MwsfdInputCb {
    MwsfdInputCbTbl *tbl;
    int nInit;
} MwsfdInputCb;

extern MwsfdInputCb mwsfd_input_cb_tbl;

void SFD_SetStmObject(void *sfd, int stmId, SfdSj *sj, int a3, int t0);
void MWSFSVM_GotoIdleBorder(void);

MwsfdInputCb *mwsst_GetCb(void);
MwsfdInputCbTbl *mwsst_GetCbTbl(void);
int mwsst_IsActive(MwsfdSst *sst);
void mwsst_ChangeStm(MwsfdPly *ply, int stmNo);
int mwsst_GetWorkSizes(int *size0, int *size1, int *size2);
int mwsst_GetWorkSizesLarge(int *size0, int *size1, int *size2);

int MWSST_CalcWork(void)
{
    int size0, size1, size2;

    return mwsst_GetWorkSizes(&size0, &size1, &size2);
}

int MWSST_CalcWorkAlt(void)
{
    int size0, size1, size2;

    return mwsst_GetWorkSizes(&size0, &size1, &size2);
}

int MWSST_CalcWorkLarge(void)
{
    int size0, size1, size2;

    return mwsst_GetWorkSizesLarge(&size0, &size1, &size2);
}

int mwsst_GetWorkSizes(int *size0, int *size1, int *size2)
{
    *size0 = 0x249E4;
    *size1 = 0x9C40;
    *size2 = 0x800;
    return *size0 + *size1 + *size2;
}

int mwsst_GetWorkSizesLarge(int *size0, int *size1, int *size2)
{
    *size0 = 0x6952C;
    *size1 = 0x13C68;
    *size2 = 0x2000;
    return *size0 + *size1 + *size2;
}

void MWSST_SetStmNo(MwsfdPly *ply, int stmNo)
{
    mwsst_ChangeStm(ply, stmNo);
}

/* moves the SST's SJ from the SFD stream it feeds to stream 0xC0 + stmNo */
void mwsst_ChangeStm(MwsfdPly *ply, int stmNo)
{
    MwsfdSst *sst = &ply->sst;
    void *sfd = ply->sfd;
    SfdSj *sj = sst->sj;

    SFD_SetStmObject(sfd, sst->stmNo + 0xC0, 0, 0, 0);
    SFD_SetStmObject(sfd, stmNo + 0xC0, sj, 0, 0);
    sst->stmNo = stmNo;
}

SfdSj *mwply_GetInputSj(MwsfdPly *ply)
{
    return ply->sst.sj;
}

int mwply_GetInputExtHn(MwsfdPly *ply)
{
    return ply->sst.extHn;
}

/* runs the table's init on the first call only */
void mwsst_Init(void)
{
    MwsfdInputCb *cb = mwsst_GetCb();
    MwsfdInputCbTbl *tbl = mwsst_GetCbTbl();

    if (tbl != 0 && cb->nInit == 0) {
        if (tbl->init != 0) {
            tbl->init();
        }
        cb->nInit++;
    }
}

/* runs the table's finish when the last init is undone */
void mwsst_Finish(void)
{
    MwsfdInputCb *cb = mwsst_GetCb();
    MwsfdInputCbTbl *tbl = mwsst_GetCbTbl();

    if (tbl != 0 && cb->nInit != 0 && --cb->nInit == 0 && tbl->finish != 0) {
        tbl->finish();
    }
}

int mwsst_CalcWork(int *size0, int *size1, int *size2)
{
    MwsfdInputCbTbl *tbl = mwsst_GetCbTbl();
    int total = 0;

    if (tbl != 0 && tbl->calcWork != 0) {
        total = tbl->calcWork(size0, size1, size2);
    }
    return total;
}

int mwsst_CreateExt(char *work, int size)
{
    MwsfdInputCbTbl *tbl = mwsst_GetCbTbl();
    int hn = 0;

    if (tbl != 0 && tbl->create != 0) {
        hn = tbl->create(work, size);
    }
    return hn;
}

void mwsst_DestroyExt(int hn)
{
    MwsfdInputCbTbl *tbl = mwsst_GetCbTbl();

    if (hn != 0 && tbl != 0 && tbl->destroy != 0) {
        tbl->destroy(hn);
    }
}

/* matching construct: in the functions below the handle is read before the table checks
 * (retail loads it in the first branch's delay slot) */
void mwsst_Start(MwsfdSst *sst)
{
    MwsfdInputCbTbl *tbl;

    if (mwsst_IsActive(sst) == 1) {
        int hn;
        SfdSj *sj;

        tbl = mwsst_GetCbTbl();
        hn = sst->extHn;
        sj = sst->sj;
        if (tbl != 0 && tbl->start != 0) {
            tbl->start(hn, sj);
        }
    }
}

void mwsst_Stop(MwsfdSst *sst)
{
    MwsfdInputCbTbl *tbl;

    if (mwsst_IsActive(sst) == 1) {
        int hn;

        tbl = mwsst_GetCbTbl();
        hn = sst->extHn;
        if (tbl != 0 && tbl->stop != 0) {
            tbl->stop(hn);
        }
    }
}

int mwsst_GetStat(MwsfdSst *sst)
{
    MwsfdInputCbTbl *tbl;
    int hn;
    int stat = 0;

    if (mwsst_IsActive(sst) != 1) {
        return 0;
    }
    tbl = mwsst_GetCbTbl();
    hn = sst->extHn;
    if (tbl != 0 && tbl->getStat != 0) {
        stat = tbl->getStat(hn);
    }
    return stat;
}

void mwsst_Call32(MwsfdSst *sst, int a, int b)
{
    MwsfdInputCbTbl *tbl;
    int hn;

    if (mwsst_IsActive(sst) == 1) {
        tbl = mwsst_GetCbTbl();
        hn = sst->extHn;
        if (tbl != 0 && tbl->func32 != 0) {
            tbl->func32(hn, a, b);
        }
    }
}

void mwsst_Pause(MwsfdSst *sst, int sw)
{
    MwsfdInputCbTbl *tbl;

    if (mwsst_IsActive(sst) == 1) {
        int hn;

        tbl = mwsst_GetCbTbl();
        hn = sst->extHn;
        if (tbl != 0 && tbl->pause != 0) {
            tbl->pause(hn, sw);
        }
    }
}

void mwsst_Call40(MwsfdSst *sst, int arg)
{
    MwsfdInputCbTbl *tbl;

    if (mwsst_IsActive(sst) == 1) {
        int hn;

        tbl = mwsst_GetCbTbl();
        hn = sst->extHn;
        if (tbl != 0 && tbl->func40 != 0) {
            tbl->func40(hn, arg);
        }
    }
}

int mwsst_Call44(MwsfdSst *sst)
{
    MwsfdInputCbTbl *tbl;
    int hn;
    int result = 0;

    if (mwsst_IsActive(sst) != 1) {
        return 0;
    }
    tbl = mwsst_GetCbTbl();
    hn = sst->extHn;
    if (tbl != 0 && tbl->func44 != 0) {
        result = tbl->func44(hn);
    }
    return result;
}

/* MWSST_Create (0x299ce8) links from the retail image */

/* stops the external input, resets the SJ and binds it to the SFD stream again; as retail does,
 * the external handle is what is passed for the input to stop */
void MWSST_Restart(MwsfdPly *ply)
{
    MwsfdSst *sst = &ply->sst;
    void *sfd = ply->sfd;
    int hn;
    SfdSj *sj;
    int stmNo;

    mwsst_GetCbTbl();
    hn = sst->extHn;
    sj = sst->sj;
    stmNo = sst->stmNo;
    if (mwsst_IsActive(sst) != 1) {
        return;
    }
    if (hn != 0) {
        mwsst_Stop((MwsfdSst *)hn);
    }
    sj->vtbl->reset(sj);
    SFD_SetStmObject(sfd, stmNo + 0xC0, sj, 0, 0);
}

void MWSST_Destroy(MwsfdSst *sst)
{
    int hn;
    SfdSj *sj;

    if (mwsst_IsActive(sst) == 1) {
        mwsst_GetCbTbl();
        hn = sst->extHn;
        sj = sst->sj;
        if (hn != 0) {
            MWSFSVM_GotoIdleBorder();
            mwsst_Stop((MwsfdSst *)hn);
            sst->created = 0;
            mwsst_DestroyExt(hn);
            sj->vtbl->destroy(sj);
            sst->extHn = 0;
            mwsst_Finish();
        }
    }
}

MwsfdInputCb *mwsst_GetCb(void)
{
    return &mwsfd_input_cb_tbl;
}

MwsfdInputCbTbl *mwsst_GetCbTbl(void)
{
    return mwsfd_input_cb_tbl.tbl;
}

void mwsfd_SetInputCbTbl(MwsfdInputCbTbl *tbl)
{
    mwsfd_input_cb_tbl.tbl = tbl;
}

int mwsst_IsActive(MwsfdSst *sst)
{
    if (mwsst_GetCbTbl() == 0) {
        return 0;
    }
    if (sst->created != 1) {
        return 0;
    }
    return sst->extHn != 0;
}
