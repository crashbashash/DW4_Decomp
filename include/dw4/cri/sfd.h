/* CRI SFD: the Sofdec playback library. The SFD handle is passed as `void *sfd`; each SFD file reads
 * it through its own view of the handle object. */
#ifndef DW4_CRI_SFD_H
#define DW4_CRI_SFD_H

struct SfdAdxCfg;
struct SfdBufEnt;
struct SfdBufCrePrm;
struct SfdBufInf;
struct SfdBufStat;
struct SfdSj;
struct SfdInitPrm;
struct SfdRecSlot;
struct SfdRec;
struct SfdItem;
struct SfdTrnModules;
struct SfdTrnSlot;
struct SfdTrnConfig;
struct SfdMpvCond;
struct SfdPlanes;
struct SfdLib;
struct SfdTimeSpan;
struct SfdCrePrm;

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
    int f0;
    unsigned int pastat;
    unsigned int adjmode;
    int paused;
    int count;
    int pos;
    int values[60];
    long long master_time;
    long long f272;
    long long help_time;
    long long help_unit;
    long long out_time;
    long long f304;
    long long f312;
    long long f320;
    long long f328;
    long long f336;
    long long f344;
    long long f352;
    long long f360;
    long long f368;
    long long f376;
    long long f384;
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
    int f4;
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
    int f0;
    int f4;
    int f8;
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
 * stream header and the system header (SFD_GetMvInf). */
typedef struct SfdMvInf {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int muxRate;         /* 24: the pack header's mux rate */
    int fixedFlag;       /* 28: the system header's fixed flag; 1 until one is read */
    int f32;
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
    int f8;
    int f12;
    int numSkipEmptyB;   /* 16 */
    int f20;
    int f24;
    int bpaActive;       /* 28: playback paused for want of data */
    int noSupply;        /* 32: times playback paused for want of data (MwsfdPlyInf no_supply_cnt) */
    int f36;
    int f40;
    int f44;
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
    int f352;
    SfdSyncTally tally;        /* 356 */
    SfdSyncQueue queue;        /* 492 */
    int base;                  /* 636 */
    int base_frames;           /* 640 */
    int f644;
    int f648;
    int cached_pos;            /* 652 */
    int cached_rate;           /* 656 */
    int last;                  /* 660 */
    int estimate;              /* 664 */
    int largest;               /* 668 */
    int smallest;              /* 672 */
    int f676;
    int stream_pos;            /* 680 */
    int speed;                 /* 684: 1000 = normal */
    int f688;
    int f692;
    int f696;
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
int SFBUF_InitHn(void *sfd, struct SfdBufEnt *ents, struct SfdBufCrePrm *prm);
void SFBUF_DestroySj(void *sfd);
int SFBUF_SetSupplySj(void *sfd, struct SfdBufInf *inf);
void SFBUF_SetUoch(void *sfd, int index, int slot, void *uoch);
void SFBUF_GetUoch(void *sfd, int index, int slot, void *uoch);
int SFBUF_RingGetWrite(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingGetRead(void *sfd, int index, struct SfdBufStat *stat);
int SFBUF_RingAddWrite(void *sfd, int index, int len, int tail);
int SFBUF_RingAddRead(void *sfd, int index, int len);
void SFBUF_RingGetDlm(void *sfd, int index, int *pos, int *len);
void SFBUF_RingSetDlm(void *sfd, int index, int pos, int len);
int SFBUF_GetRingBufSiz(void *sfd, int index);
int SFBUF_GetRTot(void *sfd, int index);
int SFBUF_GetWTot(void *sfd, int index);
int SFBUF_RingGetSj(void *sfd, int index, struct SfdSj **out);
void SFBUF_AddRtotSj(void *sfd, int index, int len);
int SFBUF_VfrmGetRead(void *sfd, int index, int value);
int SFBUF_VfrmAddRead(void *sfd, int index, int value);
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
int SFPTS_IsPtsQueFull(void *sfd, int index);

/* SFCON: concatenated playback */
int SFD_SetConcatPlay(void *sfd);
int SFCON_IsEndcodeSkip(void *sfd);
int SFCON_IsSystemEndcodeSkip(void *sfd);
int SFCON_IsVideoEndcodeSkip(void *sfd);
int SFCON_UpdateConcatTime(void *sfd, int amount);
int SFCON_WriteTotSmplQue(void *sfd, int pts, int last);

/* SFTRN: the stream modules */
int SFTRN_Init(struct SfdTrnModules *dst, struct SfdTrnModules *src);
int SFTRN_Finish(struct SfdTrnModules *modules);
void SFTRN_InitHn(void *sfd, struct SfdTrnSlot *s, struct SfdTrnConfig **pconfig, int arg);
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
void SFTMR_InitTsum(void *stat);
void SFTMR_AddTsum(void *stat, long time);
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
int SFD_GetSceErrMessage(void *sfd);
int SFMPVP_Put(void *sfd, char *src, int pos);
int SFMPVP_Unput(void *sfd, int count);
void sfmpvps2_StopIpu(void *sfd, int value);
int SFMPVP_GetFrameCount(void *sfd);
int SFMPVP_IsPscEnough(void *sfd);
void SFMPVP_Create(void *sfd);

/* SFTIM: playback time */
void SFTIM_Init(struct SfdLib *lib, int rate);
void SFTIM_Finish(struct SfdLib *lib);
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
int SFTIM_IsGetFrmTime(void *sfd, struct SfdTimeSpan *span);
int SFTIM_IsGetFrmTimeTunit(void *sfd, int time, int unit);
int SFTIM_IsVideoTerm(void *sfd);
void SFTIM_SetSpeed(void *sfd, int value);
int SFTIM_GetSpeed(void *sfd);

#endif
