/* The MPS library: its handles, initialisation, header queries and error reporting. */
#include "dw4/cri/mps.h"

extern char cri_mps_version[];          /* "\nCRI MPS/PS2EE Ver.1.924 Build:..." */
extern MpsHn *mps_curhn;
extern MpsWork *mps_work;

/* matching construct: hand search — returns the validation result on the success path (keeps it live in v0,
   so the copy uses v1/a0); the error path returns no value, as in the implicit-int original */
int MPS_GetPackHd(MpsHn *mps, MpsPackHd *out) {
    int result;

    result = mps_CheckHn(mps);
    if (result != 0) {
        mps_ReportError(0, 0xFF020201);
        return;
    }
    *out = mps->pack;
    return result;
}

int MPS_GetSysHdOfKind(MpsHn *mps, MpsSysHd *out, int kind) {
    int result = mps_CheckHn(mps);

    if (result != 0) {
        return mps_ReportError(0, 0xFF020202);
    }
    *out = mps->sysHdKind[kind];
    return result;
}

int MPS_GetSysHd(MpsHn *mps, MpsSysHd *out) {
    int result = mps_CheckHn(mps);

    if (result != 0) {
        return mps_ReportError(0, 0xFF020202);
    }
    *out = mps->sysHd;
    return result;
}

/* matching construct: hand search — as MPS_GetPackHd */
int MPS_GetPesInf(MpsHn *mps, MpsPesInf *out) {
    int result;

    result = mps_CheckHn(mps);
    if (result != 0) {
        mps_ReportError(0, 0xFF020203);
        return;
    }
    *out = mps->pes;
    return result;
}

char *MPS_GetVersionStr(void) {
    return cri_mps_version;
}

int mps_InitWork(int nhn, MpsWork *work);

void mps_InitLibErr(MpsErr *err);
int MPS_Destroy(MpsHn *mps);

int mps_InitWork(int nhn, MpsWork *work) {
    MpsHn *hn;
    int i;

    mps_work = work;
    mpsutl_FillWords((int *)work, 0, nhn * 64 + 4);
    mps_InitLibErr(&mps_work->err);
    mps_work->nhn = nhn;
    hn = mps_work->hn;
    if (nhn > 0) {
        i = nhn;
        do {
            hn->stat = MPS_HN_FREE;
            hn++;
        } while (--i != 0);
    }
    return 0;
}

void MPS_Finish(void) {
    MpsWork *work = mps_work;
    MpsHn *hn = work->hn;
    int nhn = work->nhn;
    int i;

    for (i = 0; i < nhn; i++) {
        MpsHn *mps = &hn[i];
        if (mps->stat != MPS_HN_FREE)
            MPS_Destroy(mps);
    }
    mpsutl_Finish();
    mpsdmx_Finish();
}

void mps_ClearErr(MpsErr *err);

void mps_InitLibErr(MpsErr *err) {
    mps_ClearErr(err);
}

void mps_ClearErr(MpsErr *err) {
    err->fn = 0;
    err->obj = 0;
    err->code = 0;
}

int mps_CallErrFn(MpsErr *err, int code);

int mps_ReportError(MpsHn *mps, int code) {
    if (mps == 0) {
        mps_CallErrFn(&mps_work->err, code);
    } else {
        mps_CallErrFn(&mps->err, code);
    }
    return code;
}

/* Records code and, when it is an error, calls the error callback; returns the callback's result. */
int mps_CallErrFn(MpsErr *err, int code) {
    err->code = code;
    if (code != 0) {
        code = (int)err->fn;
        if (code != 0) {
            code = err->fn(err->obj);
        }
    }
    return code;
}

void mps_SetErrFn(MpsErr *err, MpsErrFn fn, void *obj);

/* Sets the error callback of a handle, or the library's for a null handle. */
int MPS_EntryErrFunc(MpsHn *mps, MpsErrFn fn, void *obj) {
    if (mps == 0) {
        mps_SetErrFn(&mps_work->err, fn, obj);
    } else {
        if (mps_CheckHn(mps) != 0) {
            return mps_ReportError(0, 0xFF020101);
        }
        mps_SetErrFn(&mps->err, fn, obj);
    }
    return 0;
}

void mps_SetErrFn(MpsErr *err, MpsErrFn fn, void *obj) {
    err->fn = fn;
    err->obj = obj;
}

int MPS_GetErrInf(MpsHn *mps, MpsErr *out) {
    if (mps == 0) {
        *out = mps_work->err;
    } else {
        if (mps_CheckHn(mps) != 0) {
            return mps_ReportError(0, 0xFF020102);
        }
        *out = mps->err;
    }
    return 0;
}

/* Makes mps the current handle; -1 for a null or free handle. */
int mps_CheckHn(MpsHn *mps) {
    mps_curhn = mps;
    if (mps == 0) {
        return -1;
    }
    return mps->stat != MPS_HN_FREE ? 0 : -1;
}

MpsHn *mps_AllocHn(void);
MpsHn *mps_InitHn(MpsHn *mps);

MpsHn *MPS_Create(void) {
    MpsHn *mps = mps_AllocHn();

    if (mps != 0) {
        return mps_InitHn(mps);
    }
    return 0;
}

MpsHn *mps_AllocHn(void) {
    int nhn = mps_work->nhn;
    MpsHn *hn = mps_work->hn;
    int i;

    for (i = 0; i < nhn; i++) {
        if (hn[i].stat == MPS_HN_FREE) {
            return &hn[i];
        }
    }
    return 0;
}

void mps_ResetPackHd(MpsPackHd *pack);
void mps_ResetSysHd(MpsSysHd *sysHd);
void mps_ResetPesInf(MpsPesInf *pes);

MpsHn *mps_InitHn(MpsHn *mps) {
    mpsutl_FillWords((int *)mps, 0, 64);
    mps->stat = MPS_HN_USED;
    mps_ClearErr(&mps->err);
    mps->pesSw = 2;
    mps_ResetPackHd(&mps->pack);
    mps_ResetSysHd(&mps->sysHd);
    mps_ResetSysHd(&mps->sysHdKind[0]);
    mps_ResetSysHd(&mps->sysHdKind[1]);
    mps_ResetSysHd(&mps->sysHdKind[2]);
    mps_ResetPesInf(&mps->pes);
    mps->f208 = 0;
    mps->f216 = 0;
    mps->f220 = 0;
    mps->decode = mpsdmx_Decode;
    mps->f224 = 0;
    mps->sysHdFn = 0;
    mps->sysHdObj = 0;
    return mps;
}

void mps_ResetPackHd(MpsPackHd *pack) {
    pack->scr = -1;
    pack->scrExt = -1;
    pack->muxRate = -1;
}

void mps_ResetSysHd(MpsSysHd *sysHd) {
    sysHd->f0 = -1;
    sysHd->f4 = -1;
    sysHd->audioBound = -1;
    sysHd->videoBound = -1;
    sysHd->f16 = -1;
    sysHd->f20 = -1;
    sysHd->f24 = -1;
    sysHd->f28 = -1;
}

void mps_ResetPesInf(MpsPesInf *pes) {
    pes->pts = -1;
    pes->dts = -1;
    pes->streamId = -1;
    pes->f20 = -1;
    pes->f24 = -1;
    pes->f28 = -1;
    pes->f32 = -1;
    pes->f36 = -1;
}

int MPS_Destroy(MpsHn *mps) {
    if (mps_CheckHn(mps) != 0) {
        return mps_ReportError(0, 0xFF020103);
    }
    mps->stat = MPS_HN_FREE;
    return 0;
}
