/* The MWSFD player handle (MWPLY): one 696-byte entry of the player table in the MWSFD work area. */
#ifndef DW4_CRI_MWPLY_H
#define DW4_CRI_MWPLY_H

typedef struct MwsfdPly MwsfdPly;

typedef struct MwsfdPlyVtbl {
    void *slot[8];
    int (*getStat)(MwsfdPly *ply);             /* 32 */
    void *slot36[6];
    void (*setSj)(MwsfdPly *ply, struct SfdSj *sj); /* 60: given the input SJ before a file start */
} MwsfdPlyVtbl;

/* the creation parameters (mwPlyCreateSofdec's cprm), copied into the handle */
typedef struct MwsfdCreInf {
    int type;        /* 0 */
    int maxBps;      /* 4: scaled into the input byte rate, capped by inputBufSize */
    int maxWidth;    /* 8 */
    int maxHeight;   /* 12 */
    int nfrmPoolWk;  /* 16: frames in the work pool */
    int nfrm;        /* 20: input size multiplier, at least 1 */
    char *work;      /* 24: the player's malloc pool; 0 needs malloc functions */
    int workSize;    /* 28 */
    int f32;         /* 32 */
    int bufFmt;      /* 36: below 3 */
    int f40;         /* 40 */
    int f44;         /* 44 */
} MwsfdCreInf;

/* the player's own allocation pool */
typedef struct MwsfdMemPool {
    char *base;
    int size;
    char *cur;
    int used;
} MwsfdMemPool;

typedef enum MwsfdChromaFmt {
    MWSFD_CHROMA_FMT_0,
    MWSFD_CHROMA_FMT_1,
    MWSFD_CHROMA_FMT_2,
    MWSFD_CHROMA_FMT_3
} MwsfdChromaFmt;

typedef enum MwsfdChromaPos {
    MWSFD_CHROMA_POS_0,
    MWSFD_CHROMA_POS_1
} MwsfdChromaPos;

typedef struct MwsfdPicInf {
    unsigned int pictureStructure; /* 0 */
    unsigned int chromaFormat;     /* 4 */
    int f8;
    int f12;
    int f16;
    MwsfdChromaPos chromaPosH;     /* 20 */
    MwsfdChromaPos chromaPosV;     /* 24 */
    int f28;                       /* 28: cleared when the information is taken */
} MwsfdPicInf;

/* one entry of the per-picture log ring (8 entries, slot = position % 8) */
typedef struct MwsfdPicLog {
    int valid;          /* 0: set once the entry holds a picture */
    int picNo;          /* 4 */
    int itemTypeThree;  /* 8: mwply_IsPicItemType3 of the picture */
    int hdrInfo;        /* 12: header info word, -1 when absent */
    int compoMode;      /* 16: composition mode, 17 by default */
} MwsfdPicLog;

/* a picture user buffer: (nfrmPoolWk + 4) units of `unit` bytes */
typedef struct MwsfdPicUsrBuf {
    char *addr;
    int size;
    int unit;
} MwsfdPicUsrBuf;

typedef struct MwsfdUsrBuf {
    char *buf; /* 0 */
    int size;  /* 4 */
    int f8;    /* 8 */
} MwsfdUsrBuf;

typedef struct MwsfdAddInf {
    int valid;  /* 0 */
    char *addr; /* 4 */
    int size;   /* 8 */
} MwsfdAddInf;

/* the MWSST input: an SJ ring over a work buffer fed by the input callback table */
typedef struct MwsfdSst {
    int created;            /* 0: 1 once MWSST_Create succeeded */
    char *work;             /* 4 */
    int workSize;           /* 8 */
    struct SfdSj *sj;       /* 12: SJRBF over work */
    int stmNo;              /* 16: video stream number; SFD_SetStmObject id = 0xC0 + stmNo */
    int extHn;              /* 20: handle from the callback table's create */
} MwsfdSst;

struct MwsfdPly {
    MwsfdPlyVtbl *vtbl;             /* 0 */
    int used;                       /* 4 */
    int stat;                       /* 8: 2 while playing */
    MwsfdCreInf cre;                /* 12 */
    char pad60[4];
    void *sfd;                      /* 64: the SFD player handle */
    void *stm;                      /* 68: the MWSTM (ADXSTM) file stream */
    void *adxt;                     /* 72: the ADXT handle, mwPlyGetAdxtHn */
    struct LscObj *lsc;             /* 76: the link stream controller of seamless playback */
    int compoSet;                   /* 80 */
    int compoMode;                  /* 84 */
    int frmSync;                    /* 88: mwPlySetFrmSync */
    char pad92[4];
    int waitingSvr;                 /* 96: set while a caller waits for the server */
    int svrBusy;                    /* 100: set by the server around a pass */
    int inSfdExec;                  /* 104: set by the server around its SFD execution */
    int execFlg;                    /* 108: the server pass's used-state */
    char pad112[4];
    signed char linkReq;            /* 116: mwPlyLinkStm's switch */
    signed char linkPrev;           /* 117: set on a 1 -> 0 link switch: a term is pending */
    signed char pause;              /* 118: the pause switch, re-applied on start */
    char pad119;
    int nEntry;                     /* 120: files entered by mwPlyEntryFname, cleared by mwSfdStop */
    int curFrm;                     /* 124: the frame held by mwPlyGetCurFrm */
    int limit;                      /* 128 */
    int count;                      /* 132 */
    int numSkipDisp;                /* 136 */
    MwsfdPicInf pic;                /* 140 */
    void *sfx;                      /* 172 */
    char *sfxWork;                  /* 176 */
    int sfxWorkSize;                /* 180 */
    int picCount;                   /* 184 */
    int logPos;                     /* 188 */
    int logWrite;                   /* 192 */
    MwsfdPicLog log[8];             /* 196 */
    MwsfdPicUsrBuf sysPicUsrBuf;    /* 356: carved from the buffer given to mwPlySetSysPicUsrBuf */
    MwsfdPicUsrBuf attPicUsrBuf;    /* 368: the one given to mwPlyAttachPicUsrBuf */
    MwsfdPicUsrBuf *picUsrBuf;      /* 380: the one in use */
    char *udbuf;                    /* 384 */
    int udbufsize;                  /* 388 */
    char *ud;                       /* 392: the current picture's user data */
    int udsize;                     /* 396 */
    struct SjObj *addInfSj;         /* 400 */
    char *addInfBase;               /* 404 */
    int addInfSize;                 /* 408 */
    MwsfdUsrBuf usrBuf;             /* 412 */
    MwsfdAddInf addInf;             /* 424 */
    char pad436[4];
    char *fname;                    /* 440 */
    int fnameMax;                   /* 444: capacity of fname */
    int stmReq;                     /* 448: a file read is still to be started on stm */
    void *stmDir;                   /* 452 */
    int stmOfst;                    /* 456 */
    int stmNsct;                    /* 460 */
    struct SfdSj *sj;               /* 464: the SJ the SFD reads from */
    struct SfdSj *defSj;            /* 468: the player's own input SJ, mwPlyGetInputSj */
    char *inputBuf;                 /* 472: the input ring buffer */
    int inputBufSize;               /* 476 */
    int inputXSize;                 /* 480 */
    int srcType;                    /* 484: 2 for a caller's SJ */
    int src488;                     /* 488 */
    int src492;                     /* 492 */
    int src496;                     /* 496 */
    struct SfdSj *memSj;            /* 500: the SJ made over mwSfdStartMem's buffer */
    char *memBuf;                   /* 504 */
    int memSize;                    /* 508 */
    MwsfdMemPool pool;              /* 512 */
    int mallocCnt;                  /* 528 */
    void *mallocBlk[32];            /* 532: MWSFD_Malloc's blocks, freed together */
    MwsfdSst sst;                   /* 660: the SST input */
    char pad684[8];
    int f692;                       /* 692: cleared by the SFD stop */
};

#endif
