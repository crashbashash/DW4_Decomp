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

enum AdxtStat {
    ADXT_STAT_STOP = 0,
    ADXT_STAT_DECINFO = 1,
    ADXT_STAT_PREP = 2,
    ADXT_STAT_PLAYING = 3,
    ADXT_STAT_DECEND = 4,
    ADXT_STAT_PLAYEND = 5,
    ADXT_STAT_ERROR = 6
};

#define ADXT_TIME_RESYNC_MS 60.0f

void ADXERR_CallErrFunc1(const char *message);
void adxt_GetTimeSmpl(AdxtObj *adxt, int *ncount, int *tscale);
void adxt_IncTimeResync(void);
int ADXSJD_GetTotalNumSmpl(AdxSjdObj *sjd);
int ADXSJD_GetSfreq(AdxSjdObj *sjd);
int ADXSJD_GetOutBps(AdxSjdObj *sjd);
extern char E02080815_ADXT_GetTime_parameter_error[];
extern int adxt_time_mode;
extern int adxt_dbg_time_sw;
extern int adxt_time_unit;
extern float adxt_time_diff;
extern int adxt_vsync_cnt;

/* In a V-sync time mode the time counts V-syncs while playing, resynchronised to the sample time
 * whenever the two drift more than 60 ms apart. */
void ADXT_GetTime(AdxtObj *adxt, int *ncount, int *tscale)
{
    int nsmpl;
    int sfreq;
    int mode;
    float diff;

    if (adxt == 0 || ncount == 0 || tscale == 0) {
        ADXERR_CallErrFunc1(E02080815_ADXT_GetTime_parameter_error);
        return;
    }
    if (adxt_time_mode == 0) {
        adxt_GetTimeSmpl(adxt, ncount, tscale);
        return;
    }
    adxt_time_diff = 0;
    if (adxt->stat == ADXT_STAT_PLAYING || adxt->stat == ADXT_STAT_DECEND) {
        if (adxt->pause_flag == 0) {
            *ncount = (adxt_vsync_cnt - adxt->vbase) * 100 + adxt->vtime;
        } else {
            *ncount = adxt->vtime;
        }
        adxt_GetTimeSmpl(adxt, &nsmpl, &sfreq);
        diff = ((float)nsmpl / (float)sfreq - (float)*ncount / (float)adxt_time_unit) * 1000.0f;
        adxt_time_diff = diff;
        if (diff > ADXT_TIME_RESYNC_MS || diff < -ADXT_TIME_RESYNC_MS) {
            if (adxt_dbg_time_sw == 1) {
                mode = adxt_time_mode;
                adxt_time_mode = 0;
                ADXT_GetTime(adxt, &nsmpl, &sfreq);
                adxt_time_mode = mode;
                adxt_IncTimeResync();
            }
            adxt->vtime = (unsigned int)((float)nsmpl / (float)sfreq * (float)adxt_time_unit);
            adxt->vbase = adxt_vsync_cnt;
        }
    } else if (adxt->stat == ADXT_STAT_PLAYEND) {
        nsmpl = ADXSJD_GetTotalNumSmpl(adxt->sjd);
        sfreq = ADXSJD_GetSfreq(adxt->sjd);
        nsmpl *= 16 / ADXSJD_GetOutBps(adxt->sjd);
        *ncount = (int)((float)nsmpl / (float)sfreq * (float)adxt_time_unit);
        /* matching construct: hand search — the unsigned add keeps gcc from reassociating the + 1 */
        *ncount = (unsigned int)*ncount + (adxt->vtime + 1);
    } else {
        *ncount = 0;
    }
    *ncount += adxt->time_ofst;
    *tscale = adxt_time_unit;
}
