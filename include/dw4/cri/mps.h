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
    int isMpeg1;      /* the stream is MPEG-1: the first two bits after the start code are 00 */
    int muxRate;      /* in 50-byte units */
} MpsPackHd;

/* a system header: the fields of the last one parsed, one word each */
typedef struct MpsSysHd {
    int headerLength;
    int rateBound;       /* in 50-byte units */
    int audioBound;
    int videoBound;
    int fixedFlag;
    int cspsFlag;
    int audioLockFlag;   /* system_audio_lock_flag */
    int videoLockFlag;   /* system_video_lock_flag */
} MpsSysHd;

/* one stream entry of a system header: the P-STD buffer bound of a stream */
typedef struct MpsSysHdStream {
    unsigned char streamId;
    unsigned char bufferBoundScale;
    unsigned short bufferSizeBound;
} MpsSysHdStream;

#define MPS_SYSHD_MAX_STREAMS 48

/* what the system-header callback is given: the header fields, narrowed, and its stream entries */
typedef struct MpsSysHdInf {
    int rateBound;
    unsigned char audioBound;
    unsigned char fixedFlag;
    unsigned char cspsFlag;
    unsigned char audioLockFlag;
    unsigned char videoLockFlag;
    unsigned char videoBound;
    unsigned char packetRateRestrictionFlag;
    unsigned char reserved;
    int streamCount;
    MpsSysHdStream stream[MPS_SYSHD_MAX_STREAMS];
} MpsSysHdInf;

/* stream classes of a PES packet */
#define MPS_PES_AUDIO 0
#define MPS_PES_VIDEO 1
#define MPS_PES_PRIVATE 2
#define MPS_PES_PADDING 3
#define MPS_PES_OTHER 4

/* the fields of the last PES packet header */
typedef struct MpsPesInf {
    long long pts;
    long long dts;
    int streamId;
    int streamKind;      /* MPS_PES_* */
    int streamNo;        /* the number of the stream within its kind */
    int packetLength;
    int stdBufferSize;   /* P-STD buffer size, in bytes */
    int dataSize;        /* the packet's bytes after the header */
} MpsPesInf;

typedef struct MpsHn MpsHn;
typedef int (*MpsDecodeFn)(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
typedef void (*MpsCbFn)(void *obj, int arg);
typedef void (*MpsSysHdFn)(void *obj, MpsSysHdInf *inf);

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
    MpsSysHdFn sysHdFn;       /* 228 */
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

void UTY_MemcpyByte(char *dst, char *src, unsigned int n);
void UTY_MemcpyDword(int *dst, int *src, unsigned int n);
void UTY_MemsetByte(char *dst, char value, unsigned int count);
void UTY_MemsetDword(int *dst, int value, unsigned int count);
void mpsutl_Init(void);
void mpsutl_Finish(void);

void mpsdmx_Init(void);
void mpsdmx_Finish(void);
int mpsdmx_Decode(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
int MPS_GetStartCodeKind(unsigned char *p);

int MPS_SetPesSw(MpsHn *mps, int sw);
void MPS_SetSysHdFn(MpsHn *mps, MpsSysHdFn fn, void *obj);
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
int mpslib_InitLibWork(int nhn, MpsWork *work);
void MPS_Finish(void);
int MPS_SetErrFn(MpsHn *mps, MpsErrFn fn, void *obj);
int MPS_GetErrInf(MpsHn *mps, MpsErr *out);
MpsHn *MPS_Create(void);
int MPS_Destroy(MpsHn *mps);
int MPSLIB_CheckHn(MpsHn *mps);
int MPSLIB_SetErr(MpsHn *mps, int code);

#endif
