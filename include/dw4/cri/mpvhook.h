/* CRI MPV hooks: the table mpv_InstallHooks (mpvinst.c) fills with the M2V entry points and the mpvhook_
 * wrappers (mpvhook.c) call through. Kept out of mpv.h: declaring these pointer types in every MPV and SFD
 * file changes how sfmpv.c schedules sfmpv_SetStartTtu. */
#ifndef DW4_CRI_MPVHOOK_H
#define DW4_CRI_MPVHOOK_H

extern int mpvhook_installed;
extern int (*mpvhook_fn_GetVersionStr)(void);
extern int (*mpvhook_fn_IsConformable)(char *buf, int size);
extern int (*mpvhook_fn_Init)();
extern int (*mpvhook_fn_Finish)();
extern int (*mpvhook_fn_Create)(void);
extern int (*mpvhook_fn_Destroy)();
extern int (*mpvhook_fn_SetCond)();
extern int (*mpvhook_fn_MbCbFn)();
extern int (*mpvhook_fn_SetErrFunc)();
extern int (*mpvhook_fn_GetErrInf)();
extern int (*mpvhook_fn_DecodeFrm)();
extern int (*mpvhook_fn_SkipFrm)();
extern int (*mpvhook_fn_SetUsrSj)();
extern int (*mpvhook_fn_SetPicUsrBuf)();
extern int (*mpvhook_fn_GetPicUsr)();
extern int (*mpvhook_fn_DecodePicAtr)();
extern int (*mpvhook_fn_GetPicAtr)();
extern int (*mpvhook_fn_GetBitRate)();
extern int (*mpvhook_fn_GetVbvBufSiz)();
extern int (*mpvhook_fn_GetLinkFlg)();

#endif
