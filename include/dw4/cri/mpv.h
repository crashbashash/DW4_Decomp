/* The CRI MPV (M2V) decoder library's handle pool and work area (src/cri/mpv.c). */
#ifndef DW4_CRI_MPV_H
#define DW4_CRI_MPV_H

#include "dw4/cri/sfdsj.h"

#define MPV_COND_MAX 16
#define MPV_COND_CBFN 8   /* the condition holding the decoder's callback */
#define MPV_HN_FREE 1
#define MPV_HN_USED 2
#define MPV_HN_SIZE 1016  /* the part of a pool entry a handle uses */
#define MPV_POOL_SIZE 7136

/* the picture information reset by mpv_ResetPicInf and filled from the lower layer by mpv_GetLowerInf */
typedef struct MpvPicInf {
    int f0, f4, f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48, f52;
    int f56;    /* 3 after a reset */
    int f60;    /* 1 after a reset */
    int f64;    /* 1 after a reset */
    int f68;    /* 1 after a reset */
    int f72, f76;
    short f80, f82;
    signed char f84, f85, f86, f87, f88, f89, f90, f91, f92, f93;
    signed char f94, f95, f96, f97, f98, f99, f100;
    char pad101[128 - 101];
} MpvPicInf;

/* one of the four reference-buffer entries the lower layer gets */
typedef struct MpvBufEnt {
    int addr;
    int f4;
    int f8;
} MpvBufEnt;

/* the sequence header values of a handle */
typedef struct MpvSeqInf {
    char pad0[24];
    int width;   /* 24 */
    int height;  /* 28 */
} MpvSeqInf;

/* the size the lower layer decodes at, with its flag */
typedef struct MpvLowSize {
    int width;
    int height;
    int flag;
} MpvLowSize;

/* the error object a handle reports through: code is stored, then fn(arg) is called */
typedef struct MpvErrObj {
    int (*fn)(void *arg);
    void *arg;
    int code;
    int skipReqCnt;   /* 12: skip requests */
    int skipPicCnt;   /* 16: skips made while condition 1 was set */
} MpvErrObj;

/* one entry of the handle pool; entries are 1024 bytes apart */
typedef struct MpvHn {
    char pad0[44];
    char *mbBuf;              /* 44: pool + 4384 */
    char *blkBuf;             /* 48: pool + 4352 */
    char *dctBuf;             /* 52: pool + 4448 */
    char pad56[8];
    unsigned char *clampY;    /* 64: the saturation table centre */
    char pad68[52];
    MpvSeqInf seq;            /* 120 */
    char pad152[120];
    unsigned char *clampC;    /* 272 */
    char pad276[116];
    int stat;                 /* 392: MPV_HN_FREE or MPV_HN_USED */
    int f396;
    int cond[MPV_COND_MAX];   /* 400: conditions, copied from the library defaults */
    MpvPicInf picInf;         /* 464 */
    MpvErrObj err;            /* 592: reset by FUN_0028ea30 */
    char pad612[68];
    int lowInf0;              /* 680 */
    int lowInf1;              /* 684: in 2048-byte units */
    int f688;
    int lowInf3;              /* 692 */
    int lowInf4;              /* 696 */
    int lowInf2;              /* 700 */
    char pad704[152];
    int strmType;             /* 856: 0 unknown, 1 MPEG-1, 2 MPEG-2 */
    int f860, f864, f868;
    char pad872[24];
    int skipReq;              /* 896 */
    int skipCnt;              /* 900 */
    SfdSjChunk chunk;         /* 904: the chunk being decoded */
    char pad912[4];
    int idcPrec;              /* 916: 3 from the "IDCPREC" user data, else 0 */
    char pad920[12];
    int maxCount;             /* 932: from condition 7 */
    char pad936[8];
    int lower;                /* 944: the lower-layer decoder handle */
    char pad948[4];
    MpvBufEnt bufEnt[4];      /* 952 */
    MpvLowSize low;           /* 1000 */
    char pad1012[MPV_HN_SIZE - 1012];
    char pad1016[1024 - MPV_HN_SIZE];
} MpvHn;

/* the library work area */
typedef struct MpvLib {
    int cond[MPV_COND_MAX];   /* 0: default conditions for new handles */
    int optionFlag;           /* 64 */
    int initFlag;             /* 68 */
    char pad72[4];
    char *tables;             /* 76 */
    char *pool;               /* 80: MPV_POOL_SIZE bytes shared by the handles */
    int nhn;                  /* 84 */
    MpvHn *hn;                /* 88 */
} MpvLib;

/* the build constants MPV_Init checks the library against */
typedef struct MpvBuildInf {
    int magic;     /* 0x5a5a5a5a */
    int libSize;   /* sizeof(MpvLib) */
    int hnSize;    /* MPV_HN_SIZE */
    int poolSize;  /* MPV_POOL_SIZE */
} MpvBuildInf;

extern MpvErrObj mpv_err_global;  /* 0x4bccb8: the error object when no handle is given */

#endif
