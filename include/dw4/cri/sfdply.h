/* The SFD handle as the player files (sfdply.c, sfdring.c, sfdrec.c) see it. */
#ifndef DW4_CRI_SFDPLY_H
#define DW4_CRI_SFDPLY_H

#include "dw4/cri/sj.h"
#include "dw4/cri/sfd.h"

typedef struct SfdCrePrm {
    int f0;
    char *f4;
    char pad8[52];
    char *work;            /* 60 */
    unsigned int workSize; /* 64 */
} SfdCrePrm;

typedef struct SfdCond {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int req1;    /* 20 */
    int req2;    /* 24 */
    int f28;
    int f32;
    char pad36[20];
    int f56;
    int mode;    /* 60 */
    char pad64[16];
    int request; /* 80; -4 = none */
    int value;   /* 84 */
    char pad88[92];
    int f180;
    char pad184[216];
} SfdCond;

typedef struct SfdPly SfdPly;


typedef struct SfdItem {
    long long pos;          /* 0; negative = none */
    unsigned int addr; /* 8 */
    unsigned int size; /* 12 */
} SfdItem;

typedef struct SfdRing {
    SfdItem *items; /* 0 */
    int size;       /* 4 */
    int count;      /* 8 */
    int wr;         /* 12 */
    int rd;         /* 16 */
} SfdRing;

typedef struct SfdStmInf {
    int f0;
    SfdSj *sj;         /* 4 */
    int base;          /* 8 */
    int size;          /* 12 */
} SfdStmInf;

typedef struct SfdStmEnt {
    char pad0[16];
    SfdStmInf info; /* 16 */
    char pad32[24];
    SfdRing ring;   /* 56 */
    char pad76[40];
} SfdStmEnt;

typedef struct SfdF28 {
    char pad0[20];
    int f20;
    char pad24[128];
    int f152;
    char pad156[64];
    int f220;
    char pad224[5664];
} SfdF28;

typedef struct SfdRec SfdRec;

typedef struct SfdRecSub {
    int f0;
    int f4;
    int f8;
} SfdRecSub;

typedef struct SfdRecSlot {
    SfdRec *rec;   /* 0 */
    SfdRecSub sub; /* 4 */
} SfdRecSlot;

/* The system stream analysis kept in the seek record (sfd_mps.c in RE4's library). */
typedef struct SfdRecSysTime {
    int set;              /* 0: analysed */
    int time;             /* 4 */
    int unit;             /* 8 */
    int nvid;             /* 12: video streams of the system header */
    int naud;             /* 16: audio streams */
    int f20;
    long long scr_base;   /* 24 */
    long long pts_min;    /* 32 */
    int stmid_vid;        /* 40: the first video stream id */
    int stmid_aud;        /* 44: the first audio stream id */
} SfdRecSysTime;

typedef struct SfdRecAudioTime {
    int set;
    int time;
    int unit;
} SfdRecAudioTime;

typedef struct SfdRecVideoTime {
    int set;
    int time;
    int unit;
    int f12;
    int f16;
    int f20;
} SfdRecVideoTime;

/* The seek record SFD_EntrySeek hands a handle (sfdrec.c): the header and stream analysis of the movie,
 * then the totals the application sets. */
struct SfdRec {
    int state;                    /* 0 */
    int time;                     /* 4 */
    int unit;                     /* 8 */
    SfdHdrInf hdrInf;             /* 12 */
    SfdRecSysTime sysTime;        /* 2208 */
    char pad2256[512];
    SfdRecAudioTime audioTime;    /* 2768 */
    SfdTimeRec startTime;         /* 2780 */
    char pad2824[516];
    SfdRecVideoTime videoTime;    /* 3340 */
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

typedef struct SfdTblEnt {
    char pad0[32];
} SfdTblEnt;

typedef struct SfdTable {
    SfdTblEnt ent[5];  /* 0 */
    char trailer[64];  /* 160 */
} SfdTable;

struct SfdPly {
    SfdCrePrm cre;        /* 0 */
    int pending;          /* 68 */
    int stat;             /* 72 */
    int reqStat;          /* 76 */
    int pause;            /* 80 */
    int pauseCnt;         /* 84 */
    char pad88[32];
    SfdHdrInf hdr;        /* 120 */
    SfdMvInf mvInf;       /* 2316 */
    char pad2380[4];
    SfdPlyInf plyInf;     /* 2384 */
    SfdErrInf err;        /* 2544 */
    SfdCond cond;         /* 2564 */
    SfdCond cond2;        /* 2964 */
    char pad3364[4];
    SfdTim tim;           /* 3368 */
    SfdStmEnt ent[8];     /* 4872 */
    char pad5800[2176];
    SfdF28 f28;           /* 7976 */
    SfdRecSlot recSlot;   /* 13864 */
    SfdTable tbl;         /* 13880 */
};

#endif
