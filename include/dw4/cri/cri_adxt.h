/* CRI ADXT: the ADX playback handle; src/cri/adxt.c, adxtinit.c, adxtsvr.c, adxtsml.c (seamless playback),
 * adxtpl2.c (Pro Logic II), adxfssvr.c (the file-system server) and adxhdr.c (ADX headers). */
#ifndef DW4_CRI_CRI_ADXT_H
#define DW4_CRI_CRI_ADXT_H

#include "dw4/cri/sj.h"
#include "dw4/cri/lsc.h"
#include "dw4/cri/adxsjd.h"
#include "dw4/cri/adxstm.h"
#include "dw4/cri/adxamp.h"
#include "dw4/cri/ps2rna.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADXT_MAX_OBJ 16
#define ADXT_SCT_LEN 2048

/* CRI's ADXHINFO: what ADXT_GetHdrInfo reports about an ADX header; fmt 1 is ADX and 2 is AHX. CRI's own code
 * stores the header's loop count in lptype. */
typedef struct AdxtHdrInfo {
    int fmt;
    int sfreq;
    int nch;
    int bps;
    int nsmpl;
    int lptype;
    int lpstart;
    int lpend;
} AdxtHdrInfo;

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

/* One ADX playback handle. */
typedef struct AdxtObj {
    signed char used;
    signed char stat;           /* AdxtStat */
    signed char pmode;          /* AdxtPmode */
    signed char maxnch;
    AdxSjdObj *sjd;
    AdxStmObj *stm;
    Ps2Rna *rna;
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

typedef void (*AdxtHookFunc)(AdxtObj *adxt);
typedef void (*AdxtFltFunc)(void *obj, int ch, char *data, int len);
typedef void (*AdxtDecFunc)(void *obj, int nsmpl, int nbyte);
typedef void (*AdxtErrFunc)(void *obj, char *message);
typedef void (*AdxtDecInfoFunc)(AdxtObj *adxt, int sfreq, int nch, int total_nsmpl);

/* An ACX file: big-endian counts and offsets of the ADX streams it holds. */
typedef struct AcxEntry {
    int ofst;
    int len;
} AcxEntry;

typedef struct AcxHeader {
    int id;
    int count;
    AcxEntry ent[1];
} AcxHeader;

extern AdxtObj adxt_obj[ADXT_MAX_OBJ];
extern int adxt_output_mono;
/* the hook that detaches a Pro Logic II encoder, installed by ADXT_AttachPl2 */
extern AdxtHookFunc adxt_detach_pl2;

/* adxt.c */
AdxtObj *ADXT_Create(int maxnch, char *work, int worksize);
AdxtObj *ADXT_CreatePl2(char *work, int worksize);
void ADXT_DetachAhx(AdxtObj *adxt);
void ADXT_DetachPl2(AdxtObj *adxt);
void ADXT_Destroy(AdxtObj *adxt);
void ADXT_DestroyAll(void);
void ADXT_CloseAllHandles(void);
void adxt_start_sj(AdxtObj *adxt, SfdSj *sji);
void adxt_start_stm(AdxtObj *adxt, char *fname, void *dir, int ofst, int nsct);
void ADXT_StartSj(AdxtObj *adxt, SfdSj *sj);
void ADXT_StopWithoutLsc(AdxtObj *adxt);
void ADXT_Stop(AdxtObj *adxt);
int ADXT_GetStat(AdxtObj *adxt);
void ADXT_SetTimeMode(int mode);
void ADXT_GetTimeSfreq(AdxtObj *adxt, int *ncount, int *tscale);
void ADXT_GetTime(AdxtObj *adxt, int *ncount, int *tscale);
int ADXT_GetTimeReal(AdxtObj *adxt);
int ADXT_GetNumSmpl(AdxtObj *adxt);
int ADXT_GetSfreq(AdxtObj *adxt);
int ADXT_GetNumChan(AdxtObj *adxt);
int ADXT_GetHdrLen(AdxtObj *adxt);
int ADXT_GetFmtBps(AdxtObj *adxt);
void ADXT_SetOutPan(AdxtObj *adxt, int ch, int pan);
int ADXT_GetOutPan(AdxtObj *adxt, int ch);
void ADXT_SetOutBalance(AdxtObj *adxt, int balance);
int ADXT_GetOutBalance(AdxtObj *adxt);
void ADXT_SetOutVol(AdxtObj *adxt, int vol);
int ADXT_GetOutVol(AdxtObj *adxt);
short ADXT_GetDefOutVol(AdxtObj *adxt);
short ADXT_GetDefPan(AdxtObj *adxt, int ch);
char *ADXT_GetDataId(AdxtObj *adxt);
char *ADXT_GetHdrDataId(unsigned char *hdr);
void ADXT_SetDefSvrFreq(int freq);
void ADXT_SetSvrFreq(AdxtObj *adxt, int freq);
void ADXT_SetReloadTime(AdxtObj *adxt, float time, int nch, int sfreq);
void ADXT_ResetReloadTime(AdxtObj *adxt);
void ADXT_SetReloadSct(AdxtObj *adxt, int minsct);
short ADXT_GetReloadSct(AdxtObj *adxt);
int ADXT_GetNumSctIbuf(AdxtObj *adxt);
int ADXT_GetNumSmplObuf(AdxtObj *adxt, int ch);
float ADXT_GetIbufRemainTime(AdxtObj *adxt);
int ADXT_IsIbufSafety(AdxtObj *adxt);
void ADXT_SetAutoRcvr(AdxtObj *adxt, int rmode);
int ADXT_IsCompleted(AdxtObj *adxt);
void ADXT_ExecServer(void);
int ADXT_GetErrCode(AdxtObj *adxt);
void ADXT_ClearErrCode(AdxtObj *adxt);
int ADXT_GetLpCnt(AdxtObj *adxt);
void ADXT_SetLpFlg(AdxtObj *adxt, int flg);
SfdSj *ADXT_GetInputSj(AdxtObj *adxt);
void ADXT_SetWaitPlayStart(AdxtObj *adxt, int flg);
int ADXT_IsReadyPlayStart(AdxtObj *adxt);
void ADXT_Pause(AdxtObj *adxt, int sw);
int ADXT_GetStatPause(AdxtObj *adxt);
void ADXT_SetOutMode(int mode);
int ADXT_GetOutMode(void);
void ADXT_SetTranspose(AdxtObj *adxt, int fxch, int fxlev);
void ADXT_GetTranspose(AdxtObj *adxt, int *fxch, int *fxlev);
AdxStmObj *ADXT_GetStm(AdxtObj *adxt);
void ADXT_TermSupply(AdxtObj *adxt);
void ADXT_SetDrctLvl(AdxtObj *adxt, int lvl);
int ADXT_GetDrctLvl(AdxtObj *adxt);
void ADXT_SetFilter(AdxtObj *adxt, int coff, int q);
void ADXT_GetFilter(AdxtObj *adxt, int *coff, int *q);
void ADXT_SetSurround(AdxtObj *adxt, int sw);
void ADXT_GetSurround(AdxtObj *adxt, int *sw);
void ADXT_EntryErrFunc(AdxtErrFunc func, void *obj);
int ADXT_DiscardSmpl(AdxtObj *adxt, int nsmpl);
int ADXT_GetTimeOfst(AdxtObj *adxt);
void ADXT_SetTimeOfst(AdxtObj *adxt, int ofst);
void ADXT_AdjustSmpl(AdxtObj *adxt, int nsmpl);
void ADXT_SetLnkSw(AdxtObj *adxt, int sw);
int ADXT_GetLnkSw(AdxtObj *adxt);
void ADXT_EntryFltFunc(AdxtObj *adxt, AdxtFltFunc func, void *obj);
int ADXT_GetDecNumSmpl(AdxtObj *adxt);
int ADXT_GetDecDtLen(AdxtObj *adxt);
void ADXT_EntryDecFunc(AdxtObj *adxt, AdxtDecFunc func, void *obj);
int ADXT_IsHeader(unsigned char *buf, int len, int *hdrlen);
int ADXT_IsEndcode(unsigned char *buf, int len, int *ftrlen);
int ADXT_InsertSilence(AdxtObj *adxt, int nch, int nsmpl);
void ADXT_SetOutputMono(int flag);
void ADXT_SetKeyString(AdxtObj *adxt, char *str);
void ADXT_SetDefKeyString(char *str);
Ps2Rna *ADXT_GetRna(AdxtObj *adxt);
void ADXT_ResetDefFmt(AdxtObj *adxt);
void ADXT_StartAfs(AdxtObj *adxt, int ptid, int flid);
void ADXT_StartFnameRange(AdxtObj *adxt, char *fname, int ofst, int nsct);
void ADXT_StartFname(AdxtObj *adxt, char *fname);
void ADXT_StartMem(AdxtObj *adxt, char *data);
void ADXT_StartMem2(AdxtObj *adxt, char *data, int size);
void ADXT_StartMemIdx(AdxtObj *adxt, AcxHeader *acx, int no);

/* adxtinit.c */
void ADXT_ConfigVsyncSvr(int value);
void ADXT_VsyncProc(void);
void ADXT_Init(void);
void ADXT_ResetLibrary(void);
void ADXT_Finish(void);
void ADXT_InsertHdrSfa(AdxtObj *adxt, int nch, int sfreq, int nsmpl);

/* adxtsvr.c */
AdxtDecInfoFunc ADXT_EntryDecInfoFunc(AdxtDecInfoFunc func);
void ADXT_ExecErrChk(AdxtObj *adxt);
void ADXT_ExecRdErrChk(AdxtObj *adxt);
void ADXT_ExecRdCompChk(AdxtObj *adxt);
void ADXT_ExecHndl(AdxtObj *adxt);
int ADXT_GetStatRead(AdxtObj *adxt);

/* adxtsml.c */
void ADXT_EntryFname(AdxtObj *adxt, const char *fname);
void ADXT_EntryFnameRange(AdxtObj *adxt, const char *fname, int ofst, int nsct);
void ADXT_EntryAfs(AdxtObj *adxt, int ptid, int flid);
void ADXT_StartSeamless(AdxtObj *adxt);
void ADXT_SetSeamlessLp(AdxtObj *adxt, int sw);
void ADXT_StartFnameLp(AdxtObj *adxt, const char *fname);
void ADXT_StartFnameRangeLp(AdxtObj *adxt, const char *fname, int ofst, int nsct);
void ADXT_StartAfsLp(AdxtObj *adxt, int ptid, unsigned int flid);
void ADXT_ReleaseSeamless(void);
int ADXT_GetNumFiles(AdxtObj *adxt);
void ADXT_ResetEntry(AdxtObj *adxt);

/* adxtpl2.c */
void ADXT_AttachPl2(AdxtObj *adxt, void *work, int wksize);
void ADXT_SetPl2Pos(AdxtObj *adxt, int x, int y);

/* adxfssvr.c */
void ADXT_ExecFsSvr(void);
void ADXT_ExecFsServer(void);
int ADXT_IsActiveFsSvr(void);

/* adxhdr.c */
void ADXT_GetHdrInfo(void *buf, int size, AdxtHdrInfo *info);

#ifdef __cplusplus
}
#endif

#endif
