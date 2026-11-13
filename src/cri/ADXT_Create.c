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

#define ADXT_MAX_OBJ 16
#define ADXT_SCT_LEN 2048
#define ADXT_OBUF_SIZE 8192         /* bytes of output per channel */
#define ADXT_OBUF_DIST 8288         /* stride between channel buffers, ADXT_OBUF_SIZE plus the extra area */
#define ADXT_CH_WORK 16576          /* output work per channel: two ADXT_OBUF_DIST halves */
#define ADXT_IBUF_XLEN 36
#define ADXT_FNBUF_LEN 292          /* file name buffer, plus the extra area, after ibuf */

extern AdxtObj adxt_obj[ADXT_MAX_OBJ];
extern int adxt_def_svrfreq;
extern char E02080804_ADXT_Create_parameter_error[];
extern char E03100801_ADXT_Create_Too_many_handles[];

void ADXERR_CallErrFunc1(const char *message);
void *memset(void *, int, unsigned int);
SfdSj *SJRBF_Create(char *buf, int bsize, int xsize);
AdxStmObj *ADXSTM_Create(SfdSj *sj, int maxsct);
AdxSjdObj *ADXSJD_Create(SfdSj *sji, int nch, SfdSj **sjo);
AdxRna *ADXRNA_Create(SfdSj **sjo, int nch);
LscObj *LSC_Create(SfdSj *sj);
void LSC_SetStmHndl(LscObj *lsc, AdxStmObj *stm);
void ADXT_Destroy(AdxtObj *adxt);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void ADXT_SetLnkSw(AdxtObj *adxt, int sw);

/* matching construct: brute-force store-order search (AdxGrpB) — ibuf/obuf/obufsize/obufdist/ibufbsize/ibufxsize/fnbuf store order */
AdxtObj *ADXT_Create(int maxnch, char *work, int worksize)
{
    AdxtObj *adxt;
    char *buf;
    int rest;
    int i;
    int id;

    buf = (char *)(((int)work + 63) & ~63);
    rest = worksize - (buf - work);
    if (maxnch < 0 || work == 0 || worksize < 0) {
        ADXERR_CallErrFunc1(E02080804_ADXT_Create_parameter_error);
        return 0;
    }
    for (id = 0; id < ADXT_MAX_OBJ; id++) {
        if (adxt_obj[id].used == 0) {
            break;
        }
    }
    if (id == ADXT_MAX_OBJ) {
        ADXERR_CallErrFunc1(E03100801_ADXT_Create_Too_many_handles);
        return 0;
    }
    adxt = &adxt_obj[id];
    memset(adxt, 0, sizeof(AdxtObj));
    adxt->maxnch = maxnch;
    adxt->ibuf = buf + maxnch * ADXT_CH_WORK;
    adxt->obuf = buf;
    adxt->obufsize = ADXT_OBUF_SIZE;
    adxt->obufdist = ADXT_OBUF_DIST;
    adxt->ibufbsize = (rest - maxnch * ADXT_CH_WORK - ADXT_FNBUF_LEN) / ADXT_SCT_LEN * ADXT_SCT_LEN;
    adxt->ibufxsize = ADXT_IBUF_XLEN;
    adxt->fnbuf = adxt->ibuf + (adxt->ibufbsize + adxt->ibufxsize);
    adxt->sji = 0;
    adxt->sjf = SJRBF_Create(adxt->ibuf, adxt->ibufbsize, adxt->ibufxsize);
    if (adxt->sjf == 0) {
        goto fail;
    }
    adxt->stm = ADXSTM_Create(adxt->sjf, 0);
    if (adxt->stm == 0) {
        goto fail;
    }
    for (i = 0; i < maxnch; i++) {
        adxt->sjo[i] = SJRBF_Create(adxt->obuf + adxt->obufdist * i * 2, adxt->obufsize * 2,
                                    (adxt->obufdist - adxt->obufsize) * 2);
        if (adxt->sjo[i] == 0) {
            goto fail;
        }
    }
    adxt->sjd = ADXSJD_Create(adxt->sjf, maxnch, adxt->sjo);
    if (adxt->sjd == 0) {
        goto fail;
    }
    adxt->rna = ADXRNA_Create(adxt->sjo, maxnch);
    if (adxt->rna == 0) {
        goto fail;
    }
    adxt->lsc = LSC_Create(adxt->sjf);
    if (adxt->lsc == 0) {
fail:
        ADXT_Destroy(adxt);
        return 0;
    }
    LSC_SetStmHndl(adxt->lsc, adxt->stm);
    ADXCRS_Lock();
    adxt->outvol = 0;
    adxt->maxsct = adxt->ibufbsize / ADXT_SCT_LEN;
    adxt->svrfreq = adxt_def_svrfreq;
    adxt->minsct = (float)adxt->maxsct * 0.85f;
    for (i = 0; i < maxnch; i++) {
        adxt->outpan[i] = -128;
    }
    adxt->outbalance = 0;
    adxt->lpflg = 1;
    adxt->trp = 0;
    adxt->wpos = 0;
    adxt->mofst = 0;
    adxt->ercode = 0;
    adxt->edecpos = 0;
    adxt->edeccnt = 0;
    adxt->eshrtcnt = 0;
    adxt->autorcvr = 1;
    adxt->pause_flag = 0;
    adxt->time_ofst = 0;
    ADXT_SetLnkSw(adxt, 0);
    adxt->used = 1;
    ADXCRS_Unlock();
    return adxt;
}
