#ifndef SFDHN_H
#define SFDHN_H

#include "dw4/cri/sj.h"
#include "dw4/cri/sfd.h"

/* The picture-user text block of a picture record: two texts and their lengths. */
typedef struct SfdPicTxt {
    char text[2][176];   /* 0 */
    int len[2];          /* 352 */
} SfdPicTxt;

/* The picture record kept in the work record: its times and its user texts. */
typedef struct SfdPicRec {
    int valid;           /* 0 */
    int bps;             /* 4 */
    int f8;
    int videoBound;      /* 12 */
    int audioBound;      /* 16 */
    int f20;
    long long baseTime;       /* 24 */
    long long startPts;       /* 32 */
    int f40;
    int f44;
    SfdPicTxt txt;       /* 48 */
} SfdPicRec;

/* The work record at handle +13864: a copy of the header and of the last picture record. */
typedef struct SfdWork {
    int state;           /* 0 */
    int f4;
    int f8;
    SfdHdrInf hdr;       /* 12 */
    SfdPicRec pic;       /* 2208 */
} SfdWork;

/* A buffer channel's area description (sfdbuf.c). */
typedef struct SfdChanInf {
    char *data;          /* 0 */
    SfdSj *sj;           /* 4 */
    unsigned char *buf;  /* 8 */
    int size;            /* 12 */
    int xsize;           /* 16 */
    int f20;
} SfdChanInf;

/* A buffer channel at handle +4872 (sfdbuf.c). */
typedef struct SfdChan {
    int state;           /* 0 */
    int valid;           /* 4 */
    int f8;
    int f12;
    SfdChanInf inf;      /* 16 */
    char pad40[76];
} SfdChan;

/* The stream table of the MPS handler: an object per stream id 0xBC..0xFF and the callback run on its data. */
typedef struct SfdMpsPrm {
    void *mps;                              /* 0: the MPS demultiplexer */
    int videoBound;                         /* 4: the most video streams a system header announced */
    int audioBound;                         /* 8: the most audio streams a system header announced */
    int pad12;
    long long startPts;                          /* 16 */
    long long firstPts;                          /* 24; LONG_MAX when unset */
    int nPics;                              /* 32 */
    int f36;
    int f40;
    int f44;
    int f48;
    int videoCh;                            /* 52 */
    int audioCh;                            /* 56 */
    int f60;
    SfdSj *object[68];                      /* 64: indexed by stream id - 0xBC */
    int (*stmCb)(void *obj, int arg);       /* 336 */
    void *stmCbObj;                         /* 340 */
    int f344;
} SfdMpsPrm;

/* A module's place in the per-handle stream graph at +7976: its work and the channels it reads and writes. */
typedef struct SfdTrnSlot {
    int f0;
    int f4;
    void *work;          /* 8 */
    void *fns;           /* 12 */
    int from;            /* 16 */
    int outputs[3];      /* 20 */
    int f32;
    char pad36[32];
} SfdTrnSlot;

/* The MPS module's place in the stream graph: the same slot with its work typed. */
typedef struct SfdMpsSlot {
    int f0;
    int f4;
    union {
        void *obj;
        SfdMpsPrm *prm;
    } hn;                /* 8: the work, a union of the drivers' work types */
    void *fns;           /* 12 */
    int from;            /* 16: the channel it demultiplexes */
    int outputs[3];      /* 20: video, audio and user-data channels */
    int f32;
    char pad36[32];
} SfdMpsSlot;

/* A user-data output of a channel: the ring it goes into and the callbacks run around each put. */
typedef struct SfdUoch {
    SfdSj *sj;
    void (*begin)(void *hn, int id);
    void (*end)(void *arg, int id);
    void *arg;
} SfdUoch;

/* The SFD handle as the core, header, supply and MPS files see it. */
typedef struct SfdHandle {
    char pad0[8];
    int f8;                  /* 8: the input size limit (0 or negative when unset) */
    char pad12[28];
    int zeroPad;             /* 40: the zero padding the demultiplexer skips */
    char pad44[28];
    int stat;                /* 72; made non-positive by an error */
    char pad76[44];
    SfdHdrInf hdr;           /* 120 */
    SfdMvInf mvInf;          /* 2316 */
    char pad2380[4];
    SfdPlyInf plyInf;        /* 2384 */
    SfdErrInf err;           /* 2544 */
    int cond[100];           /* 2564 */
    char pad2964[404];
    SfdTim tim;              /* 3368 */
    SfdChan chan[8];         /* 4872 */
    char pad5800[2176];
    SfdTrnSlot sup;          /* 7976: the supply module */
    SfdMpsSlot mps;          /* 8044: the MPS module */
    char pad8112[480];
    SfdMpsPrm mpsPrm;        /* 8592 */
    char pad8944[4920];
    SfdWork *work;           /* 13864 */
} SfdHandle;

void SFHDS_Init(void);
void SFHDS_Finish(void);
int SFHDS_SetHdr(SfdHandle *hn, int type, unsigned char *p, int size, int *set);
int SFHDS_IsSfdHeader(unsigned char *p, int size);
void SFHDS_ReprocessHdr(SfdHandle *hn);
void SFHDS_ProcessHdr(SfdHdrInf *hdr);

#endif
