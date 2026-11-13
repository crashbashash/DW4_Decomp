#include "dw4/cri/sfdsj.h"

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

extern char E02080805_ADXT_Destroy_parameter_error[];

void ADXERR_CallErrFunc1(const char *message);
void ADXT_DetachAhx(void);
void ADXT_DetachMpa(AdxtObj *adxt);
void ADXT_DetachPl2(AdxtObj *adxt);
void ADXT_Stop(AdxtObj *adxt);
void ADXRNA_Destroy(AdxRna *rna);
void ADXSJD_Destroy(AdxSjdObj *sjd);
void ADXSTM_EntryEosFunc(AdxStmObj *stm, void (*func)(void *obj), void *obj);
void ADXSTM_Destroy(AdxStmObj *stm);
void LSC_Destroy(LscObj *lsc);
void ADXAMP_Destroy(AdxAmpObj *amp);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void *memset(void *, int, unsigned int);

void ADXT_Destroy(AdxtObj *adxt)
{
    AdxStmObj *stm;
    int i;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080805_ADXT_Destroy_parameter_error);
        return;
    }
    ADXT_DetachAhx();
    ADXT_DetachMpa(adxt);
    ADXT_DetachPl2(adxt);
    if (adxt->used == 1) {
        ADXT_Stop(adxt);
    }
    if (adxt->rna != 0) {
        AdxRna *rna = adxt->rna;
        adxt->rna = 0;
        ADXRNA_Destroy(rna);
    }
    if (adxt->sjd != 0) {
        AdxSjdObj *sjd = adxt->sjd;
        adxt->sjd = 0;
        ADXSJD_Destroy(sjd);
    }
    if ((stm = adxt->stm) != 0) {
        adxt->stm = 0;
        ADXSTM_EntryEosFunc(stm, 0, 0);
        ADXSTM_Destroy(stm);
    }
    if (adxt->lsc != 0) {
        LscObj *lsc = adxt->lsc;
        adxt->lsc = 0;
        LSC_Destroy(lsc);
    }
    ADXCRS_Lock();
    if (adxt->sjf != 0) {
        SfdSj *sj = adxt->sjf;
        adxt->sjf = 0;
        sj->vtbl->destroy(sj);
    }
    for (i = 0; i < adxt->maxnch; i++) {
        if (adxt->sjo[i] != 0) {
            SfdSj *sj = adxt->sjo[i];
            adxt->sjo[i] = 0;
            sj->vtbl->destroy(sj);
        }
        if (adxt->ampsji[i] != 0) {
            SfdSj *sj = adxt->ampsji[i];
            adxt->ampsji[i] = 0;
            sj->vtbl->destroy(sj);
        }
        if (adxt->ampsjo[i] != 0) {
            SfdSj *sj = adxt->ampsjo[i];
            adxt->ampsjo[i] = 0;
            sj->vtbl->destroy(sj);
        }
    }
    if (adxt->amp != 0) {
        AdxAmpObj *amp = adxt->amp;
        adxt->amp = 0;
        ADXAMP_Destroy(amp);
    }
    memset(adxt, 0, sizeof(AdxtObj));
    adxt->used = 0;
    ADXCRS_Unlock();
}
