/* CRI MPV hooks: the table mpv_InstallHooks (mpvinst.c) fills with the M2V entry points and the mpvhook_
 * wrappers (mpvhook.c) call through. Kept out of mpv.h: declaring these pointer types in every MPV and SFD
 * file changes how sfmpv.c schedules sfmpv_SetStartTtu. */
#ifndef DW4_CRI_MPVHOOK_H
#define DW4_CRI_MPVHOOK_H

#include "dw4/cri/m2v.h"

extern int mpvhook_installed;
extern char *(*mpvhook_fn_GetVersionStr)(void);
extern int (*mpvhook_fn_IsConformable)(char *buf, int size);
extern void (*mpvhook_fn_Init)(int nobj, char *work, unsigned int size);
extern void (*mpvhook_fn_Finish)(void);
extern M2vObj *(*mpvhook_fn_Create)(void);
extern void (*mpvhook_fn_Destroy)(M2vObj *hn);
extern void (*mpvhook_fn_SetCond)(M2vObj *hn, int no, M2vCondFn fn);
extern void (*mpvhook_fn_MbCbFn)(void);
extern void (*mpvhook_fn_SetErrFunc)(M2vObj *hn, int (*func)(void *obj), void *obj);
extern void (*mpvhook_fn_GetErrInf)(M2vObj *hn, M2vErrInf *inf);
extern void (*mpvhook_fn_DecodeFrm)(void);
extern void (*mpvhook_fn_SkipFrm)(M2vObj *hn, struct SfdSj *sj);
extern void (*mpvhook_fn_SetUsrSj)(M2vObj *hn, int no, struct SfdSj *sj, M2vUsrDatFn fn, void *obj);
extern void (*mpvhook_fn_SetPicUsrBuf)(M2vObj *hn, char *buf, int size);
extern void (*mpvhook_fn_GetPicUsr)(M2vObj *hn, char **buf, int *size);
extern int (*mpvhook_fn_DecodePicAtr)(M2vObj *hn, struct SfdSj *sj);
extern void (*mpvhook_fn_GetPicAtr)(M2vObj *hn, M2vPicAtr *picatr);
extern void (*mpvhook_fn_GetBitRate)(M2vObj *hn, int *bit_rate);
extern void (*mpvhook_fn_GetVbvBufSiz)(M2vObj *hn, int *vbv_size, int *vbv_delay, int *reserved);
extern void (*mpvhook_fn_GetLinkFlg)(M2vObj *hn, int *closed_gop, int *broken_link);

#endif
