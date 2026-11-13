/* The MWSFD work area: the library's settings, the server hooks and the 8 player handles. */
#ifndef DW4_CRI_MWSFD_H
#define DW4_CRI_MWSFD_H

#include "dw4/cri/mwply.h"

#define MWSFD_NPLY 8

/* the init parameters of mwPlyInitSfdFx */
typedef struct MwsfdInitPrm {
    float vhz;          /* 0 */
    int dispCycle;      /* 4 */
    int dispLatency;    /* 8 */
    void *decSvr;       /* 12: the decode server; 1 runs it in a thread (typed apart from the ints: mwsflib_InitLibWork matches only so) */
} MwsfdInitPrm;

typedef struct MwsfdWork {
    int f0;
    MwsfdInitPrm prm;              /* 4 */
    char pad20[16];
    int waitingSvr;                /* 36 */
    void *(*mallocFn)(void *obj, int size);  /* 40: MWSFD_SetMallocFunc */
    void (*freeFn)(void *obj, void *ptr);    /* 44 */
    void *mallocObj;                         /* 48 */
    int workFlag;                  /* 52 */
    int picUsrEnable;              /* 56: picture user data is handled */
    int waitSvrOnStart;            /* 60 */
    void (*preSvrFn)(void *obj);   /* 64: called before the server's player loop */
    void *preSvrObj;               /* 68 */
    void (*postSvrFn)(void *obj);  /* 72: called after it */
    void *postSvrObj;              /* 76 */
    void (*idleFn)(void *obj);     /* 80: called when no player is pending */
    void *idleObj;                 /* 84 */
    int svrLock;                   /* 88 */
    int execLock;                  /* 92 */
    char pad96[8];
    int errCode;                   /* 104: the last error code, MWSFLIB_SetErrCode */
    MwsfdPly ply[MWSFD_NPLY];      /* 108 */
} MwsfdWork;

MwsfdWork *MWSFLIB_GetLibWorkPtr(void);

#endif
