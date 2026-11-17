/* CRI ADX on PS2: the ADXM threads that run the CRI servers, the ADXPS2 calls around them, and the setup
 * of the cvFs devices ADX reads through (disc, host, memory); src/cri/adxps2.c, adxdvd.c, adxhst.c and
 * adxmfs.c. */
#ifndef DW4_CRI_ADX_PS2_H
#define DW4_CRI_ADX_PS2_H

#include "dw4/cri/svm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Disc file system: the root folder and the sceCd read mode. */
typedef struct AdxDvdFsPrm {
    const char *rootdir;
    int rdmode;
    int trycount;
    int spindlctrl;
    int datapattern;
} AdxDvdFsPrm;

/* Host file system: the root folder, the IOP open mode and the SRD host switches. */
typedef struct AdxHstFsPrm {
    const char *rootdir;
    int openmode;
    int host64;         /* nonzero: the 64-bit host file system */
    int hostlock;       /* nonzero: SRD holds its lock across host reads */
} AdxHstFsPrm;

/* A file list loaded in advance, so opening a listed file needs no search. */
typedef struct AdxFcachePrm {
    const char *flist;
    int fnamelen;       /* longest file name in the list */
    void *buf;
    int bufsize;
} AdxFcachePrm;

/* Thread priorities and the two user-thread stacks, as ADXM_SetupThrdEx takes them. */
typedef struct AdxmThreadPrmEx {
    int lockPrio;
    int safePrio;
    int usrVsyncPrio;
    int vsyncPrio;
    int fsPrio;
    int mainPrio;
    int mwIdlePrio;
    int usrIdlePrio;
    void *usrVsyncStack;
    int usrVsyncStackSize;
    void *usrIdleStack;
    int usrIdleStackSize;
} AdxmThreadPrmEx;

/* The priorities ADXM_SetupThrd takes. */
typedef struct AdxmThreadPrm {
    int lockPrio;
    int safePrio;
    int vsyncPrio;
    int fsPrio;
    int mainPrio;
    int mwIdlePrio;
} AdxmThreadPrm;

/* The priorities ADXPS2_SetupThrd takes; the FS and MW-idle ones are derived from them. */
typedef struct Adxps2ThreadPrm {
    int lockPrio;
    int safePrio;
    int vsyncPrio;
    int mainPrio;
} Adxps2ThreadPrm;

/* nonzero: ADX streams read with the SRD read mode */
extern int adxt_srd_rmode_sw;
/* end-of-stream margin handed to each ADXT stream */
extern int adxt_stm_eos;

/* adxps2.c */
int ADXM_ExecSvrAll(void);
int ADXM_IsSetupThrd(void);
void ADXM_SetCbErr(SvmErrFunc func, void *obj);
void ADXM_SetupThrd(AdxmThreadPrm *tprm);
void ADXM_ShutdownThrd(void);
void ADXM_Lock(void);
void ADXM_Unlock(void);
int ADXM_GetLockLevel(void);
int ADXPS2_ExecVint(int arg);
int ADXM_ExecVint(int arg);
void ADXM_ExecMain(void);
void ADXPS2_ResumeIdleThrd(void);
void ADXPS2_WakeupMainThrd(void);
void ADXPS2_SleepMainThrd(void);
void ADXM_ExecVsyncFrame(void);
void ADXPS2_WaitVsync(void);
int ADXPS2_ExecServerEx(void);
void ADXPS2_SetupThrd(Adxps2ThreadPrm *prm);
void ADXPS2_ShutdownThrd(void);
void ADXPS2_ExecServerLocked(void);
void ADXPS2_Lock(void);
void ADXPS2_Unlock(void);
void ADXM_SetupThrdEx(AdxmThreadPrmEx *tprm);
void ADXM_ShutdownThrdEx(void);
void ADXM_SetCbUsrVsync(SvmSvrFunc func, void *obj);
void ADXM_SetCbUsrIdle(SvmSvrFunc func, void *obj);
void ADXM_GotoUsrIdleBdr(void);

/* adxdvd.c */
void ADXPS2_SetupDvdFs(AdxDvdFsPrm *prm);
int ADXPS2_LoadFcacheDvd(AdxFcachePrm *prm);
int ADXPS2_LoadFcacheDvdMem(AdxFcachePrm *prm, char *list, int listlen);
void ADXPS2_SetRdModeDvd(AdxDvdFsPrm *prm);
int ADXPS2_IsExistFileDvd(const char *fname);
void ADXPS2_SetDvdLayer(unsigned int layer);
int ADXPS2_GetDvdLayer(void);
int ADXPS2_SeekDvd(int lsn);
void ADXT_SetSrdRmodeSw(int sw);
int ADXT_GetSrdRmodeSw(void);

/* adxhst.c */
void ADXPS2_SetupHostFs(AdxHstFsPrm *prm);
int ADXPS2_LoadFcacheHost(AdxFcachePrm *prm);
int ADXPS2_IsExistFcacheHost(const char *fname);
void ADXPS2_SetRdModeHost(AdxHstFsPrm *prm);

/* adxmfs.c */
void ADXPS2_SetupMemFs(void *prm);
int ADXT_GetStmEos(void);
void ADXT_SetStmEos(int eos);

#ifdef __cplusplus
}
#endif

#endif
