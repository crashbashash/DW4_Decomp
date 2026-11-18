/* CRI SFD: the Sofdec playback library. The SFD handle is passed as `void *sfd`; every SFD file reads
 * it as the one handle object, SfdPly (sfdply.h). This header holds the handle's parts. */
#ifndef DW4_CRI_SFD_H
#define DW4_CRI_SFD_H

struct SfdSj;
struct SfdBufStat;
struct SfdRecSlot;
struct SfdRec;
struct SfdMpvCond;
struct SfdPlanes;
struct SfdFrameInfo;
struct SfdPly;

/* A clock source: the time of the handle as a count of units. */
typedef int (*SfdTimeFn)(void *sfd, int *time, int *unit);

/* A time code: the frame-rate index into SFTIM_prate, the drop-frame flag and the hours to frames; repeat
 * counts the fields the picture repeats and field the half frame. */
typedef struct SfdTimeCode {
    int rate;      /* 0 */
    int drop;      /* 4 */
    int hour;      /* 8 */
    int minute;    /* 12 */
    int second;    /* 16 */
    int frame;     /* 20 */
    int add;       /* 24: added to frame */
    short repeat;  /* 28 */
    short field;   /* 30 */
} SfdTimeCode;

/* A time with the time code it came from (SFTIM_InitTtu). */
typedef struct SfdTimeRec {
    int valid;       /* 0 */
    SfdTimeCode tc;  /* 4 */
    int time;        /* 36 */
    int unit;        /* 40 */
} SfdTimeRec;

/* A ratio of 64-bit counts: a time and its unit. */
typedef struct SfdRatio {
    long long num;
    long long den;
} SfdRatio;

/* The time stabiliser of a handle (sfdtst.c): the master and helper clocks, the moving averages of their
 * difference and the adjustment limits. */
typedef struct SfdTst {
    int tstflg;                /* 0: the stabiliser is on */
    unsigned int pastat;
    unsigned int adjmode;
    int paused;
    int count;
    int pos;
    int values[60];
    long long master_time;
    long long master_unit;     /* 272 */
    long long help_time;
    long long help_unit;
    long long out_time;
    long long out_unit;        /* 304 */
    long long tolerance;       /* 312: SFTST_SetTolerance, over tolerance_unit */
    long long tolerance_unit;  /* 320 */
    long long excess;          /* 328: SFTST_SetExcessErr, over excess_unit */
    long long excess_unit;     /* 336 */
    long long adj_start;       /* 344: SFTST_SetAdjStart, over adj_start_unit */
    long long adj_start_unit;  /* 352 */
    long long adj_poff;        /* 360: SFTST_SetAdjPoff, over adj_poff_unit */
    long long adj_poff_unit;   /* 368 */
    long long base_hlp;        /* 376: the helper time at the last base, -1 with none */
    long long base_out;        /* 384: the output time at that base */
    long long mt_max;
    int adj_limit;
    int adj_front;
    int adj_rear;
    int resethist;
    int excesserr;
    int movave_1st;
    int movave_2nd;
    int diff_l_max;
    int diff_l_min;
    int diff_a_max;
    int diff_a_min;
    int pad444;
} SfdTst;

/* The running total of decoded amounts with the totals of the last 32 additions. */
typedef struct SfdSyncTally {
    int total;           /* 0 */
    int count;           /* 4 */
    int history[32];     /* 8 */
} SfdSyncTally;

/* The 32-entry queue of time stamps the audio handler hands to the video handler. */
typedef struct SfdSyncQueue {
    int last;            /* 0 */
    int samples;         /* 4: the audio samples of the files joined so far */
    int wr;              /* 8 */
    int rd;              /* 12 */
    int items[32];       /* 16 */
} SfdSyncQueue;

/* The repeated fields of the picture with one temporal reference, and the fields accumulated before it. */
typedef struct SfdFieldEntry {
    short repeat;
    unsigned short total;
} SfdFieldEntry;

/* The video PTS manager entry kept across a player reset. */
typedef struct SfdPtsm {
    int mgr;             /* 0: the manager; a reset re-attaches a non-zero one */
    int rsv[2];          /* 4: copied with it; never read */
} SfdPtsm;

/* A stream header's audio stream. */
typedef struct SfdHdrAudio {
    int codec;
    int nch;
    int bps;
    int sfreq;
} SfdHdrAudio;

/* A stream header's multiplexing description. */
typedef struct SfdHdrMux {
    int kind[4];
    int numFrm;
    int totalTime;
    int timeUnit;
} SfdHdrMux;

/* A stream header's video stream. */
typedef struct SfdHdrVideo {
    int codec;      /* 0 */
    int bitRate;    /* 4 */
    int width;      /* 8 */
    int height;     /* 12 */
    int frameRate;  /* 16 */
    int avail;      /* 20: the rest is read only when the stream says it is available */
    int picType;    /* 24 */
    int profile;    /* 28 */
    int flag0;      /* 32 */
    int flag4;      /* 36 */
    int chroma;     /* 40 */
    int zFirst;     /* 44 */
    int zSecond;    /* 48 */
} SfdHdrVideo;

/* What the CRI header in private stream 2 says about a movie, and the header bytes it was read from. */
typedef struct SfdHdrInf {
    int valid;           /* 0 */
    int verMajor;        /* 4 */
    int verMinor;        /* 8 */
    int muxRate;         /* 12: bytes per second; negative before version 1.10 */
    int bitRate;         /* 16 */
    int sysType;         /* 20 */
    int numStm;          /* 24 */
    int totalSize;       /* 28 */
    SfdHdrMux mux;       /* 32 */
    int adxStm;          /* 60: stream id 0xBD when present */
    int prv2Stm;         /* 64: stream id 0xBF when present */
    int audioStm;        /* 68: the first id in 0xC0..0xDF */
    int videoStm;        /* 72: the first id in 0xE0..0xEF */
    SfdHdrAudio audio;   /* 76 */
    SfdHdrVideo video;   /* 92 */
    int size;            /* 144 */
    char data[2048];     /* 148 */
} SfdHdrInf;

/* The stream information of a handle (handle +2316), cleared by sfply_InitMvInf and filled from the
 * stream header, the first picture's attributes and the system header (SFD_GetMvInf). */
typedef struct SfdMvInf {
    int width;           /* 0: the picture size */
    int height;          /* 4 */
    int mbWidth;         /* 8: the size in macroblocks */
    int mbHeight;        /* 12 */
    int bitRate;         /* 16: the sequence header's bit rate; 0 until a picture is read */
    int frameRate;       /* 20: the frame-rate index into SFTIM_prate */
    int muxRate;         /* 24: the pack header's mux rate */
    int fixedFlag;       /* 28: the system header's fixed flag; 1 until one is read */
    int vbvSize;         /* 32: the sequence header's VBV buffer size */
    int audioBound;      /* 36: audio streams; -1 until known */
    int videoBound;      /* 40: video streams */
    int privateBound;    /* 44: private streams */
    int f48[4];
} SfdMvInf;

/* The playback information of a handle (handle +2384, SFD_GetPlyInf): decode and skip counts, the
 * buffer-pause state and the 64-bit flow counters of the system stream, the video input, the audio input
 * and the audio decoder's stream joint. */
typedef struct SfdPlyInf {
    int numTotalDec;     /* 0 */
    int numSkip;         /* 4: skipped decodes, empty B pictures included */
    int rsv[2];          /* 8: cleared by sfply_InitPlyInf, read nowhere */
    int numSkipEmptyB;   /* 16 */
    int numSkipEmptyP;   /* 20: empty P pictures skipped */
    int frmOut;          /* 24: a frame is handed out (SFD_GetFrm until SFD_RelFrm) */
    int bpaActive;       /* 28: playback paused for want of data */
    int noSupply;        /* 32: times playback paused for want of data (MwsfdPlyInf no_supply_cnt) */
    int vidShort;        /* 36: the video input holds no whole picture */
    int noFreeFrm;       /* 40: the decoder found no free frame */
    int lockCnt;         /* 44: frames locked by SFD_LockFrm */
    long long sysFlow;   /* 48: the system stream ring's flow count */
    long long sysByte;   /* 56: system stream bytes demultiplexed */
    long long sysSkip;   /* 64 */
    long long vidFlow;   /* 72: the video input ring's flow count */
    long long vidByte;   /* 80: video bytes handed to the decoder */
    long long vidSkip;   /* 88: video bytes skipped up to a start code */
    long long audInWr;   /* 96: the audio input ring: written */
    long long audInRd;   /* 104: read */
    long long audByte;   /* 112: audio bytes handed to the decoder */
    long long audSjWr;   /* 120: the decoder's stream joint: written */
    long long audSjRd;   /* 128: read */
    long long f136;
    int f144[4];
} SfdPlyInf;

/* What the start of a stream says it is: which handlers would play it and the movie's parameters. */
typedef struct SfdAnaInf {
    char found;          /* 0 */
    char isAv;           /* 1 */
    char pad2[2];
    void *system;        /* 4: the MPS handler when the data is a system stream */
    void *video;         /* 8: the video handler */
    void *audio;         /* 12: the audio handler */
    int packSize;        /* 16; -1 when the packs are not evenly spaced */
    int width;           /* 20 */
    int height;          /* 24 */
    int bps;             /* 28 */
    int frameRate;       /* 32 */
    int vbvSize;         /* 36 */
    signed char nch;     /* 40 */
    char pad41[3];
    int sfreq;           /* 44 */
    char pad48[16];
} SfdAnaInf;

/* The callback told about each error of a handle. */
typedef void (*SfdErrFn)(void *obj, int code);

/* An error block: the first code recorded and the callback told about each error. */
typedef struct SfdErrInf {
    SfdErrFn func;                      /* 0 */
    void *obj;                          /* 4 */
    int code;                           /* 8 */
    int f12;
    int f16;
} SfdErrInf;

/* The external clock SFD_SetExtClockFn installs. */
typedef int (*SfdExtClockFn)(int ctx, int *time, int *unit);
/* The user's skip decision SFD_SetUsrIsSkipFn installs. */
typedef int (*SfdIsSkipFn)(void *sfd, int type, int time, int unit);

/* The time work of a handle (sftim.c), at handle +3368: the clock sources, the time stamps of the stream,
 * the decode tallies, the clock state, the time stabiliser, the field table and the PTS manager entry. */
typedef struct SfdTim {
    SfdTimeFn timefn[6];       /* 0: clock sources; [4] is the user's */
    SfdIsSkipFn isSkipFn;      /* 24 */
    SfdTimeCode tc;            /* 28 */
    SfdTimeRec state;          /* 60 */
    SfdTimeRec best;           /* 104 */
    SfdTimeRec tot;            /* 148: the total time */
    SfdTimeRec cur;            /* 192 */
    SfdTimeRec latest;         /* 236: the video start time */
    SfdTimeRec vofst;          /* 280: the video start offset */
    int astart_smpl;           /* 324: SFTIM_SetStartTime */
    int astart_sfreq;          /* 328 */
    int pad332;
    long long baseTime;        /* 336 */
    long long ofsTime;         /* 344 */
    int concat_frmcnt;         /* 352: the IPU frame count when the last file was joined */
    SfdSyncTally tally;        /* 356 */
    SfdSyncQueue queue;        /* 492 */
    int base;                  /* 636 */
    int base_frames;           /* 640 */
    int dec_time;              /* 644: the time of the furthest frame decoded */
    int dec_unit;              /* 648 */
    int cached_pos;            /* 652 */
    int cached_rate;           /* 656 */
    int last;                  /* 660 */
    int estimate;              /* 664 */
    int largest;               /* 668 */
    int smallest;              /* 672 */
    int usr_frm_sync;          /* 676: SFD_OutUsrFrmSync calls */
    int stream_pos;            /* 680 */
    int speed;                 /* 684: 1000 = normal */
    int disp_sync_cnt;         /* 688: SFD_OutDispSync calls */
    int disp_sync_time;        /* 692 */
    int disp_sync_unit;        /* 696 */
    int sync_count;            /* 700 */
    float sync_pending;        /* 704 */
    int sync_last;             /* 708 */
    float sync_time;           /* 712 */
    int count;                 /* 716 */
    int chg_base;              /* 720: the clock at the last time change */
    SfdExtClockFn clock_get;   /* 724 */
    int clock_last;            /* 728 */
    int decoded_pos;           /* 732 */
    int rate;                  /* 736 */
    int clock_wrap;            /* 740 */
    int clock_ctx;             /* 744 */
    int pad748;
    SfdTst tst;                /* 752 */
    SfdFieldEntry fields[64];  /* 1200: by temporal reference */
    SfdPtsm ptsm;              /* 1456 */
    char pad1468[36];
} SfdTim;

/* The SFD conditions (SFD_SetCond, SFSET_GetCond): a handle's settings, read by index. */
enum {
    SFD_COND_VIDEO = 5,             /* the movie has video to play */
    SFD_COND_AUDIO = 6,             /* the movie has audio to play */
    SFD_COND_KEEPSUP = 8,           /* a reset keeps the supply pointer */
    SFD_COND_SYNCMODE = 15,         /* 1: audio master, 2: video master */
    SFD_COND_ETIME = 20,            /* the end time, -4 for none */
    SFD_COND_ETUNIT = 21,           /* its unit */
    SFD_COND_LNKSTM = 49,
    SFD_COND_SUPPLY_END = 56,
    SFD_COND_DECODE_END = 57,
    SFD_COND_DEMUX_SPLIT = 59,
    SFD_COND_VIDEO_AUTO_OFF = 79,
    SFD_COND_AUDIO_AUTO_OFF = 80,
    SFD_COND_SYSHD_FN = 85,
    SFD_COND_SYSHD_FN_OBJ = 86,
    SFD_COND_NUM = 100
};

/* The frame buffer format the handle was created with (MWSFD converts it with
 * mwl_convBufFmtFromSFD); an enum in CRI's header. */
typedef enum SfdBufFmt {
    SFD_BUFFMT_0 = 0
} SfdBufFmt;

/* An SFBUF ring id; SFD_BUF_NONE marks a transfer slot with no ring connected. */
typedef enum SfdBufId {
    SFD_BUF_NONE = 8
} SfdBufId;

/* The creation parameters (SFD_Create); the handle starts with a copy of them. The buffer work is cut
 * into the eight buffers by their sizes. */
typedef struct SfdCrePrm {
    struct SfdTrnConfig *trnConfig;   /* 0: the stream modules by slot (SFTRN_InitHn) */
    char *bufWork;            /* 4 */
    int bufSize[8];           /* 8: the sizes of buffers 0..7 */
    int unit;                 /* 40: the input's sector size, the zero padding of a short read */
    int nfrm;                 /* 44: the decoder's frame buffers */
    int width;                /* 48: the largest picture */
    int height;               /* 52 */
    SfdBufFmt bufFmt;         /* 56: the frame buffer format */
    char *work;               /* 60: the handle work */
    unsigned int workSize;    /* 64 */
} SfdCrePrm;

/* A time stamp queued with the data it belongs to. */
typedef struct SfdItem {
    long long pos;            /* 0; negative = none */
    unsigned int addr;        /* 8 */
    unsigned int size;        /* 12 */
} SfdItem;

/* The time-stamp queue of a ring buffer (SFPTS). */
typedef struct SfdRing {
    SfdItem *items;           /* 0 */
    int size;                 /* 4 */
    int count;                /* 8 */
    int wr;                   /* 12 */
    int rd;                   /* 16 */
} SfdRing;

/* A buffer's supply: the memory area or the stream joint it is fed from (SFD_SetSupplySj). */
typedef struct SfdBufInf {
    char *data;               /* 0 */
    struct SfdSj *sj;         /* 4 */
    char *buf;                /* 8 */
    int size;                 /* 12 */
    int xsize;                /* 16 */
    char *p0;                 /* 20 */
} SfdBufInf;

/* An audio ring's second channel: where it starts and the ring's length in samples. */
typedef struct SfdBufCur {
    char *pos;
    int len;
} SfdBufCur;

/* The delimiter a ring's reader has reached and the end of the data searched for it (SFBUF_RingGetDlm). */
typedef struct SfdBufDlm {
    char *pos;
    char *end;
} SfdBufDlm;

/* A ring buffer: its supply, the delimiter, the totals written and read and the time-stamp queue. */
typedef struct SfdBufRing {
    SfdBufInf sup;            /* 0 */
    SfdBufDlm dlm;            /* 24 */
    int wtot;                 /* 32 */
    int rtot;                 /* 36 */
    SfdRing ptsque;           /* 40 */
} SfdBufRing;

/* An audio ring: the area, the sample format and the two channels, the write and read positions in
 * samples and the totals. */
typedef struct SfdBufAring {
    SfdBufInf sup;            /* 0: data is the area and sj its size until SFBUF_FixAringBuf */
    SfdBufCur ch1;            /* 24: the second channel and the ring's length in samples */
    int wpos;                 /* 32 */
    int rpos;                 /* 36 */
    int wtot;                 /* 40 */
    int rtot;                 /* 44 */
} SfdBufAring;

/* A user-data output of a buffer: the joint it goes into and the callbacks run around each put. */
typedef struct SfdUoch {
    struct SfdSj *sj;
    void (*begin)(void *hn, int id);
    void (*end)(void *arg, int id);
    void *arg;
} SfdUoch;

/* A buffer of the handle (SFBUF; mode 1 frames, 2 audio ring, 3 user outputs, 4 none, 5 ring): the
 * stream modules writing and reading it, 9 for none. */
typedef struct SfdBufEnt {
    int mode;                 /* 0 */
    int used;                 /* 4 */
    int prepFlg;              /* 8 */
    int termFlg;              /* 12 */
    union {
        SfdBufRing ring;
        SfdBufAring aring;
        SfdBufInf vfrm;       /* frames: data is the area, sj its size and xsize the frame table */
        SfdUoch uoch[3];
    } u;                      /* 16 */
    int inTr;                 /* 76 */
    int outTr;                /* 80 */
    char pad84[32];
} SfdBufEnt;

/* A stream module's entry: init, finish, server, create, destroy, ... (SFTRN), called with the
 * arguments each one takes. */
typedef int (*SfdTrnFn)();

/* The stream modules the library is initialised with. */
typedef struct SfdTrnModules {
    SfdTrnFn *fns[15];
} SfdTrnModules;

/* The stream modules of a handle by slot: 0 input, 1 system, 2 video, 3 audio, 4 video out, 5 audio
 * out, 6 and 7 output, 8 user data. */
typedef struct SfdTrnConfig {
    SfdTrnFn *fns[9];
} SfdTrnConfig;

/* The ADX audio stream module's entries (sfadx.c); a handle whose audio slot holds it plays ADX. */
extern SfdTrnFn sfadx_handler[];

/* What SFD_Init is given: the stream modules and the V-sync rate. */
typedef struct SfdInitPrm {
    SfdTrnModules *modules;   /* 0 */
    int vrate;                /* 4 */
} SfdInitPrm;

/* The system stream handler's work (sfmps.c): the demultiplexer, an output per stream id 0xBC..0xFF
 * and the callback run on its data. */
typedef struct SfdMpsPrm {
    void *mps;                              /* 0: the MPS demultiplexer */
    int videoBound;                         /* 4: the most video streams a system header announced */
    int audioBound;                         /* 8: the most audio streams a system header announced */
    int pad12;
    long long startPts;                     /* 16 */
    long long firstPts;                     /* 24; LONG_MAX when unset */
    int nPics;                              /* 32 */
    int f36;
    int f40;
    int f44;
    int f48;
    int videoCh;                            /* 52 */
    int audioCh;                            /* 56 */
    int f60;
    struct SfdSj *object[68];               /* 64: indexed by stream id - 0xBC */
    int (*stmCb)(void *obj, int arg);       /* 336 */
    void *stmCbObj;                         /* 340 */
    int f344;
} SfdMpsPrm;

/* The ADX audio parameters (SFD_SetAdxtPara): the ring buffer and the ADXT work, both aligned to 32
 * bytes when set. */
typedef struct SfdAdxCfg {
    int bsize;         /* 0: ring buffer size */
    int xsize;         /* 4: its extra size */
    char *buf;         /* 8: the ring buffer */
    int maxnch;        /* 12 */
    int rsv;           /* 16: copied by SFD_SetAdxtPara, read nowhere */
    int worksize;      /* 20 */
    char *work;        /* 24: the ADXT work */
} SfdAdxCfg;

typedef void (*SfdAdxStep)(struct SfdPly *h, char *buf, int size, int *used);

/* The ADX audio handler's work (sfadx.c). */
typedef struct SfdAdxCtx {
    void *adxt;        /* 0 */
    void *sj;          /* 4 */
    SfdAdxCfg cfg;     /* 8 */
    int time;          /* 36 */
    int unit;          /* 40 */
    int pause;         /* 44: the pause sfadxt_WaitStart asked for */
    int carry;         /* 48 */
    int started;       /* 52 */
    int pos;           /* 56 */
    SfdAdxStep step;   /* 60 */
    int noHdr;         /* 64: positive, sfadxt_GetHd reports no audio header */
    int opt27;         /* 68 */
    int total;         /* 72 */
    int rsv;           /* 76: cleared by sfadxt_InitInf, read nowhere */
} SfdAdxCtx;

/* The audio output of a handle (slot 7, SFAOAP): the renderer and the pan, volume and speed functions
 * of the audio handler. */
typedef struct SfdAoap {
    int rna;                                                   /* 0 */
    void (*setOutPan)(struct SfdPly *h, int ch, int pan);      /* 4 */
    int (*getOutPan)(struct SfdPly *h, int ch);                /* 8 */
    void (*setOutVol)(struct SfdPly *h, int vol);              /* 12 */
    int (*getOutVol)(struct SfdPly *h);                        /* 16 */
    void (*setSpeed)(struct SfdPly *h, int speed);             /* 20 */
} SfdAoap;

/* A user output of the additional-information channel (slot 8): a memory block or a stream joint. */
typedef struct SfainfOut {
    int kind;
    void *sj;
    void *buf;
    int size;
} SfainfOut;

/* The user outputs of the additional-information channel. */
typedef struct SfainfList {
    int nout;
    SfainfOut out[3];
} SfainfList;

/* A stream module's place in the handle's stream graph: its flags, its work (a union of the modules'
 * work types), its entries and the buffers it reads and writes, 8 for none. */
typedef struct SfdTrnSlot {
    int prepFlg;              /* 0 */
    int termFlg;              /* 4 */
    union {
        void *obj;
        SfdMpsPrm *mps;
        struct SfdMpv *mpv;
        SfdAdxCtx *adxt;
        SfdAoap *aoap;
        SfainfList *uo;
    } hn;                     /* 8 */
    SfdTrnFn *fns;            /* 12 */
    SfdBufId bufIn;           /* 16 */
    int bufOut[3];            /* 20: video, audio and user data for the system module */
    int readTot;              /* 32: the bytes the module has read from its input; -1 when unknown */
    char pad36[32];
} SfdTrnSlot;

/* The run-time statistics of a server step (SFTMR): the total, shortest and longest times and the count. */
typedef struct SfdTsum {
    long long sum;
    long long min;
    long long max;
    int count;
    int pad28;
} SfdTsum;

/* The server statistics of a handle (SFD_GetTmrInf); [5] times the whole server step. */
typedef struct SfdTmrInf {
    SfdTsum tsum[6];
} SfdTmrInf;

/* The library's V-sync count (sftim.c). */
typedef struct SfdTimLib {
    int vcount;               /* 0 */
    int rsv;                  /* 4: cleared by SFTIM_Init; never read */
    int vrate;                /* 8: V-syncs per 1000 seconds */
} SfdTimLib;

/* The server counters sfdply.c keeps. */
typedef struct SfdSvrCnt {
    int cnt;
    int busy;
} SfdSvrCnt;

/* The library's global state: the default conditions of a new handle, the library-wide error
 * block, the other files' library blocks and the handle table. */
typedef struct SfdLibInf {
    int cond[SFD_COND_NUM];   /* 0 */
    SfdInitPrm prm;           /* 400 */
    int sysStat;              /* 408 */
    SfdErrInf err;            /* 412 */
    SfdTimLib tim;            /* 432 */
    int buf;                  /* 444: sfdbuf.c's */
    SfdTrnModules trn;        /* 448 */
    SfdSvrCnt svr;            /* 508 */
    struct SfdPly *hn[8];     /* 516 */
} SfdLibInf;

extern SfdLibInf sfd_lib;

/* SFADXT: the ADX audio stream */
int SFADXT_IsHeader(unsigned char *header, int length, int *headerSize);
void SFD_SetAdxtPara(struct SfdAdxCfg *cfg);


/* the user streams of the audio information */
int SFD_SetUsrSj(void *sfd, int index, int kind, void *sj);

/* analysis of a stream head for the creation parameters */
void SFD_AnalyCreInf(unsigned char *buf, int size, SfdAnaInf *inf);

/* SFBUF: the stream buffers */
void sfbuf_Init(void *work);
void SFBUF_Finish(void *work);
int SFBUF_InitHn(void *sfd, SfdBufEnt *ents, SfdCrePrm *prm);
void SFBUF_DestroySj(void *sfd);
int SFBUF_SetSupplySj(void *sfd, struct SfdBufInf *inf);
void SFBUF_SetUoch(void *sfd, int index, int slot, void *uoch);
void SFBUF_GetUoch(void *sfd, int index, int slot, void *uoch);
int SFBUF_RingGetWrite(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingGetRead(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingAddWrite(void *sfd, int index, int len, int tail);
int SFBUF_RingAddRead(void *sfd, int index, int len);
void SFBUF_RingGetDlm(void *sfd, int index, char **pos, char **end);
void SFBUF_RingSetDlm(void *sfd, int index, char *pos, char *end);
int SFBUF_GetRingBufSiz(void *sfd, int index);
int SFBUF_GetRTot(void *sfd, int index);
int SFBUF_GetWTot(void *sfd, int index);
int SFBUF_RingGetSj(void *sfd, int index, struct SfdSj **out);
void SFBUF_AddRtotSj(void *sfd, int index, int len);
int SFBUF_VfrmGetRead(void *sfd, int index, struct SfdFrameInfo **frm);
int SFBUF_VfrmAddRead(void *sfd, int index, struct SfdFrameInfo *frm);
int SFBUF_SetPrepFlg(void *sfd, int index, int value);
int SFBUF_GetPrepFlg(void *sfd, int index);
void SFBUF_SetTermFlg(void *sfd, int index, int value);
int SFBUF_GetTermFlg(void *sfd, int index);
int SFBUF_RingGetDataSiz(void *sfd, int index);
void sfbuf_GetSjPos(struct SfdSj *sj, int *first, int *second);
long sfbuf_MergeTotal(long total, unsigned int low);

/* conditions and status */
int SFD_GetSvrStat(void);
int SFD_GetHnStat(void *sfd);
int SFD_SetCond(void *sfd, int index, int value);
void SFSET_SetCond(void *sfd, int index, int value);
int SFD_GetCond(void *sfd, int index, int *out);
int SFSET_GetCond(void *sfd, int index);
int SFD_GetMvInf(void *sfd, SfdMvInf *out);
int SFD_GetPlyInf(void *sfd, SfdPlyInf *out);
int SFD_GetTrHn(void *sfd, int index, int *out);

/* SFHDS: the stream header */
void SFHDS_InitFhd(SfdHdrInf *hdr);
void SFHDS_FinishFhd(SfdHdrInf *hdr);
int SFHDS_GetMuxVerNum(void *sfd);
int SFHDS_GetColType(void *sfd);
void SFHDS_Init(void);
void SFHDS_Finish(void);
int SFHDS_SetHdr(struct SfdPly *hn, int type, unsigned char *p, int size, int *set);
int SFHDS_IsSfdHeader(unsigned char *p, int size);
void SFHDS_ReprocessHdr(struct SfdPly *hn);
void SFHDS_ProcessHdr(SfdHdrInf *hdr);

/* the library, errors and locks */
int SFD_IsHnSize(void *work, int size);
long SFD_Init(struct SfdInitPrm *prm);
int SFD_Finish(void);
void sfd_ClearErr(SfdErrInf *err);
int SFD_SetErrFn(void *sfd, SfdErrFn func, void *obj);
int sfd_ReportError(void *sfd, int code);
int SFLIB_CheckHn(void *sfd);
void sfd_Lock(void *guard);
void sfd_Unlock(void *guard);

/* playback */
int SFD_GetPaStat(void *sfd);
int SFD_Pause(void *sfd, int sw);
int SFD_Standby(void *sfd);
int SFD_SetSpeed(void *sfd, int value);
int SFD_SetAudioCh(void *sfd, int value);
int SFD_SetVideoCh(void *sfd, int value);
void sfmpvps2_Init(void);
void SFD_VsyncSvr(void);
int SFD_IsHnSvrWait(void *sfd);
int SFD_IsSvrDone(void);
int SFD_ExecOne(void *sfd);
int SFPLY_DecideSvrStat(void);
void SFPLY_AddSkipPic(void *sfd, int delta, int arg);
int SFD_Destroy(void *sfd);
int SFD_Start(void *sfd);
int SFD_Stop(void *sfd);
int SFPLY_Stop(void *sfd);
int SFPLY_GetResetFlg(void);
int SFD_GetWritePtr(void *sfd, struct SfdBufStat *inf);
int SFD_AddWritePtr(void *sfd, int a, int b);
int SFD_TermSupply(void *sfd);
int SFD_GetFrm(void *sfd, int *out);
int SFD_RelFrm(void *sfd, int value);
int SFD_SetSupplySj(void *sfd, struct SfdBufInf *inf);

/* SFSEE: seeking and the stream record */
void SFSEE_InitHn(struct SfdRecSlot *slot);
int SFD_EntrySeek(void *sfd, struct SfdRec *rec);
void SFSEE_FixAvPlay(void *sfd, int id3512, int id3516);
void SFSEE_ExecServer(void *sfd);
int SFD_SetFileSize(void *sfd, int value);
int SFD_SetTotTime(void *sfd, int divisor, int scale);
int SFD_SetByteRate(void *sfd, int value);
void SFD_SetSeekPos(void *sfd, int offset);

/* the time-stamp rings */
int SFPTS_WritePtsQue(void *sfd, int index, struct SfdItem *item, int *full);
int SFPTS_ReadPtsQue(struct SfdPly *h, int index, unsigned int pos, struct SfdItem *out);
int SFPTS_IsPtsQueFull(void *sfd, int index);

/* SFCON: concatenated playback */
int SFD_SetConcatPlay(void *sfd);
int SFCON_IsEndcodeSkip(void *sfd);
int SFCON_IsSystemEndcodeSkip(void *sfd);
int SFCON_IsVideoEndcodeSkip(void *sfd);
int SFCON_UpdateConcatTime(void *sfd, int amount);
int SFCON_WriteTotSmplQue(void *sfd, int pts, int last);
int SFCON_ReadTotSmplQue(struct SfdPly *hn, int *pts, int *last);

/* SFTRN: the stream modules */
int SFTRN_Init(struct SfdTrnModules *dst, struct SfdTrnModules *src);
int SFTRN_Finish(struct SfdTrnModules *modules);
void SFTRN_InitHn(void *sfd, SfdTrnSlot *s, SfdCrePrm *prm, int arg);
int SFTRN_CallTrSetup(void *sfd, int k);
void SFTRN_SetPrepFlg(void *sfd, int index, int value);
int SFTRN_GetPrepFlg(void *sfd, int index);
void SFTRN_SetTermFlg(void *sfd, int index, int value);
int SFTRN_GetTermFlg(void *sfd, int index);
int SFTRN_CallTrtTrif(void *sfd, int index, int k, int a, int b);
int SFTRN_IsSetup(void *sfd, int index);

/* the pass-through wrappers between the SFD files */
void SFPTS_InitPtsQue(void *ring);
int SFD_SetVideoPts(void *sfd, void *data, int size);
void SFTMR_InitTsum(SfdTsum *tsum);
void SFTMR_AddTsum(SfdTsum *tsum, long time);
int SFMPV_SaveCond(void *sfd, int *values, unsigned int size);
void SFMPV_RestoreCond(void *sfd, int *values, int count);
int SFPL2_Standby(void *sfd);
void SFMPVP_SearchPsc(void *sfd, unsigned char *data, int size);
void SFMPVP_Destroy(void *sfd);
int SFTIM_GetAudioStartSample(void *tim, int scale);
void SFTIM_Pause(void *sfd, unsigned int kind);
void *SFD_Create(struct SfdCrePrm *prm, int arg);
extern int SFTIM_prate[];

/* SFTST: the time-stamp statistics */
void SFTST_Create(SfdTst *p);
void SFTST_SetTstFlg(SfdTst *tst, int value);
long SFTST_SetTolerance(SfdTst *tst, SfdRatio *ratio);
void SFTST_SetExcessErr(SfdTst *tst, SfdRatio *ratio);
void SFTST_SetAdjStart(SfdTst *tst, SfdRatio *ratio);
long SFTST_SetAdjPoff(SfdTst *tst, SfdRatio *ratio);
void SFTST_SetMovaveRange(SfdTst *tst, int count);
void SFTST_Pause(SfdTst *tst, unsigned int pastat);
void SFTST_SetAdjFlg(SfdTst *tst, int paused);
void SFTST_GoNextFrame(SfdTst *tst, SfdRatio *ratio);
void SFTST_Calc(SfdTst *tst, SfdRatio *mt, SfdRatio *hlp, SfdRatio *out);

/* the user audio output */
void SFD_SetOutPan(void *sfd, int a, int b);
int SFD_GetOutPan(void *sfd, int a);
void SFD_SetOutVol(void *sfd, int a);
int SFD_GetOutVol(void *sfd);
void SFAOAP_SetSpeed(void *sfd, int a);

/* SFMPS: the system stream */
int SFD_GetVideoCh(void *sfd);
int SFD_GetAudioCh(void *sfd);
int SFMPS_GetConcatCnt(void *sfd);

/* SFMPV: the video stream */
void SFD_SetMpvParaTbl(struct SfdMpvCond *cond, int *work, int *bufs);
void SFD_CalcYccPlane(char *base, int width, int height, struct SfdPlanes *planes);
void SFD_SetMpvCond(void *sfd, int mode, int value);
int SFD_GetNumFrm(void *sfd, int *out);
void SFD_SetPicUsrBuf(void *sfd, char *base, int count, int size);
void SFD_GetNextPicUsr(void *sfd, char **data, int *size);
int SFD_GetNumRemainFrm(void *sfd);
int SFD_IsNextFrmReady(void *sfd);

/* SFMPVP: the PS2 MPEG decoder */
void SFD_SetSceMpeg(int enable);
int SFMPVP_IsSceMpegUsed(void *sfd);
void SFMPVP_Init(void);
char *SFD_GetSceErrMessage(void *sfd);
int SFMPVP_Put(void *sfd, char *src, int pos);
int SFMPVP_Unput(void *sfd, int count);
void sfmpvps2_StopIpu(void *sfd, int value);
int SFMPVP_GetFrameCount(void *sfd);
int SFMPVP_IsPscEnough(void *sfd);
void SFMPVP_Create(void *sfd);

/* SFTIM: playback time */
void SFTIM_Init(SfdTimLib *lib, int vrate);
void SFTIM_Finish(SfdTimLib *lib);
void SFTIM_InitHn(void *sfd, SfdTim *tim);
void SFTIM_InitTtu(SfdTimeRec *rec, int time);
void SFTIM_UpdateItime(SfdTim *tim, int now);
int SFTIM_GetNextItime(SfdTim *tim, int now);
void SFTIM_VbIn(void);
int SFTIM_IsStagnant(void *sfd);
int SFTIM_GetVideoStartSample(SfdTim *tim, int scale, int *valid);
void SFTIM_SetStartTime(SfdTim *tim, int a, int b);
int SFD_GetTime(void *sfd, int *time, int *unit);
int SFTIM_GetTimeSub(void *sfd, int *time, int *unit);
int SFTIM_GetTime(void *sfd, int *time, int *unit);
int SFTIM_ChkRegularTime(void *sfd, int *time, int *unit);
int SFD_CmpTime(int num0, int den0, int num1, int den1);
int SFD_SetExtClockFn(void *sfd, SfdExtClockFn get, int wrap, int ctx);
int SFD_SetUsrIsSkipFn(void *sfd, SfdIsSkipFn fn);
int SFD_SetUsrTimeFn(void *sfd, SfdTimeFn fn);
int SFD_UpdateTime(void *sfd);
void SFTIM_SetTimeFn(void *sfd, SfdTimeFn fn, int index);
void SFTIM_Tc2Time(SfdTimeCode *tc, int *time, int *unit);
void SFTIM_GetTimeOneFrmVideo(void *sfd, int *scale, int *rate);
int SFD_GetFps(void *sfd, int *rate);
int SFTIM_IsGetFrmTime(void *sfd, struct SfdFrameInfo *frm);
int SFTIM_IsGetFrmTimeTunit(void *sfd, int time, int unit);
int SFTIM_IsVideoTerm(void *sfd);
void SFTIM_SetSpeed(void *sfd, int value);
int SFTIM_GetSpeed(void *sfd);

#endif
