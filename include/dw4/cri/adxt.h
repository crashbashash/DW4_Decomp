/* CRI ADXT: the ADX playback handle; src/cri/adxt.c and src/cri/adxtsvr.c. */
#ifndef DW4_CRI_ADXT_H
#define DW4_CRI_ADXT_H

/* lsc.h brings sfdsj.h, which has no include guard. */
#include "dw4/cri/lsc.h"

#define ADXT_MAX_OBJ 16
#define ADXT_SCT_LEN 2048

typedef struct AdxSjdObj AdxSjdObj;
typedef struct AdxStmObj AdxStmObj;
typedef struct AdxRna AdxRna;
typedef struct AdxAmpObj AdxAmpObj;

enum AdxtStat {
    ADXT_STAT_STOP = 0,
    ADXT_STAT_DECINFO = 1,
    ADXT_STAT_PREP = 2,
    ADXT_STAT_PLAYING = 3,
    ADXT_STAT_DECEND = 4,
    ADXT_STAT_PLAYEND = 5,
    ADXT_STAT_ERROR = 6
};

/* What the handle plays from. */
enum AdxtPmode {
    ADXT_PMODE_FNAME = 0,
    ADXT_PMODE_AFS = 1,
    ADXT_PMODE_MEM = 2,
    ADXT_PMODE_SJ = 3,
    ADXT_PMODE_SLFILE = 4
};

/* What the error check does once it flags an error. */
enum AdxtRmode {
    ADXT_RMODE_NOACT = 0,
    ADXT_RMODE_STOP = 1,
    ADXT_RMODE_REPLAY = 2
};

enum AdxtErrCode {
    ADXT_ERR_OK = 0,
    ADXT_ERR_SHRTBUF = -1,
    ADXT_ERR_SNDBLK = -2
};

/* SJ lines. */
enum { SJ_LIN_FREE = 0, SJ_LIN_DATA = 1 };

enum AdxSjdStat {
    ADXSJD_STAT_STOP = 0,
    ADXSJD_STAT_DECHDR = 1,
    ADXSJD_STAT_DECODE = 2,
    ADXSJD_STAT_DECEND = 3
};

enum AdxStmStat {
    ADXSTM_STAT_STOP = 0,
    ADXSTM_STAT_READING = 2,
    ADXSTM_STAT_READEND = 3,
    ADXSTM_STAT_ERROR = 4
};

/* One ADX playback handle. */
typedef struct AdxtObj {
    signed char used;
    signed char stat;           /* AdxtStat */
    signed char pmode;          /* AdxtPmode */
    signed char maxnch;
    AdxSjdObj *sjd;
    AdxStmObj *stm;
    AdxRna *rna;
    SfdSj *sjf;                 /* the ring buffer over ibuf the stream fills */
    SfdSj *sji;                 /* the decoder's input */
    SfdSj *sjo[2];
    char *ibuf;
    int ibufbsize;
    int ibufxsize;
    char *obuf;
    int obufsize;
    int obufdist;
    int svrfreq;                /* server calls per second */
    short maxsct;
    short minsct;               /* reload sectors */
    short outvol;
    short outpan[2];
    short outbalance;
    int maxdecsmpl;
    int lpcnt;
    int lp_skiplen;
    int trp;
    int wpos;
    int mofst;
    short ercode;               /* AdxtErrCode */
    int edecpos;
    short edeccnt;
    short eshrtcnt;
    signed char lpflg;
    signed char autorcvr;       /* AdxtRmode */
    signed char fltmode;
    signed char execflag;
    signed char pstwait_flag;
    signed char pstready_flag;
    signed char pause_flag;
    AdxAmpObj *amp;
    SfdSj *ampsji[2];
    SfdSj *ampsjo[2];
    int time_ofst;
    int lesct;                  /* loop end sector */
    int trpnsmpl;               /* loop start sample */
    LscObj *lsc;
    signed char lnkflg;         /* seamless link switch */
    unsigned int vtime;         /* V-sync time at the base count */
    int vbase;                  /* V-sync count the time was taken at */
    int decofst;                /* samples decoded by earlier linked streams */
    int pad_nsmpl;              /* silence padded after the end */
    signed char stm_req;        /* a file start waits for the stream to stop */
    char *fnbuf;                /* file name buffer after ibuf */
    char *fname;
    void *dir;
    int ofst;
    int nsct;
} AdxtObj;

extern AdxtObj adxt_obj[ADXT_MAX_OBJ];
extern int adxt_vsync_cnt;

/* adxt.c */
void adxt_start_sj(AdxtObj *adxt, SfdSj *sji);
void adxt_start_stm(AdxtObj *adxt, char *fname, void *dir, int ofst, int nsct);
void ADXT_Stop(AdxtObj *adxt);
int ADXT_GetStat(AdxtObj *adxt);
int ADXT_GetNumChan(AdxtObj *adxt);
void ADXT_SetOutPan(AdxtObj *adxt, int ch, int pan);
void ADXT_SetFx(AdxtObj *adxt, int fxch, int fxlev);
void ADXT_GetFx(AdxtObj *adxt, int *fxch, int *fxlev);
void ADXT_SetLnkSw(AdxtObj *adxt, int sw);

/* adxtsvr.c */
void ADXT_ExecHndl(AdxtObj *adxt);

/* ADXCRS */
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);

/* ADXERR */
void ADXERR_CallErrFunc1(const char *message);
void ADXERR_CallErrFunc2(const char *code, const char *message);
void ADXERR_ItoA2(int value1, int value2, char *buf, int size);

/* ADXSJD */
void ADXSJD_SetInSj(AdxSjdObj *sjd, SfdSj *sji);
void ADXSJD_Start(AdxSjdObj *sjd);
void ADXSJD_Stop(AdxSjdObj *sjd);
void ADXSJD_TermSupply(AdxSjdObj *sjd);
int ADXSJD_GetStat(AdxSjdObj *sjd);
int ADXSJD_GetNumChan(AdxSjdObj *sjd);
int ADXSJD_GetSfreq(AdxSjdObj *sjd);
int ADXSJD_GetOutBps(AdxSjdObj *sjd);
int ADXSJD_GetBlkSmpl(AdxSjdObj *sjd);
int ADXSJD_GetTotalNumSmpl(AdxSjdObj *sjd);
int ADXSJD_GetDecNumSmpl(AdxSjdObj *sjd);
short ADXSJD_GetDefOutVol(AdxSjdObj *sjd);
int ADXSJD_GetLpStartPos(AdxSjdObj *sjd);
int ADXSJD_GetLpEndPos(AdxSjdObj *sjd);
int ADXSJD_GetLpStartOfst(AdxSjdObj *sjd);
void ADXSJD_SetDecPos(AdxSjdObj *sjd, int pos);
void ADXSJD_SetMaxDecSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_SetTrapNumSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_SetTrapCnt(AdxSjdObj *sjd, int cnt);
void ADXSJD_SetTrapDtLen(AdxSjdObj *sjd, int len);
void ADXSJD_EntryTrapFunc(AdxSjdObj *sjd, void (*func)(AdxtObj *adxt), AdxtObj *adxt);

/* ADXSTM */
void ADXSTM_SetEos(AdxStmObj *stm, int sct);
void ADXSTM_EntryEosFunc(AdxStmObj *stm, void (*func)(AdxtObj *adxt), AdxtObj *adxt);
int ADXSTM_GetStat(AdxStmObj *stm);
int ADXSTM_Seek(AdxStmObj *stm, int sct);
int ADXSTM_Start(AdxStmObj *stm);

/* ADXRNA */
void ADXRNA_SetTransSw(AdxRna *rna, int sw);
void ADXRNA_SetPlaySw(AdxRna *rna, int sw);
int ADXRNA_GetNumData(AdxRna *rna);
void ADXRNA_SetOutVol(AdxRna *rna, int vol);
void PS2RNA_SetStopFlag(AdxRna *rna, int sw);

void SJ_SplitChunk(SfdSjChunk *ck, int len, SfdSjChunk *head, SfdSjChunk *rest);
void *memset(void *dst, int value, unsigned int size);

#endif
