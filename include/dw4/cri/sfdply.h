/* The SFD handle (SFD_Create): the one object every SFD file reads, with the seek record it is given. */
#ifndef DW4_CRI_SFDPLY_H
#define DW4_CRI_SFDPLY_H

#include "dw4/cri/sj.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/sfmpv.h"

typedef struct SfdPly SfdPly;

typedef struct SfdRec SfdRec;

/* A seek request (SFD_Seek): the time to seek to, -3 for none, and its unit. */
typedef struct SfdRecSub {
    int rsv;       /* 0: cleared by SFSEE_InitHn, copied with the request, read nowhere */
    int time;
    int unit;
} SfdRecSub;

/* The seek record of a handle (SFD_EntrySeek) and the request kept with it. */
typedef struct SfdRecSlot {
    SfdRec *rec;   /* 0 */
    SfdRecSub sub; /* 4 */
} SfdRecSlot;

/* The pack and system headers of the video and the audio stream, kept for seeking. */
typedef struct SfdSysHd {
    char data[2][176];   /* 0 */
    int len[2];          /* 352 */
} SfdSysHd;

/* The system stream analysis kept in the seek record (sfmps.c, sfd_mps.c in RE4's library): the byte
 * rate, the streams of the system header, the first time stamps and stream ids, and the headers. */
typedef struct SfdRecSys {
    int valid;            /* 0: analysed */
    int time;             /* 4: bytes per unit */
    int unit;             /* 8 */
    int nvid;             /* 12: video streams of the system header */
    int naud;             /* 16: audio streams */
    int f20;
    long long scrBase;    /* 24 */
    long long ptsMin;     /* 32 */
    int stmidVid;         /* 40: the first video stream id */
    int stmidAud;         /* 44: the first audio stream id */
    SfdSysHd syshd;       /* 48 */
} SfdRecSys;

/* The audio stream's analysis. */
typedef struct SfdRecAudio {
    int valid;
    int time;
    int unit;
    int nch;
    int sfreq;
    int nsmpl;
} SfdRecAudio;

/* The seek record SFD_EntrySeek hands a handle (sfdrec.c): the header and stream analysis of the movie,
 * then the totals the application sets. */
struct SfdRec {
    int state;                    /* 0 */
    int time;                     /* 4 */
    int unit;                     /* 8 */
    SfdHdrInf hdrInf;             /* 12 */
    SfdRecSys sys;                /* 2208 */
    char pad2616[152];
    SfdRecVideo video;            /* 2768 */
    SfdRecAudio audio;            /* 3340 */
    char pad3364[132];
    int derived;                  /* 3496 */
    int default_value;            /* 3500 */
    int default_divisor;          /* 3504 */
    int default_scale;            /* 3508 */
    int id3512;
    int id3516;
    int delegate;                 /* 3520 */
    int fsize;                    /* 3524: SFD_SetFileSize */
    int tottime;                  /* 3528: SFD_SetTotTime */
    int tunit;                    /* 3532 */
    int byterate;                 /* 3536: SFD_SetByteRate */
    int seekpos;                  /* 3540: SFD_SetSeekPos */
};

/* The SFD handle: the creation parameters, the play state, the movie's header and information, the
 * conditions, the time work, the buffers and frames, the stream graph with the system, video, audio and
 * output modules' work, the seek record and the server statistics. */
struct SfdPly {
    SfdCrePrm cre;               /* 0 */
    int pending;                 /* 68: set by a change the server has to see */
    int stat;                    /* 72 */
    int reqStat;                 /* 76 */
    int pause;                   /* 80 */
    int pauseCnt;                /* 84 */
    char pad88[32];
    SfdHdrInf hdr;               /* 120 */
    SfdMvInf mvInf;              /* 2316 */
    char pad2380[4];
    SfdPlyInf plyInf;            /* 2384 */
    SfdErrInf err;               /* 2544 */
    int cond[SFD_COND_NUM];      /* 2564 */
    int cond2[SFD_COND_NUM];     /* 2964: the conditions a reset restores */
    char pad3364[4];
    SfdTim tim;                  /* 3368 */
    SfdBufEnt buf[8];            /* 4872 */
    SfdVfrm vfrm[16];            /* 5800 */
    SfdTrnSlot trn[9];           /* 7976 */
    char pad8588[4];
    SfdMpsPrm mps;               /* 8592 */
    char pad8944[176];
    SfdMpv mpv;                  /* 9120 */
    SfdAdxCtx adxt;              /* 13600 */
    char pad13680[100];
    SfdAoap aoap;                /* 13780 */
    char pad13804[4];
    SfainfList uo;               /* 13808 */
    char pad13860[4];
    SfdRecSlot see;              /* 13864 */
    SfdTmrInf tmr;               /* 13880 */
};

#endif
