/* The MPS library: its handles, initialisation, header queries and error reporting. */
#include "dw4/cri/mps.h"

extern char cri_mps_version[];          /* "\nCRI MPS/PS2EE Ver.1.924 Build:..." */
extern MpsHn *mps_curhn;
extern unsigned char mps_endian_mark[4];
extern char *volatile mps_version_ptr;
extern MpsWork *mps_work;

/* matching construct: hand search — returns the validation result on the success path (keeps it live in v0,
   so the copy uses v1/a0); the error path returns no value, as in the implicit-int original */
int MPS_GetPackHd(MpsHn *mps, MpsPackHd *out) {
    int result;

    result = MPSLIB_CheckHn(mps);
    if (result != 0) {
        MPSLIB_SetErr(0, 0xFF020201);
        return;
    }
    *out = mps->pack;
    return result;
}

int MPS_GetSysHdOfKind(MpsHn *mps, MpsSysHd *out, int kind) {
    int result = MPSLIB_CheckHn(mps);

    if (result != 0) {
        return MPSLIB_SetErr(0, 0xFF020202);
    }
    *out = mps->sysHdKind[kind];
    return result;
}

int MPS_GetSysHd(MpsHn *mps, MpsSysHd *out) {
    int result = MPSLIB_CheckHn(mps);

    if (result != 0) {
        return MPSLIB_SetErr(0, 0xFF020202);
    }
    *out = mps->sysHd;
    return result;
}

/* matching construct: hand search — as MPS_GetPackHd */
int MPS_GetPesInf(MpsHn *mps, MpsPesInf *out) {
    int result;

    result = MPSLIB_CheckHn(mps);
    if (result != 0) {
        MPSLIB_SetErr(0, 0xFF020203);
        return;
    }
    *out = mps->pes;
    return result;
}

char *MPS_GetVersionStr(void) {
    return cri_mps_version;
}

int MPS_Init(int nhn, MpsWork *work) {
    int result;

    mps_version_ptr = cri_mps_version;
    if (mps_endian_mark[0] != 4) {
        for (;;) {
            ((void (*)(void))-1)();
        }
    }
    result = mpslib_InitLibWork(nhn, work);
    if (result != 0) {
        return result;
    }
    mpsutl_Init();
    mpsdmx_Init();
    return 0;
}

int mpslib_InitLibWork(int nhn, MpsWork *work);

void mpslib_InitErr(MpsErr *err);
int MPS_Destroy(MpsHn *mps);

int mpslib_InitLibWork(int nhn, MpsWork *work) {
    MpsHn *hn;
    int i;

    mps_work = work;
    UTY_MemsetDword((int *)work, 0, nhn * 64 + 4);
    mpslib_InitErr(&mps_work->err);
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

void MPSLIB_InitErrInf(MpsErr *err);

void mpslib_InitErr(MpsErr *err) {
    MPSLIB_InitErrInf(err);
}

void MPSLIB_InitErrInf(MpsErr *err) {
    err->fn = 0;
    err->obj = 0;
    err->code = 0;
}

int mpslib_SetErrSub(MpsErr *err, int code);

int MPSLIB_SetErr(MpsHn *mps, int code) {
    if (mps == 0) {
        mpslib_SetErrSub(&mps_work->err, code);
    } else {
        mpslib_SetErrSub(&mps->err, code);
    }
    return code;
}

/* Records code and, when it is an error, calls the error callback; returns the callback's result. */
int mpslib_SetErrSub(MpsErr *err, int code) {
    err->code = code;
    if (code != 0) {
        code = (int)err->fn;
        if (code != 0) {
            code = err->fn(err->obj);
        }
    }
    return code;
}

void mpslib_SetErrFnSub(MpsErr *err, MpsErrFn fn, void *obj);

/* Sets the error callback of a handle, or the library's for a null handle. */
int MPS_SetErrFn(MpsHn *mps, MpsErrFn fn, void *obj) {
    if (mps == 0) {
        mpslib_SetErrFnSub(&mps_work->err, fn, obj);
    } else {
        if (MPSLIB_CheckHn(mps) != 0) {
            return MPSLIB_SetErr(0, 0xFF020101);
        }
        mpslib_SetErrFnSub(&mps->err, fn, obj);
    }
    return 0;
}

void mpslib_SetErrFnSub(MpsErr *err, MpsErrFn fn, void *obj) {
    err->fn = fn;
    err->obj = obj;
}

int MPS_GetErrInf(MpsHn *mps, MpsErr *out) {
    if (mps == 0) {
        *out = mps_work->err;
    } else {
        if (MPSLIB_CheckHn(mps) != 0) {
            return MPSLIB_SetErr(0, 0xFF020102);
        }
        *out = mps->err;
    }
    return 0;
}

/* Makes mps the current handle; -1 for a null or free handle. */
int MPSLIB_CheckHn(MpsHn *mps) {
    mps_curhn = mps;
    if (mps == 0) {
        return -1;
    }
    return mps->stat != MPS_HN_FREE ? 0 : -1;
}

MpsHn *mpslib_SearchFreeHn(void);
MpsHn *mpslib_InitHn(MpsHn *mps);

MpsHn *MPS_Create(void) {
    MpsHn *mps = mpslib_SearchFreeHn();

    if (mps != 0) {
        return mpslib_InitHn(mps);
    }
    return 0;
}

MpsHn *mpslib_SearchFreeHn(void) {
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
void mpslib_InitSys(MpsSysHd *sysHd);
void mps_ResetPesInf(MpsPesInf *pes);

MpsHn *mpslib_InitHn(MpsHn *mps) {
    UTY_MemsetDword((int *)mps, 0, 64);
    mps->stat = MPS_HN_USED;
    MPSLIB_InitErrInf(&mps->err);
    mps->pesSw = 2;
    mps_ResetPackHd(&mps->pack);
    mpslib_InitSys(&mps->sysHd);
    mpslib_InitSys(&mps->sysHdKind[0]);
    mpslib_InitSys(&mps->sysHdKind[1]);
    mpslib_InitSys(&mps->sysHdKind[2]);
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
    pack->isMpeg1 = -1;
    pack->muxRate = -1;
}

void mpslib_InitSys(MpsSysHd *sysHd) {
    sysHd->headerLength = -1;
    sysHd->rateBound = -1;
    sysHd->audioBound = -1;
    sysHd->videoBound = -1;
    sysHd->fixedFlag = -1;
    sysHd->cspsFlag = -1;
    sysHd->audioLockFlag = -1;
    sysHd->videoLockFlag = -1;
}

void mps_ResetPesInf(MpsPesInf *pes) {
    pes->pts = -1;
    pes->dts = -1;
    pes->streamId = -1;
    pes->streamKind = -1;
    pes->streamNo = -1;
    pes->packetLength = -1;
    pes->stdBufferSize = -1;
    pes->dataSize = -1;
}

int MPS_Destroy(MpsHn *mps) {
    if (MPSLIB_CheckHn(mps) != 0) {
        return MPSLIB_SetErr(0, 0xFF020103);
    }
    mps->stat = MPS_HN_FREE;
    return 0;
}
