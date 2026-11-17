/* The CRI MPV (M2V) decoder library's handle pool and work area (src/cri/mpv.c). */
#ifndef DW4_CRI_MPV_H
#define DW4_CRI_MPV_H

#include "dw4/cri/sj.h"

#define MPV_COND_MAX 16
#define MPV_COND_CBFN 8   /* the condition holding the decoder's callback */
#define MPV_HN_FREE 1
#define MPV_HN_USED 2
#define MPV_HN_SIZE 1016  /* the part of a pool entry a handle uses */
#define MPV_POOL_SIZE 7136

/* the picture information reset by mpv_ResetPicInf and filled from the lower layer by mpv_GetLowerInf */
typedef struct MpvPicInf {
    int horizontalSize;     /* 0 */
    int verticalSize;       /* 4 */
    int mbWidth;            /* 8 */
    int mbHeight;           /* 12 */
    int frameRateCode;      /* 16: picture_rate */
    int temporalReference;  /* 20 */
    int pictureCodingType;  /* 24: 1 I, 2 P, 3 B */
    int dropFrameFlag;      /* 28: the group's time code */
    int hours;              /* 32 */
    int minutes;            /* 36 */
    int seconds;            /* 40 */
    int pictures;           /* 44 */
    int gopCount;           /* 48: group headers decoded */
    int seqCount;           /* 52: sequence headers decoded */
    int f56;    /* 3 after a reset */
    int f60;    /* 1 after a reset */
    int f64;    /* 1 after a reset */
    int f68;    /* 1 after a reset */
    int bitRate;            /* 72 */
    int vbvBufferSize;      /* 76 */
    short f80, f82;
    signed char f84, f85, f86, f87, f88;
    signed char pelAspectRatio;      /* 89: aspect_ratio_information */
    signed char constrainedParams;   /* 90 */
    signed char f91, f92, f93;
    signed char f94, f95, f96, f97, f98, f99, f100;
    char pad101[128 - 101];
} MpvPicInf;

/* the header level the user data that follows belongs to */
typedef enum MpvUdLevel {
    MPV_UDLVL_SEQ = 1,
    MPV_UDLVL_GOP = 2,
    MPV_UDLVL_PIC = 3
} MpvUdLevel;

/* called with the level after user data was written to a sink */
typedef void (*MpvUsrDatFn)(void *obj, int level);

/* where the user data of one level goes: a stream joint to write it to, and a callback told when it was */
typedef struct MpvBufEnt {
    SfdSj *sj;
    MpvUsrDatFn fn;
    void *obj;
} MpvBufEnt;

/* the sequence header values of a handle */
typedef struct MpvSeqInf {
    char pad0[24];
    int width;   /* 24 */
    int height;  /* 28 */
} MpvSeqInf;

/* the size the lower layer decodes at, with its flag */
/* the buffer the user data in front of a picture is copied to, and the length copied */
typedef struct MpvPicUsr {
    char *buf;
    int size;
    int len;
} MpvPicUsr;

/* the motion vector range of one direction of a P or B picture */
typedef struct MpvMotionRange {
    int fullPel;     /* full_pel_forward_vector, or the backward one */
    int rSize;       /* f_code - 1 */
    int shift;       /* 27 - rSize */
    int f;           /* 1 << rSize */
} MpvMotionRange;

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
    char pad612[64];
    int pelAspectRatio;       /* 676 */
    int bitRate;              /* 680: bit_rate_value */
    int vbvBufferSize;        /* 684: vbv_buffer_size_value, in 2048-byte units */
    int constrainedParams;    /* 688: constrained_parameters_flag */
    int closedGop;            /* 692 */
    int brokenLink;           /* 696 */
    int vbvDelay;             /* 700 */
    char pad704[20];
    int f724;
    char pad728[4];
    int f732;
    char pad736[12];
    MpvMotionRange fwd;       /* 748: forward_f_code and full_pel_forward_vector */
    char pad764[20];
    MpvMotionRange bwd;       /* 784 */
    char pad800[32];
    int lastMbAddr;           /* 832: macroblocks in a picture, less one */
    char pad836[20];
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
    MpvUdLevel usrDatLevel;   /* 948: the level the next user data belongs to */
    MpvBufEnt bufEnt[4];      /* 952: the user-data sink of each level */
    MpvPicUsr picusr;         /* 1000 */
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

int MPV_GoNextDelimSj(SfdSj *sj);
int MPV_MoveChunk(SfdSj *sj, int id, int n);

int MPV_Init(int count, void *work);
void MPV_Finish(void);
MpvHn *MPV_Create(void);
int MPV_Destroy(MpvHn *hn);
int MPV_SetCond(MpvHn *hn, int no, int value);
int MPV_GetCond(MpvHn *hn, int no, int *value);
int MPVLIB_CheckHn(MpvHn *hn);
int mpv_StartLower(MpvHn *hn, SfdSj *sj);

void mpv_InitLibErr(void);
void mpv_ResetErr(MpvErrObj *err);
int mpv_ReportError(MpvHn *mpv, int code);
void mpvapi_Init(void);
int MPV_DecPicSj(MpvHn *mpv, SfdSj *sj, int arg);
int MPV_SkipFrmSj(MpvHn *mpv, SfdSj *sj);
int MPV_GetPicInf(MpvHn *mpv, MpvPicInf *out);
int MPV_GetBitRate(MpvHn *mpv, int *bitRate);
int MPV_GetVbvBufSiz(MpvHn *mpv, int *size, int *delay, int *bytes);
int MPV_GetLinkFlg(MpvHn *mpv, int *inf3, int *inf4);

void MPV_SetUsrSj(MpvHn *mpv, int index, SfdSj *sj, MpvUsrDatFn fn, void *obj);
void MPV_SetPicUsrBuf(MpvHn *mpv, char *buf, int size);
void MPV_GetPicUsr(MpvHn *mpv, char **buf, int *len);
int MPV_DecodePicAtrSj(MpvHn *mpv, SfdSj *sj);
int MPV_DecodePicAtr(MpvHn *mpv, SfdSjChunk *buf, int *used);

int MPV_CheckDelim(const unsigned char *p);
char *MPV_SearchDelim(char *buf, int len, int mask);
char *MPV_BsearchDelim(char *end, int len, int mask);
int MPV_IsEmptyBpic(unsigned char *buf, int nbyte, int nmb);
int MPV_IsEmptyPpic(unsigned char *buf, int nbyte, int nmb);

int mpvhook_IsInstalled(void);
void mpvhook_Init(int nobj, void *work, int size);
void mpvhook_Finish(void);
int mpvhook_Create(void);
void mpvhook_Destroy(int lower);
void mpvhook_SetCond(int lower, int no, int value);
void mpvhook_SetBufEnt(int lower, int index, SfdSj *sj, MpvUsrDatFn fn, void *obj);
void mpvhook_SetSize(int lower, char *buf, int size);
void mpvhook_SetFlagPtr(int lower, int index, int *flag);
int mpvhook_Start(int lower, SfdSj *sj);
void mpvhook_GetPicInf(int lower, MpvPicInf *inf);
void mpvhook_GetInf(int lower, int *inf);
void mpvhook_GetRate(int lower, int *a, int *b, int *c);
void mpvhook_GetDispSize(int lower, int *width, int *height);
void mpv_InstallHooks(void);

#endif
