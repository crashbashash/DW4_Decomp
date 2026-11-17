/* MWSFPLY: the MWSFD player's control. The SFD standby and start, the starts from a file, a file
 * range, an AFS entry, memory and an SJ, and the stop and pause. */
#include "dw4/cri/cri_mwsfd.h"
#include "dw4/cri/sj.h"
#include <stdio.h>
#include "dw4/cri/sfd.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/cri/lsc.h"

/* an object that opens a stream by name (vtbl +24) */
typedef struct MwsfdNameObj MwsfdNameObj;
typedef struct MwsfdNameObjVtbl {
    char pad0[24];
    void (*open)(MwsfdNameObj *obj, char *name); /* 24 */
} MwsfdNameObjVtbl;
struct MwsfdNameObj {
    MwsfdNameObjVtbl *vtbl;
};

void *memset(void *dst, int c, unsigned int n);
int strlen(const char *s);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, int n);

void mw_sfd_start_ex(MwsfdPly *ply);
void mwsfd_InitForStart(MwsfdPly *ply);
int mwPlySfdStandby(MwsfdPly *ply);
void mwSfdStartFnameSub(MwsfdPly *ply, char *fname, int ofst, int nsct);
void mwply_SetFnameAll(MwsfdPly *ply, char *fname);
void mwply_SetFnameRange(MwsfdPly *ply, char *fname, int ofst, int nsct);
void mwply_SetAfsRange(MwsfdPly *ply, int dir, int ofst);

int mwPlySfdStandby(MwsfdPly *ply)
{
    int err = SFD_Standby(ply->sfd);

    if (err != 0) {
        MWSFLIB_SetErrCode(-311);
        MWSFSVM_Error("E20010703F mwPlySfdStandby: ");
        err = -311;
    }
    return err;
}

int mwPlySfdStart(MwsfdPly *ply)
{
    int err = SFD_Start(ply->sfd);

    if (err != 0) {
        MWSFLIB_SetErrCode(-307);
        MWSFSVM_Error("E20010703G mwPlySfdStart: ");
        err = -307;
    }
    return err;
}

/* the player's SFD input buffer: the first chunk's address and length and the tail's length */
void mwPlySfdGetWritePtr(MwsfdPly *ply, char **data, int *len, int *tailLen)
{
    SfdBufStat stat;

    SFD_GetWritePtr(ply->sfd, &stat);
    *data = stat.ck0.data;
    *len = stat.ck0.len;
    *tailLen = stat.tailLen;
}

void mwPlySfdAddWritePtr(MwsfdPly *ply, int len1, int len2)
{
    void *sfd = ply->sfd;

    if (len1 >= 0) {
        SFD_AddWritePtr(sfd, len1, len2);
    }
}

int mwPlyIsPause(MwsfdPly *ply)
{
    int stat = SFD_GetPaStat(ply->sfd);
    int result;

    if (stat == 0) {
        result = 0;
    } else if (stat == 1) {
        result = 1;
    } else {
        MWSFSVM_Error("E10821A : Invalid value of SFD_GetPaStat : %d", stat);
        result = 0;
    }
    return result;
}

void mwPlyTermSupply(MwsfdPly *ply)
{
    SFD_TermSupply(ply->sfd);
}

/* matching construct: permuter, reduced by hand: the input object read just before its use */
void mw_sfd_start_ex(MwsfdPly *ply)
{
    void *input;

    MWSFLIB_GetLibWorkPtr();
    if (ply->sfd != 0) {
        if (MWSFCRE_ResetSfdHn(ply) != 0) {
            MWSFSVM_Error("E0203263: mw_sfd_start_ex: RESET failed.");
            return;
        }
        MWSST_Restart(ply);
        MWSFTAG_ResetAinfSj(ply);
        if (MWSFTAG_SetAinfSj(ply) != 0) {
            MWSFSVM_Error("E201213 mw_sfd_start_ex: can't set AddInfSJ");
            return;
        }
        mwsfsfx_ResetAddInf(ply);
        mwply_ResetPicLog(ply);
    }
    mwsfd_InitForStart(ply);
    mwPlySfdStandby(ply);
    mwSfdPause(ply, ply->pause);
    input = &ply->sst;
    mwsst_Pause(input, 1);
    mwsst_Start(input);
    ply->numSkipDisp = 0;
    ply->linkPrev = 0;
    ply->stat = 1;
}

void mwsfd_InitForStart(MwsfdPly *ply)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler keeps independent
     * stores in source order, so the statements follow the retail store order */
    ply->limit = 0;
    ply->count = 0;
}

void mwPlyStartFname(MwsfdPly *ply, char *fname)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122601: mwPlyStartFname: handle is invalid.");
        return;
    }
    if (fname == 0) {
        MWSFSVM_Error("E10915C: mwPlyStartFname: fname is NULL.");
        return;
    }
    mwSfdStartFnameSub(ply, fname, 0, -1);
}

void mwSfdStartFnameSub(MwsfdPly *ply, char *fname, int ofst, int nsct)
{
    ply->sj = ply->defSj;
    mwSfdStopDec(ply);
    mw_sfd_start_ex(ply);
    mwply_SetFnameAll(ply, fname);
    MWSFSEE_StartFnameSub1(ply, ofst, nsct);
    MWSFSEE_StartFnameSub2(ply, ofst, nsct);
}

void mwSfdStartMem(MwsfdPly *ply, char *buf, int size)
{
    SfdSj *sj;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122610 mwSfdStartMem: handle is invalid.");
        return;
    }
    mwSfdStopDec(ply);
    ply->memSj->vtbl->destroy(ply->memSj);
    sj = SJMEM_Create(buf, size);
    ply->memSj = sj;
    ply->sj = sj;
    ply->memBuf = buf;
    ply->memSize = size;
    mw_sfd_start_ex(ply);
    MWSFCRE_SetSupplySj(ply);
}

void mwSfdStartSj(MwsfdPly *ply, SfdSj *sj)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122609 mwSfdStartSj: handle is invalid.");
        return;
    }
    mwSfdStopDec(ply);
    ply->sj = sj;
    ply->srcType = 2;
    ply->srcBuf = 0;
    ply->srcSize = 0;
    ply->srcXSize = 0;
    mw_sfd_start_ex(ply);
    MWSFCRE_SetSupplySj(ply);
}

void mwSfdStopDec(MwsfdPly *ply)
{
    void *sfd = ply->sfd;

    if (sfd == 0) {
        return;
    }
    mwlSfdSleepDecSvr(ply);
    ply->stat = 0;
    if (SFD_Stop(sfd) != 0) {
        MWSFLIB_SetErrCode(-308);
        MWSFSVM_Error("E2003 mwSfdStop:can't stop SFD");
    }
    mwsst_Stop(&ply->sst);
    ply->f692 = 0;
    if (ply->stm != 0) {
        MWSTM_ReqStop(ply->stm);
    }
    LSC_Stop(ply->lsc);
}

void mwSfdStop(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122602 mwSfdStop: handle is invalid.");
        return;
    }
    mwSfdStopDec(ply);
    mwPlyLinkStm(ply, 0);
    ply->nEntry = 0;
    LSC_Stop(ply->lsc);
}

void mwSfdPause(MwsfdPly *ply, int sw)
{
    void *sfd;
    int value;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122604 mwSfdPause; handle is invalid.");
        return;
    }
    sfd = ply->sfd;
    if (ply->pause == 0 && sw == 0)
        return;
    if (MWSFD_GetPauseBdr() == 1 && ply->cre.type == 1) {
        if (SFD_GetCond(sfd, 6, &value) == 0) {
            if (value == 1)
                mwlSfdSleepDecSvr(ply);
        } else
            mwlSfdSleepDecSvr(ply);
    }
    if (SFD_Pause(sfd, sw) != 0) {
        MWSFLIB_SetErrCode(-310);
        MWSFSVM_Error("E2007 mwSfdPause; can't pause (%s)", sw == 1 ? "ON" : "OFF");
    }
    mwsst_Pause(&ply->sst, sw);
    ply->pause = sw;
}

void mwPlyStartAfs(MwsfdPly *ply, int dir, int ofst)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E1122638: mwPlyStartAfs: handle is invalid.");
        return;
    }
    ply->vtbl->setSj(ply, mwPlyGetInputSj(ply));
    mwply_SetAfsRange(ply, dir, ofst);
}

/* sets the input buffer's refill threshold to 80% of its size */
void MWSFPLY_SetFlowLimit(MwsfdPly *ply)
{
    int size = ply->inputBufSize;

    MWSFD_SetFlowLimit(ply, size * 0.8, size);
}

void mwPlyChkSupply(MwsfdPly *ply)
{
    void *stm = ply->stm;
    void *sfd = ply->sfd;

    if (stm != 0 && MWSTM_GetStat(stm) == 3) {
        SFD_TermSupply(sfd);
    }
}

void MWSFPLY_RecordFname(MwsfdPly *ply, const char *fname)
{
    if (ply->fnameMax < strlen(fname)) {
        MWSFSVM_Error("E211121: filename is longer.");
        strncpy(ply->fname, fname, ply->fnameMax);
        return;
    }
    strcpy(ply->fname, fname);
}

void mwply_SetFnameAll(MwsfdPly *ply, char *fname)
{
    mwply_SetFnameRange(ply, fname, 0, 0xFFFFF);
}

void mwply_SetFnameRange(MwsfdPly *ply, char *fname, int ofst, int nsct)
{
    MWSFPLY_RecordFname(ply, fname);
    ply->stmOfst = ofst;
    ply->stmNsct = nsct;
    ply->stmReq = 1;
    ply->stmDir = 0;
}

void mwply_SetAfsRange(MwsfdPly *ply, int dir, int ofst)
{
    void *outDir;
    int outOfst;
    int outNsct;

    if (ADXF_GetFnameRangeEx(dir, ofst, ply->fname, &outDir, &outOfst, &outNsct) == 0) {
        ply->stmDir = outDir;
        ply->stmOfst = outOfst;
        ply->stmNsct = outNsct;
        ply->stmReq = 1;
    } else {
        MWSFSVM_Error("E211151: ADXF_GetFnameRangeEx() faild.");
    }
}

/* opens a sector range by its "%08x.%08x" name (first sector, sector count) */
void mwply_OpenSctRange(MwsfdNameObj *obj, int first, unsigned int size)
{
    char name[20];

    sprintf(name, "%08x.%08x", first, (size + 2047) >> 11);
    obj->vtbl->open(obj, name);
    memset(name, 0, sizeof(name));
}

void mwPlyStartFnameRange(MwsfdPly *ply, char *fname, int ofst, int nsct)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        MWSFSVM_Error("E407021: mwPlyStartFnameRange: handle is invalid.");
        return;
    }
    if (fname == 0) {
        MWSFSVM_Error("E407022: mwPlyStartFnameRange: fname is NULL.");
        return;
    }
    ply->vtbl->setSj(ply, mwPlyGetInputSj(ply));
    mwply_SetFnameRange(ply, fname, ofst, nsct);
}
