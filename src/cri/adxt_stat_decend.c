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

enum { SJ_LIN_FREE = 0, SJ_LIN_DATA = 1 };
enum { ADXT_STAT_PLAYEND = 5 };

extern int adxt_eos_rna_ndata;
void *memset(void *, int, unsigned int);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void ADXRNA_SetTransSw(AdxRna *rna, int sw);
void ADXRNA_SetPlaySw(AdxRna *rna, int sw);
int ADXRNA_GetNumData(AdxRna *rna);
int ADXSJD_GetNumChan(AdxSjdObj *sjd);
void PS2RNA_SetStopFlag(AdxRna *rna, int sw);
void SJ_SplitChunk(SfdSjChunk *ck, int len, SfdSjChunk *head, SfdSjChunk *rest);

/* State DECEND: pads every output channel with silence up to one decode step, and stops the
 * renderer (state PLAYEND) once all queued samples have been played. */
void adxt_stat_decend(AdxtObj *adxt)
{
    SfdSjChunk ck[2];
    SfdSjChunk rest[2];
    int nch;
    int i;
    unsigned int nsmpl;
    unsigned int n;
    int nmax;
    int m;

    adxt_eos_rna_ndata = ADXRNA_GetNumData(adxt->rna);
    nch = ADXSJD_GetNumChan(adxt->sjd);
    ADXCRS_Lock();
    nsmpl = adxt->maxdecsmpl;
    for (i = 0; i < nch; i++) {
        adxt->sjo[i]->vtbl->getChunk(adxt->sjo[i], SJ_LIN_FREE, nsmpl * 2, &ck[i]);
        n = (unsigned int)ck[i].len >> 1;
        if (n < nsmpl) {
            nsmpl = n;
        }
    }
    for (i = 0; i < nch; i++) {
        SJ_SplitChunk(&ck[i], nsmpl * 2, &ck[i], &rest[i]);
        memset(ck[i].data, 0, ck[i].len);
        adxt->sjo[i]->vtbl->putChunk(adxt->sjo[i], SJ_LIN_DATA, &ck[i]);
        adxt->sjo[i]->vtbl->ungetChunk(adxt->sjo[i], SJ_LIN_FREE, &rest[i]);
    }
    nmax = 0;
    adxt->pad_nsmpl += nsmpl;
    ADXCRS_Unlock();
    for (i = 0; i < nch; i++) {
        m = (unsigned int)adxt->sjo[i]->vtbl->getNumData(adxt->sjo[i], SJ_LIN_DATA) >> 1;
        if (m >= nmax) {
            nmax = m;
        }
    }
    if (nmax + ADXRNA_GetNumData(adxt->rna) - adxt->pad_nsmpl <= 0) {
        ADXRNA_SetTransSw(adxt->rna, 0);
        ADXRNA_SetPlaySw(adxt->rna, 0);
        PS2RNA_SetStopFlag(adxt->rna, 1);
        adxt->stat = ADXT_STAT_PLAYEND;
    }
}
