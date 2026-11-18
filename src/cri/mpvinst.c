/* Points the MPEG-2 video decoder hooks (mpvhook.c) at the M2V entry points and marks them installed. */
#include "dw4/cri/m2v.h"
#include "dw4/cri/mpv.h"
#include "dw4/cri/mpvhook.h"
void mpv_InstallHooks(void) {
    mpvhook_fn_GetVersionStr = M2V_GetVersionStr;
    mpvhook_fn_IsDecodable = M2V_IsDecodable;
    mpvhook_fn_Init = M2V_Init;
    mpvhook_fn_Finish = M2V_Finish;
    mpvhook_fn_Create = M2V_Create;
    mpvhook_fn_Destroy = M2V_Destroy;
    mpvhook_fn_SetCond = M2V_SetCond;
    mpvhook_fn_MbCbFn = M2V_MbCbFn;
    mpvhook_fn_SetErrFunc = M2V_SetErrFunc;
    mpvhook_fn_GetErrInf = M2V_GetErrInf;
    mpvhook_fn_DecodeFrm = M2V_DecodeFrm;
    mpvhook_fn_SkipFrm = M2V_SkipFrm;
    mpvhook_fn_SetUsrSj = M2V_SetUsrSj;
    mpvhook_fn_SetPicUsrBuf = M2V_SetPicUsrBuf;
    mpvhook_fn_GetPicUsr = M2V_GetPicUsr;
    mpvhook_fn_DecodePicAtr = M2V_DecodePicAtr;
    mpvhook_fn_GetPicAtr = M2V_GetPicAtr;
    mpvhook_fn_GetBitRate = M2V_GetBitRate;
    mpvhook_fn_GetVbvBufSiz = M2V_GetVbvBufSiz;
    mpvhook_fn_GetLinkFlg = M2V_GetLinkFlg;
    mpvhook_installed = 1;
}
