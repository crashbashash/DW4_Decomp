/* Hooks of the MPEG-2 video decoder that mpv_InstallHooks (mpvinst.c) points at the M2V entry points:
 * mpvhook_installed says whether they are installed, and each mpvhook_fn_ pointer holds the M2V entry
 * point of its name. Each wrapper calls its hook when one is set. */
#include "dw4/cri/mpv.h"
#include "dw4/cri/mpvhook.h"

int mpvhook_IsInstalled(void) {
    return mpvhook_installed;
}

char *mpvhook_GetVersionStr(void) {
    if (mpvhook_fn_GetVersionStr != 0) {
        return mpvhook_fn_GetVersionStr();
    }
    return 0;
}

int mpvhook_IsConformable(char *buf, int size) {
    if (mpvhook_fn_IsConformable != 0) {
        return mpvhook_fn_IsConformable(buf, size);
    }
    return 0;
}

void mpvhook_Init(int nobj, char *work, unsigned int size) {
    if (mpvhook_fn_Init != 0) {
        mpvhook_fn_Init(nobj, work, size);
    }
}

void mpvhook_Finish(void) {
    if (mpvhook_fn_Finish != 0) {
        mpvhook_fn_Finish();
    }
}

M2vObj *mpvhook_Create(void) {
    if (mpvhook_fn_Create != 0) {
        return mpvhook_fn_Create();
    }
    return 0;
}

void mpvhook_Destroy(M2vObj *lower) {
    if (mpvhook_fn_Destroy != 0) {
        mpvhook_fn_Destroy(lower);
    }
}

void mpvhook_MbCbFn(void) {
    if (mpvhook_fn_MbCbFn != 0) {
        mpvhook_fn_MbCbFn();
    }
}

void mpvhook_SetCond(M2vObj *lower, int no, M2vCondFn fn) {
    if (mpvhook_fn_SetCond != 0) {
        mpvhook_fn_SetCond(lower, no, fn);
    }
}

void mpvhook_SetErrFunc(M2vObj *lower, int (*func)(void *obj), void *obj) {
    if (mpvhook_fn_SetErrFunc != 0) {
        mpvhook_fn_SetErrFunc(lower, func, obj);
    }
}

void mpvhook_GetErrInf(M2vObj *lower, M2vErrInf *inf) {
    if (mpvhook_fn_GetErrInf != 0) {
        mpvhook_fn_GetErrInf(lower, inf);
    }
}

void mpvhook_DecodeFrm(void) {
    if (mpvhook_fn_DecodeFrm != 0) {
        mpvhook_fn_DecodeFrm();
    }
}

void mpvhook_SkipFrm(M2vObj *lower, SfdSj *sj) {
    if (mpvhook_fn_SkipFrm != 0) {
        mpvhook_fn_SkipFrm(lower, sj);
    }
}

void mpvhook_SetUsrSj(M2vObj *lower, int index, SfdSj *sj, M2vUsrDatFn fn, void *obj) {
    if (mpvhook_fn_SetUsrSj != 0) {
        mpvhook_fn_SetUsrSj(lower, index, sj, fn, obj);
    }
}

void mpvhook_SetPicUsrBuf(M2vObj *lower, char *buf, int size) {
    if (mpvhook_fn_SetPicUsrBuf != 0) {
        mpvhook_fn_SetPicUsrBuf(lower, buf, size);
    }
}

void mpvhook_GetPicUsr(M2vObj *lower, char **buf, int *len) {
    if (mpvhook_fn_GetPicUsr != 0) {
        mpvhook_fn_GetPicUsr(lower, buf, len);
    }
}

int mpvhook_DecodePicAtr(M2vObj *lower, SfdSj *sj) {
    if (mpvhook_fn_DecodePicAtr != 0) {
        return mpvhook_fn_DecodePicAtr(lower, sj);
    }
    return 0;
}

void mpvhook_GetPicAtr(M2vObj *lower, M2vPicAtr *picatr) {
    if (mpvhook_fn_GetPicAtr != 0) {
        mpvhook_fn_GetPicAtr(lower, picatr);
    }
}

void mpvhook_GetBitRate(M2vObj *lower, int *bit_rate) {
    if (mpvhook_fn_GetBitRate != 0) {
        mpvhook_fn_GetBitRate(lower, bit_rate);
    }
}

void mpvhook_GetVbvBufSiz(M2vObj *lower, int *vbv_size, int *vbv_delay, int *reserved) {
    if (mpvhook_fn_GetVbvBufSiz != 0) {
        mpvhook_fn_GetVbvBufSiz(lower, vbv_size, vbv_delay, reserved);
    }
}

void mpvhook_GetLinkFlg(M2vObj *lower, int *closed_gop, int *broken_link) {
    if (mpvhook_fn_GetLinkFlg != 0) {
        mpvhook_fn_GetLinkFlg(lower, closed_gop, broken_link);
    }
}
