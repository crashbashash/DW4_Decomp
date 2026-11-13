/* The MWSFD player handle (MWPLY): one 696-byte entry of the player table in the MWSFD work area. */
#ifndef DW4_CRI_MWPLY_H
#define DW4_CRI_MWPLY_H

typedef struct MwsfdPly MwsfdPly;

typedef struct MwsfdPlyVtbl {
    void *slot[8];
    int (*getStat)(MwsfdPly *ply); /* 32 */
} MwsfdPlyVtbl;

/* the creation parameters, kept in the handle */
typedef struct MwsfdCreInf {
    int type;        /* 0 */
    char pad4[12];
    int nfrmPoolWk;  /* 16: frames in the work pool */
    char pad20[12];
    int f32;         /* 32 */
} MwsfdCreInf;

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

struct MwsfdPly {
    MwsfdPlyVtbl *vtbl;             /* 0 */
    int used;                       /* 4 */
    int stat;                       /* 8: 2 while playing */
    MwsfdCreInf cre;                /* 12 */
    char pad48[16];
    void *sfd;                      /* 64: the SFD player handle */
    void *stm;                      /* 68: the MWSTM (ADXSTM) file stream */
    char pad72[4];
    struct LscObj *lsc;             /* 76: the link stream controller of seamless playback */
    int compoSet;                   /* 80 */
    int compoMode;                  /* 84 */
    char pad88[8];
    int waitingSvr;                 /* 96: set while a caller waits for the server */
    char pad100[4];
    int inSfdExec;                  /* 104: set by the server around its SFD execution */
    char pad108[20];
    int limit;                      /* 128 */
    int count;                      /* 132 */
    char pad136[4];
    MwsfdPicInf pic;                /* 140 */
    char pad168[4];
    void *sfx;                      /* 172 */
    char pad176[8];
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
    char pad444[4];
    int stmReq;                     /* 448: a file read is still to be started on stm */
    void *stmDir;                   /* 452 */
    int stmOfst;                    /* 456 */
    int stmNsct;                    /* 460 */
    char pad464[8];
    char *inputBuf;                 /* 472: the input ring buffer */
    int inputBufSize;               /* 476 */
    int inputXSize;                 /* 480 */
    char pad484[176];
    int inputType;                  /* 660: 1 when the input is an SJ */
    char pad664[8];
    struct SfdSj *inputSj;          /* 672 */
    char pad676[4];
    int inputExtHn;                 /* 680: released through the input callback table */
    char pad684[12];
};

#endif
