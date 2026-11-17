/* Hooks of the MPEG-2 video decoder that mpv_InstallHooks (mpvinst.c) points at the M2V entry points:
 * mpvhook_installed says whether they are installed, and each mpvhook_fn_ pointer holds the M2V entry
 * point of its name. Each wrapper calls its hook when one is set. */
#include "dw4/cri/mpv.h"
#include "dw4/cri/mpvhook.h"

int mpvhook_IsInstalled(void) {
    return mpvhook_installed;
}

int mpvhook_GetVersionStr(void) {
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

void mpvhook_Init(int nobj, void *work, int size) {
    if (mpvhook_fn_Init != 0) {
        mpvhook_fn_Init(nobj, work, size);
    }
}

void mpvhook_Finish(void) {
    if (mpvhook_fn_Finish != 0) {
        mpvhook_fn_Finish();
    }
}

int mpvhook_Create(void) {
    if (mpvhook_fn_Create != 0) {
        return mpvhook_fn_Create();
    }
    return 0;
}

void mpvhook_Destroy(int lower) {
    if (mpvhook_fn_Destroy != 0) {
        mpvhook_fn_Destroy(lower);
    }
}

void mpvhook_MbCbFn(void) {
    if (mpvhook_fn_MbCbFn != 0) {
        mpvhook_fn_MbCbFn();
    }
}

void mpvhook_SetCond(int lower, int no, int value) {
    if (mpvhook_fn_SetCond != 0) {
        mpvhook_fn_SetCond(lower, no, value);
    }
}

void mpvhook_SetErrFunc(void) {
    if (mpvhook_fn_SetErrFunc != 0) {
        mpvhook_fn_SetErrFunc();
    }
}

void mpvhook_GetErrInf(void) {
    if (mpvhook_fn_GetErrInf != 0) {
        mpvhook_fn_GetErrInf();
    }
}

void mpvhook_DecodeFrm(void) {
    if (mpvhook_fn_DecodeFrm != 0) {
        mpvhook_fn_DecodeFrm();
    }
}

void mpvhook_SkipFrm(void) {
    if (mpvhook_fn_SkipFrm != 0) {
        mpvhook_fn_SkipFrm();
    }
}

void mpvhook_SetUsrSj(int lower, int index, SfdSj *sj, MpvUsrDatFn fn, void *obj) {
    if (mpvhook_fn_SetUsrSj != 0) {
        mpvhook_fn_SetUsrSj(lower, index, sj, fn, obj);
    }
}

void mpvhook_SetPicUsrBuf(int lower, char *buf, int size) {
    if (mpvhook_fn_SetPicUsrBuf != 0) {
        mpvhook_fn_SetPicUsrBuf(lower, buf, size);
    }
}

void mpvhook_GetPicUsr(int lower, int index, int *flag) {
    if (mpvhook_fn_GetPicUsr != 0) {
        mpvhook_fn_GetPicUsr(lower, index, flag);
    }
}

int mpvhook_DecodePicAtr(int lower, SfdSj *sj) {
    if (mpvhook_fn_DecodePicAtr != 0) {
        return mpvhook_fn_DecodePicAtr(lower, sj);
    }
    return 0;
}

void mpvhook_GetPicAtr(int lower, MpvPicInf *inf) {
    if (mpvhook_fn_GetPicAtr != 0) {
        mpvhook_fn_GetPicAtr(lower, inf);
    }
}

void mpvhook_GetBitRate(int lower, int *inf) {
    if (mpvhook_fn_GetBitRate != 0) {
        mpvhook_fn_GetBitRate(lower, inf);
    }
}

void mpvhook_GetVbvBufSiz(int lower, int *a, int *b, int *c) {
    if (mpvhook_fn_GetVbvBufSiz != 0) {
        mpvhook_fn_GetVbvBufSiz(lower, a, b, c);
    }
}

void mpvhook_GetLinkFlg(int lower, int *width, int *height) {
    if (mpvhook_fn_GetLinkFlg != 0) {
        mpvhook_fn_GetLinkFlg(lower, width, height);
    }
}
