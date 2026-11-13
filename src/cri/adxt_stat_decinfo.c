/* include/dw4/cri/sfdsj.h, repeated: this unit builds without -Iinclude. */
typedef struct SfdSj SfdSj;

typedef struct SfdSjChunk {
    char *data;
    int len;
} SfdSjChunk;

typedef struct SfdSjVtbl {
    void *slot0;
    void *slot1;
    void *slot2;
    void (*destroy)(SfdSj *sj);                                    /* 12 */
    int (*getUuid)(SfdSj *sj);                                     /* 16 */
    void (*reset)(SfdSj *sj);                                      /* 20 */
    void (*getChunk)(SfdSj *sj, int id, int n, SfdSjChunk *ck);    /* 24 */
    void (*ungetChunk)(SfdSj *sj, int id, SfdSjChunk *ck);         /* 28 */
    void (*putChunk)(SfdSj *sj, int id, SfdSjChunk *ck);           /* 32 */
    int (*getNumData)(SfdSj *sj, int id);                          /* 36 */
} SfdSjVtbl;

struct SfdSj {
    SfdSjVtbl *vtbl;
};

typedef struct AdxSjdObj AdxSjdObj;
typedef struct AdxStmObj AdxStmObj;
typedef struct AdxRna AdxRna;
typedef struct AdxAmpObj AdxAmpObj;
typedef struct LscObj LscObj;

/* CRI ADXT: one ADX playback handle, 0xc4 bytes. */
typedef struct AdxtObj {
    signed char used;           /* 0x00 */
    signed char stat;           /* 0x01: AdxtStat */
    signed char pmode;          /* 0x02: AdxtPmode */
    signed char maxnch;         /* 0x03 */
    AdxSjdObj *sjd;             /* 0x04 */
    AdxStmObj *stm;             /* 0x08 */
    AdxRna *rna;                /* 0x0c */
    SfdSj *sjf;                 /* 0x10: ring buffer over ibuf */
    SfdSj *sji;                 /* 0x14: current input */
    SfdSj *sjo[2];              /* 0x18 */
    char *ibuf;                 /* 0x20 */
    int ibufbsize;              /* 0x24 */
    int ibufxsize;              /* 0x28 */
    char *obuf;                 /* 0x2c */
    int obufsize;               /* 0x30 */
    int obufdist;               /* 0x34 */
    int svrfreq;                /* 0x38: server calls per second */
    short maxsct;               /* 0x3c */
    short minsct;               /* 0x3e: reload sectors */
    short outvol;               /* 0x40 */
    short outpan[2];            /* 0x42 */
    short outbalance;           /* 0x46 */
    int maxdecsmpl;             /* 0x48 */
    int lpcnt;                  /* 0x4c */
    int lp_skiplen;             /* 0x50 */
    int trp;                    /* 0x54 */
    int wpos;                   /* 0x58 */
    int mofst;                  /* 0x5c */
    short ercode;               /* 0x60 */
    short pad98;
    int edecpos;                /* 0x64 */
    short edeccnt;              /* 0x68 */
    short eshrtcnt;             /* 0x6a */
    signed char lpflg;          /* 0x6c */
    signed char autorcvr;       /* 0x6d: AdxtRmode */
    signed char fltmode;        /* 0x6e */
    signed char execflag;       /* 0x6f */
    signed char pstwait_flag;   /* 0x70 */
    signed char pstready_flag;  /* 0x71 */
    signed char pause_flag;     /* 0x72 */
    char pad115;
    AdxAmpObj *amp;             /* 0x74 */
    SfdSj *ampsji[2];           /* 0x78 */
    SfdSj *ampsjo[2];           /* 0x80 */
    int time_ofst;              /* 0x88 */
    int lesct;                  /* 0x8c: loop end sector */
    int trpnsmpl;               /* 0x90: loop start sample */
    LscObj *lsc;                /* 0x94 */
    signed char lnkflg;         /* 0x98: seamless link switch */
    char pad153[3];
    int vtime;                  /* 0x9c: V-sync time at the base count */
    int vbase;                  /* 0xa0: V-sync count the time was taken at */
    int decofst;                /* 0xa4: samples decoded by earlier linked streams */
    int pad_nsmpl;              /* 0xa8: silence padded after the end */
    signed char stm_req;        /* 0xac: a file start waits for the stream to stop */
    char pad173[3];
    char *fnbuf;                /* 0xb0: file name buffer after ibuf */
    char *fname;                /* 0xb4 */
    void *dir;                  /* 0xb8 */
    int ofst;                   /* 0xbc */
    int nsct;                   /* 0xc0 */
} AdxtObj;

enum AdxtStat {
    ADXT_STAT_STOP = 0,
    ADXT_STAT_DECINFO = 1,
    ADXT_STAT_PREP = 2,
    ADXT_STAT_PLAYING = 3,
    ADXT_STAT_DECEND = 4,
    ADXT_STAT_PLAYEND = 5,
    ADXT_STAT_ERROR = 6
};

enum AdxtPmode {
    ADXT_PMODE_SJ = 0,
    ADXT_PMODE_FNAME = 1,
    ADXT_PMODE_MEM = 2
};

enum { ADXSJD_STAT_DECODE = 2 };
enum { ADXSTM_STAT_READING = 2 };
enum { ADXB_FORMAT_SPSD = 2 };

#define ADXT_SCT_LEN 2048

typedef void (*AdxtDecInfoFunc)(AdxtObj *adxt, int sfreq, int nch, int total_nsmpl);

extern AdxtDecInfoFunc adxt_decinfo_func;
extern char E9081001_adxt_stat_decinfo_can_t_play_this_number_of_channels[];
void ADXAMP_SetSfreq(AdxAmpObj *amp, int sfreq);
void ADXERR_CallErrFunc2(const char *code, const char *message);
void ADXERR_ItoA2(int value1, int value2, char *buf, int size);
void ADXRNA_SetTransSw(AdxRna *rna, int sw);
void ADXRNA_SetNumChan(AdxRna *rna, int nch);
void ADXRNA_SetSfreq(AdxRna *rna, int sfreq);
void ADXRNA_SetOutVol(AdxRna *rna, int vol);
void ADXRNA_SetBitPerSmpl(AdxRna *rna, int bps);
void ADXRNA_SetTotalNumSmpl(AdxRna *rna, int nsmpl);
void ADXRNA_SetStmHdInfo(AdxRna *rna, char *info);
int ADXSJD_GetStat(AdxSjdObj *sjd);
void ADXSJD_SetMaxDecSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_EntryTrapFunc(AdxSjdObj *sjd, void (*func)(AdxtObj *), AdxtObj *adxt);
void ADXSJD_SetTrapNumSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_SetTrapCnt(AdxSjdObj *sjd, int cnt);
void ADXSJD_SetTrapDtLen(AdxSjdObj *sjd, int len);
int ADXSJD_GetFormat(AdxSjdObj *sjd);
int ADXSJD_GetSfreq(AdxSjdObj *sjd);
int ADXSJD_GetNumChan(AdxSjdObj *sjd);
int ADXSJD_GetOutBps(AdxSjdObj *sjd);
int ADXSJD_GetBlkSmpl(AdxSjdObj *sjd);
int ADXSJD_GetTotalNumSmpl(AdxSjdObj *sjd);
int ADXSJD_GetNumLoop(AdxSjdObj *sjd);
int ADXSJD_GetLpStartPos(AdxSjdObj *sjd);
int ADXSJD_GetLpEndPos(AdxSjdObj *sjd);
int ADXSJD_GetLpEndOfst(AdxSjdObj *sjd);
int ADXSJD_GetDefOutVol(AdxSjdObj *sjd);
char *ADXSJD_GetSpsdInfo(AdxSjdObj *sjd);
int ADXSTM_GetStat(AdxStmObj *stm);
void ADXSTM_EntryEosFunc(AdxStmObj *stm, void (*func)(AdxtObj *), AdxtObj *adxt);
void ADXSTM_SetEos(AdxStmObj *stm, int sct);
void adxt_start_stm(AdxtObj *adxt, char *fname, void *dir, int ofst, int nsct);
void ADXT_Stop(AdxtObj *adxt);
void ADXT_SetFx(AdxtObj *adxt, int fxch, int fxlev);
void ADXT_GetFx(AdxtObj *adxt, int *fxch, int *fxlev);
void adxt_set_outpan(AdxtObj *adxt);
void adxt_trap_entry_lp(AdxtObj *adxt);
void adxt_eos_entry(AdxtObj *adxt);
void adxt_trap_entry_lnk(AdxtObj *adxt);

/* State DECINFO: starts a pending file stream, waits for the header, then sizes the decode step,
 * sets the loop traps and configures the renderer for the stream. */
void adxt_stat_decinfo(AdxtObj *adxt)
{
    char nchstr[32];
    AdxSjdObj *sjd;
    int sctlen;
    int fxch;
    int fxlev;
    int sfreq;
    int nch;
    int total_nsmpl;
    int nloop;
    int lpeofst;
    int blkbytes;

    sctlen = ADXT_SCT_LEN;
    fxch = 0;
    sjd = adxt->sjd;
    fxlev = 0;
    adxt->pad_nsmpl = 0;
    if ((adxt->pmode == ADXT_PMODE_SJ || adxt->pmode == ADXT_PMODE_FNAME) && adxt->stm_req == 1) {
        if (ADXSTM_GetStat(adxt->stm) == ADXSTM_STAT_READING) {
            return;
        }
        if (adxt->sjf != 0) {
            adxt->sjf->vtbl->reset(adxt->sjf);
        }
        adxt_start_stm(adxt, adxt->fname, adxt->dir, adxt->ofst, adxt->nsct);
        adxt->stm_req = 0;
    }
    if (ADXSJD_GetStat(sjd) != ADXSJD_STAT_DECODE) {
        return;
    }
    nch = ADXSJD_GetNumChan(sjd);
    if (adxt->maxnch < nch) {
        ADXERR_ItoA2(nch, adxt->maxnch, nchstr, 16);
        ADXERR_CallErrFunc2(E9081001_adxt_stat_decinfo_can_t_play_this_number_of_channels, nchstr);
        ADXT_Stop(adxt);
        return;
    }
    sfreq = ADXSJD_GetSfreq(sjd);
    nloop = ADXSJD_GetNumLoop(sjd);
    if (nloop > 0) {
        adxt->maxdecsmpl = (sfreq / adxt->svrfreq) * 3;
    } else {
        adxt->maxdecsmpl = (sfreq / adxt->svrfreq) * 3 / 2;
    }
    blkbytes = ADXSJD_GetBlkSmpl(sjd) * 2;
    adxt->maxdecsmpl = ((adxt->maxdecsmpl + blkbytes) / blkbytes) * blkbytes;
    ADXSJD_SetMaxDecSmpl(sjd, adxt->maxdecsmpl);
    if (nloop > 0) {
        if (adxt->pmode == ADXT_PMODE_MEM) {
            adxt->lp_skiplen = 0;
        } else {
            lpeofst = ADXSJD_GetLpEndOfst(sjd);
            adxt->lp_skiplen = sctlen - lpeofst % sctlen;
            adxt->lp_skiplen = adxt->lp_skiplen % sctlen;
            adxt->lesct = (lpeofst + sctlen - 1) / sctlen;
            ADXSTM_SetEos(adxt->stm, adxt->lesct);
            ADXSTM_EntryEosFunc(adxt->stm, adxt_eos_entry, adxt);
        }
        ADXSJD_GetLpEndPos(sjd);
        adxt->trpnsmpl = ADXSJD_GetLpStartPos(sjd);
        ADXSJD_SetTrapNumSmpl(sjd, adxt->trpnsmpl);
        ADXSJD_SetTrapDtLen(sjd, 0);
        ADXSJD_SetTrapCnt(sjd, 0);
        ADXSJD_EntryTrapFunc(sjd, adxt_trap_entry_lp, adxt);
    } else {
        if (adxt->stm != 0) {
            ADXSTM_SetEos(adxt->stm, 0x7fffffff);
        }
        ADXSJD_SetTrapNumSmpl(sjd, ADXSJD_GetTotalNumSmpl(sjd));
        ADXSJD_SetTrapDtLen(sjd, 0);
        ADXSJD_SetTrapCnt(sjd, 0);
        ADXSJD_EntryTrapFunc(sjd, adxt_trap_entry_lnk, adxt);
    }
    sfreq = ADXSJD_GetSfreq(sjd);
    nch = ADXSJD_GetNumChan(sjd);
    total_nsmpl = ADXSJD_GetTotalNumSmpl(sjd);
    ADXRNA_SetBitPerSmpl(adxt->rna, ADXSJD_GetOutBps(sjd));
    ADXRNA_SetSfreq(adxt->rna, sfreq);
    ADXRNA_SetNumChan(adxt->rna, nch);
    ADXRNA_SetTotalNumSmpl(adxt->rna, total_nsmpl);
    ADXRNA_SetOutVol(adxt->rna, adxt->outvol + ADXSJD_GetDefOutVol(adxt->sjd));
    ADXT_GetFx(adxt, &fxch, &fxlev);
    if (fxch != 0 || fxlev != 0) {
        ADXT_SetFx(adxt, fxch, fxlev);
    }
    adxt_set_outpan(adxt);
    if (adxt->amp != 0) {
        ADXAMP_SetSfreq(adxt->amp, sfreq);
    }
    if (ADXSJD_GetFormat(sjd) == ADXB_FORMAT_SPSD) {
        ADXRNA_SetStmHdInfo(adxt->rna, ADXSJD_GetSpsdInfo(sjd));
    }
    ADXRNA_SetTransSw(adxt->rna, 1);
    if (adxt_decinfo_func != 0) {
        adxt_decinfo_func(adxt, sfreq, nch, total_nsmpl);
    }
    adxt->stat = ADXT_STAT_PREP;
}
