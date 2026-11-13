/* The CRI MPS (MPEG program stream demultiplexer) library: its handles and work area
 * (src/cri/mpsutl.c, mpsdmx.c, mps.c). */
#ifndef DW4_CRI_MPS_H
#define DW4_CRI_MPS_H

#define MPS_HN_FREE 1
#define MPS_HN_USED 2

/* start-code classes MPS_GetStartCodeKind returns */
#define MPS_SC_PACK 0x10000     /* pack header, 00 00 01 BA */
#define MPS_SC_SYSHDR 0x20000   /* system header, 00 00 01 BB */
#define MPS_SC_PES 0x40000      /* PES packet, stream id 0xBC and up */
#define MPS_SC_END 0x80000      /* program end, 00 00 01 B9 */

typedef int (*MpsErrFn)(void *obj);

/* an error callback and the last error code reported to it */
typedef struct MpsErr {
    MpsErrFn fn;
    void *obj;
    int code;
} MpsErr;

/* the fields of the last pack header */
typedef struct MpsPackHd {
    long long scr;
    int scrExt;
    int muxRate;      /* in 50-byte units */
} MpsPackHd;

/* a system header */
typedef struct MpsSysHd {
    int f0;
    int f4;
    int audioBound;
    int videoBound;
    int f16;
    int f20;
    int f24;
    int f28;
} MpsSysHd;

/* the fields of the last PES packet header */
typedef struct MpsPesInf {
    long long pts;
    long long dts;
    int streamId;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
} MpsPesInf;

typedef struct MpsHn MpsHn;
typedef int (*MpsDecodeFn)(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
typedef void (*MpsCbFn)(void *obj, int arg);

/* one 256-byte handle */
struct MpsHn {
    int stat;                 /* 0: MPS_HN_FREE or MPS_HN_USED */
    MpsErr err;               /* 4 */
    int pesSw;                /* 16: handed to the PES parser */
    int f20;
    MpsPackHd pack;           /* 24 */
    MpsSysHd sysHd;           /* 40: the last system header */
    MpsSysHd sysHdKind[3];    /* 72: the last system header of each kind */
    MpsPesInf pes;            /* 168 */
    int f208;
    MpsDecodeFn decode;       /* 212 */
    int f216;
    int f220;
    int f224;
    MpsCbFn sysHdFn;          /* 228 */
    void *sysHdObj;           /* 232 */
    MpsCbFn auxFn;            /* 236: installed by MPS_SetAuxFn; no MPS code calls it */
    void *auxObj;             /* 240 */
    MpsCbFn pesFn;            /* 244: called with the stream id after each PES packet */
    void *pesObj;             /* 248 */
    int f252;
};

/* the work area MPS_Init is given: the library's own error callback and the handles */
typedef struct MpsWork {
    MpsErr err;
    int nhn;
    MpsHn hn[1];
} MpsWork;

void mpsutl_CopyBytes(char *dst, char *src, unsigned int n);
void mpsutl_CopyWords(int *dst, int *src, unsigned int n);
void mpsutl_FillBytes(char *dst, char value, unsigned int count);
void mpsutl_FillWords(int *dst, int value, unsigned int count);
void mpsutl_Init(void);
void mpsutl_Finish(void);

void mpsdmx_Init(void);
void mpsdmx_Finish(void);
int mpsdmx_Decode(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
int MPS_GetStartCodeKind(unsigned char *p);

int MPS_SetPesSw(MpsHn *mps, int sw);
void MPS_SetSysHdFn(MpsHn *mps, MpsCbFn fn, void *obj);
void MPS_SetAuxFn(MpsHn *mps, MpsCbFn fn, void *obj);
void MPS_SetPesFn(MpsHn *mps, MpsCbFn fn, void *obj);
int MPS_DecodeChunk(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
int MPS_IsMpeg1(unsigned char *buf, int size);

int MPS_GetPackHd(MpsHn *mps, MpsPackHd *out);
int MPS_GetSysHdOfKind(MpsHn *mps, MpsSysHd *out, int kind);
int MPS_GetSysHd(MpsHn *mps, MpsSysHd *out);
int MPS_GetPesInf(MpsHn *mps, MpsPesInf *out);
char *MPS_GetVersionStr(void);
int MPS_Init(int nhn, MpsWork *work);
int mps_InitWork(int nhn, MpsWork *work);
void MPS_Finish(void);
int MPS_EntryErrFunc(MpsHn *mps, MpsErrFn fn, void *obj);
int MPS_GetErrInf(MpsHn *mps, MpsErr *out);
MpsHn *MPS_Create(void);
int MPS_Destroy(MpsHn *mps);
int mps_CheckHn(MpsHn *mps);
int mps_ReportError(MpsHn *mps, int code);

#endif
