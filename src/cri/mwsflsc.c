/* MWSFD seamless playback over LSC: queues files on the player's link stream controller and starts,
 * loops and releases the queue; the file names, AFS entries and file ranges become LSC entries. */
#include "dw4/cri/mwply.h"
#include "dw4/cri/lsc.h"

int sprintf(char *buf, const char *format, ...);
void *memset(void *dst, int value, unsigned int size);
void mwsfd_Error(const char *format, ...);
int MWSFD_IsEnableHndl(void *ply);
void mwSfdStartSj(MwsfdPly *ply, SfdSj *sj);
void MWSFPLY_SetFlowLimit(MwsfdPly *ply);
void MWSFPLY_RecordFname(MwsfdPly *ply, const char *fname);
void MWSFCRE_SetSupplySj(MwsfdPly *ply);
int SFD_SetLnkStm(void *sfd);
int ADXF_GetFnameRangeEx(int patid, int fid, char *fname, void **dir, int *ofst, int *nsct);
char *ADXF_GetFnameFromPt(int patid);
int LSC_EntryFname(LscObj *lsc, const char *fname);
int LSC_EntryFileRange(LscObj *lsc, char *fname, void *dir, int ofst, int nsct);
void LSC_Start(LscObj *lsc);
void LSC_Stop(LscObj *lsc);
int LSC_GetStat(LscObj *lsc);
int LSC_GetNumStm(LscObj *lsc);
int LSC_GetStmId(LscObj *lsc, int no);
char *LSC_GetStmFname(LscObj *lsc, int id);
int LSC_GetStmStat(LscObj *lsc, int id);
int LSC_GetStmRdSct(LscObj *lsc, int id);
void LSC_SetFlowLimit(LscObj *lsc, int min);
int LSC_GetFlowLimit(LscObj *lsc);
void LSC_SetLpFlg(LscObj *lsc, int loop);

void mwPlyLinkStm(void *hn, int sw);

void mwPlyEntryFname(MwsfdPly *ply, const char *fname)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122633: mwPlyEntryFname: handle is invalid.");
        return;
    }
    if (fname == 0) {
        mwsfd_Error("E10915B: mwPlyEntryFname: fname is NULL.");
        return;
    }
    if (LSC_EntryFname(ply->lsc, fname) < 0) {
        ply->stat = 4;
        mwsfd_Error("E204021: mwPlyEntryFname: Can't entry file'%s'", fname);
        return;
    }
    ply->nEntry++;
}

void mwPlyStartSeamless(MwsfdPly *ply)
{
    SfdSj *sj;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122634: mwPlyStartSeamless: handle is invalid.");
        return;
    }
    mwPlyLinkStm(ply, 1);
    mwSfdStartSj(ply, ply->defSj);
    MWSFPLY_SetFlowLimit(ply);
    LSC_Start(ply->lsc);
    sj = ply->sj;
    if (sj != 0) {
        sj->vtbl->reset(sj);
    }
    MWSFCRE_SetSupplySj(ply);
}

void mwPlySetLpFlg(MwsfdPly *ply, int loop)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122641: mwPlySetLpFlg: handle is invalid.");
        return;
    }
    LSC_SetLpFlg(ply->lsc, loop);
}

void mwPlyStartFnameLp(MwsfdPly *ply, const char *fname)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122630: mwPlyStartFnameLp: handle is invalid.");
        return;
    }
    if (fname == 0) {
        mwsfd_Error("E10915A: mwPlyStartFnameLp: fname is NULL.");
        return;
    }
    MWSFPLY_RecordFname(ply, fname);
    LSC_Stop(ply->lsc);
    mwPlyEntryFname(ply, ply->fname);
    mwPlySetLpFlg(ply, 1);
    mwPlyStartSeamless(ply);
}

void mwPlyReleaseSeamless(MwsfdPly *ply);

void mwPlyReleaseLp(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122631: mwPlyReleaseLp: handle is invalid.");
        return;
    }
    mwPlySetLpFlg(ply, 0);
    mwPlyReleaseSeamless(ply);
}

void mwPlyReleaseSeamless(MwsfdPly *ply)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122635: mwPlyReleaseSeamless: handle is invalid.");
        return;
    }
    mwPlyLinkStm(ply, 0);
}

int mwPlyGetNumSlFiles(MwsfdPly *ply)
{
    return LSC_GetNumStm(ply->lsc);
}

void mwPlyEntryAfs(MwsfdPly *ply, int patid, int fid)
{
    void *dir;
    int ofst, nsct;
    LscObj *lsc;

    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122636: mwPlyEntryAfs: handle is invalid.");
        return;
    }
    lsc = ply->lsc;
    if (ADXF_GetFnameRangeEx(patid, fid, ply->fname, &dir, &ofst, &nsct) == 0)
        LSC_EntryFileRange(lsc, ADXF_GetFnameFromPt(patid), dir, ofst, nsct);
    else
        mwsfd_Error("E008311 mwPlyEntryAfs: can't entry pid=%d fid=%d", patid, fid);
}

void mwPlyStartAfsLp(MwsfdPly *ply, int patid, int fid)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122632: mwPlyStartAfsLp: handle is invalid.");
        return;
    }
    LSC_Stop(ply->lsc);
    mwPlyEntryAfs(ply, patid, fid);
    mwPlySetLpFlg(ply, 1);
    mwPlyStartSeamless(ply);
}

void mwPlyEntryFnameRange(MwsfdPly *ply, char *fname, int ofst, int nsct)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E407023: mwPlyEntryFnameRange: handle is invalid.");
        return;
    }
    LSC_EntryFileRange(ply->lsc, fname, 0, ofst, nsct);
}

void mwPlyStartFnameRangeLp(MwsfdPly *ply, char *fname, int ofst, int nsct)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E407024: mwPlyStartFnameRangeLp: handle is invalid.");
        return;
    }
    LSC_Stop(ply->lsc);
    mwPlyEntryFnameRange(ply, fname, ofst, nsct);
    mwPlySetLpFlg(ply, 1);
    mwPlyStartSeamless(ply);
}

int mwPlyGetSlStmId(MwsfdPly *ply, int no);
char *mwPlyGetSlStmFname(MwsfdPly *ply, int id);

char *mwPlyGetSlFname(MwsfdPly *ply, int no)
{
    if (MWSFD_IsEnableHndl(ply) == 0) {
        mwsfd_Error("E1122637: mwPlyGetSlFname: handle is invalid.");
        return 0;
    }
    if (no < mwPlyGetNumSlFiles(ply)) {
        if (no < 0) {
            mwsfd_Error("E10821B : Invalid value of stm_no : %d", no);
            return 0;
        }
        return mwPlyGetSlStmFname(ply, mwPlyGetSlStmId(ply, no));
    }
    return 0;
}

int mwPlyGetSlStat(MwsfdPly *ply)
{
    return LSC_GetStat(ply->lsc);
}

int mwPlyGetSlStmId(MwsfdPly *ply, int no)
{
    return LSC_GetStmId(ply->lsc, no);
}

char *mwPlyGetSlStmFname(MwsfdPly *ply, int id)
{
    return LSC_GetStmFname(ply->lsc, id);
}

int mwPlyGetSlStmStat(MwsfdPly *ply, int id)
{
    return LSC_GetStmStat(ply->lsc, id);
}

int mwPlyGetSlStmRdSct(MwsfdPly *ply, int id)
{
    return LSC_GetStmRdSct(ply->lsc, id);
}

/* LSC state 3 is its error state */
int mwsflsc_IsLscErr(LscObj *lsc)
{
    return LSC_GetStat(lsc) == 3;
}

void MWSFLSC_SetFlowLimit(MwsfdPly *ply, int min)
{
    LscObj *lsc = ply->lsc;

    if (lsc != 0) {
        LSC_SetFlowLimit(lsc, min);
    }
}

void mwPlyGetSlFlowLimit(MwsfdPly *ply, int *min)
{
    *min = LSC_GetFlowLimit(ply->lsc);
}

/* takes the handle untyped and types it after the check: typed from the start, GCC keeps the
 * switch byte in a register across the store of linkPrev */
void mwPlyLinkStm(void *hn, int sw)
{
    MwsfdPly *ply;
    void *sfd;

    if (MWSFD_IsEnableHndl(hn) == 0) {
        mwsfd_Error("E1122642: mwPlyLinkStm: handle is invalid.");
        return;
    }
    ply = hn;
    sfd = ply->sfd;
    if (ply->linkReq == 1 && sw == 0)
        ply->linkPrev = 1;
    if (ply->linkReq == 0 && sw == 1 && SFD_SetLnkStm(sfd) != 0)
        mwsfd_Error("E99072101 mwPlyLinkStm: can't link stream");
    ply->linkReq = sw;
}

/* plays a sector range by a name of the form "<first sector>.<sector count>" */
void mwPlyStartSctLp(MwsfdPly *ply, int sct, unsigned int size)
{
    char fname[20];

    sprintf(fname, "%08x.%08x", sct, (size + 2047) >> 11);
    mwPlyStartFnameLp(ply, fname);
    memset(fname, 0, sizeof(fname));
}
