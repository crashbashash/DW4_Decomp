#include "dw4/cri/adx_ps2.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxcrs.h"
#include "dw4/cri/adxerrs.h"
#include "dw4/cri/cri_adxf.h"
#include "dw4/cri/lsc.h"

void FUN_00263748(AdxtObj *adxt, const char *name) {
    ADXT_EntryFnameRange(adxt, name, 0, 0xFFFFF);
}

void ADXT_EntryFnameRange(AdxtObj *adxt, const char *name, int first, int last) {
    /* the file list is read before the null check (retail loads it in the branch delay slot) */
    LscObj *lsc = adxt->lsc;
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080848 ADXT_EntryFnameRange: parameter error");
        return;
    }
    if (LSC_EntryFileRange(lsc, name, 0, first, last) < 0) {
        ADXERR_CallErrFunc2("E4063001:Can't entry file ", name);
    }
}

void ADXT_EntryAfs(AdxtObj *adxt, int afs, int fid) {
    LscObj *lsc = adxt->lsc;
    char text[16];
    void *dir;
    int ofst;
    int nsct;
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080855 ADXT_EntryAfs: parameter error");
        return;
    }
    if (ADXF_GetFnameRangeEx(afs, fid, adxt->fnbuf, &dir, &ofst, &nsct) == 0) {
        LSC_EntryFileRange(lsc, ADXF_GetFnameFromPt(afs), dir, ofst, nsct);
    } else {
        ADXERR_ItoA2(afs, fid, text, sizeof(text));
        ADXERR_CallErrFunc2("E0071301 ADXT_EntryAfs: can't entry ", text);
    }
}

void ADXT_StartSeamless(AdxtObj *adxt) {
    LscObj *lsc = adxt->lsc;
    SfdSj *sji;
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080850 ADXT_StartSeamless: parameter error");
        return;
    }
    ADXT_StopWithoutLsc(adxt);
    ADXCRS_Lock();
    adxt_start_sj(adxt, adxt->sjf);
    sji = adxt->sji;
    sji->vtbl->reset(sji);
    adxt->pmode = ADXT_PMODE_SLFILE;
    LSC_SetFlowLimit(lsc, adxt->minsct << 11);
    ADXCRS_Unlock();
    LSC_Start(lsc);
    ADXT_SetLnkSw(adxt, 1);
}

void ADXT_SetSeamlessLp(AdxtObj *adxt, int enable) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080851 ADXT_SetSeamlessLp: parameter error");
        return;
    }
    LSC_SetLpFlg(adxt->lsc, enable);
}


void ADXT_EntryFname(AdxtObj *adxt, const char *name)
{
    ADXT_StartFnameLp(adxt, name, 0, 0xfffff);
}

void ADXT_StartFnameLp(AdxtObj *adxt, const char *name, int first, int last) {
    LscObj *lsc;
    if (adxt == 0 || name == 0) {
        ADXERR_CallErrFunc1("E02080852 ADXT_StartFnameRangeLp: parameter error");
        return;
    }
    lsc = adxt->lsc;
    LSC_Stop(lsc);
    ADXT_EntryFnameRange(adxt, name, first, last);
    LSC_SetLpFlg(lsc, 1);
    ADXT_StartSeamless(adxt);
}

void ADXT_StartAfsLp(AdxtObj *adxt, int afs, unsigned int fid) {
    LscObj *lsc;
    if (adxt == 0 || afs >= 1 || fid > 0x10000) {
        ADXERR_CallErrFunc1("E0405100 ADXT_StartAfsLp: parameter error");
        return;
    }
    lsc = adxt->lsc;
    LSC_Stop(lsc);
    ADXT_EntryAfs(adxt, afs, fid);
    LSC_SetLpFlg(lsc, 1);
    ADXT_StartSeamless(adxt);
}

void ADXT_ReleaseSeamless(void)
{
}

int ADXT_GetNumFiles(AdxtObj *adxt) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080854 ADXT_GetNumFiles: parameter error");
        return -1;
    }
    return LSC_GetNumStm(adxt->lsc);
}

void ADXT_ResetEntry(AdxtObj *adxt) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1("E02080849 ADXT_ResetEntry: parameter error");
        return;
    }
    /* matching construct: manual — early return (not an if block) lets ee-gcc emit the tail call */
    if (adxt->stat != 0) {
        return;
    }
    LSC_ResetEntry(adxt->lsc);
}
