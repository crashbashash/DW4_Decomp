/* CRI ADXT: creating and destroying playback handles, starting and stopping them, and their settings. */
#include "dw4/cri/adxt.h"

#define ADXT_OBUF_SIZE 8192         /* bytes of output per channel */
#define ADXT_OBUF_DIST 8288         /* stride between channel buffers, ADXT_OBUF_SIZE plus the extra area */
#define ADXT_CH_WORK 16576          /* output work per channel: two ADXT_OBUF_DIST halves */
#define ADXT_IBUF_XLEN 36
#define ADXT_FNBUF_LEN 292          /* file name buffer, plus the extra area, after ibuf */
#define ADXT_PL2_WORK 1024          /* Pro Logic II work ahead of a handle's own work */
#define ADXT_TIME_RESYNC_MS 60.0f
#define ADXT_MEM_SIZE 0x40000000    /* an in-memory stream of unknown length */

#define BSWAP32(x) ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) << 8) & 0xff0000) | ((x) << 24))

enum AdxtTmode {
    ADXT_TMODE_STD = 0,     /* time from decoded samples */
    ADXT_TMODE_NTSC = 1,
    ADXT_TMODE_PAL = 2
};

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

typedef void (*AdxtHookFunc)(AdxtObj *adxt);
typedef void (*AdxtFltFunc)(void *obj, int ch, char *data, int len);
typedef void (*AdxtDecFunc)(void *obj, int nsmpl, int nbyte);
typedef void (*AdxtErrFunc)(void *obj, char *message);

extern int adxt_output_mono;
extern int adxt_stm_eos;
extern int adxt_time_mode;
/* The server's phase: 0 idle, 1 entered, 2 handles, 3 renderer; read and written through a full address. */
extern volatile int adxt_svr_phase;
extern int adxt_def_svrfreq;
extern int adxt_svrfreq;
extern AdxtHookFunc adxt_detach_ahx;
extern AdxtHookFunc adxt_detach_mpa;
extern AdxtHookFunc adxt_stop_func;
extern AdxtHookFunc adxt_detach_pl2;
extern int adxt_time_resync_cnt;
extern int adxt_dbg_time_sw;
extern int adxt_time_unit;  /* V-syncs per 100 seconds */
extern float adxt_time_diff;
extern char adxt_hdr_dataid[];

extern char ntmp0_4d_ntmp2_4d_sum_4d[];
extern char niop0_4d_niop2_4d_sum_4d[];
extern char stat_4d_ttl_4d[];
extern char E02080804_ADXT_Create_parameter_error[];
extern char E03100801_ADXT_Create_Too_many_handles[];
extern char E02080805_ADXT_Destroy_parameter_error[];
extern char E02080812_ADXT_StartSj_parameter_error[];
extern char E02080813_ADXT_Stop_parameter_error[];
extern char E02080814_ADXT_GetStat_parameter_error[];
extern char E02080815_ADXT_GetTime_parameter_error[];
extern char E02080817_ADXT_GetNumSmpl_parameter_error[];
extern char E02080819_ADXT_GetSfreq_parameter_error[];
extern char E02080820_ADXT_GetNumChan_parameter_error[];
extern char E02080822_ADXT_GetHdrLen_parameter_error[];
extern char E02080821_ADXT_GetFmtBps_parameter_error[];
extern char E02080825_ADXT_SetOutPan_parameter_error[];
extern char E8101208_ADXT_SetOutPan_parameter_error[];
extern char E02080826_ADXT_GetOutPan_parameter_error[];
extern char E02080870_ADXT_SetOutBalance_parameter_error[];
extern char E02080871_ADXT_GetOutBalance_parameter_error[];
extern char E02080823_ADXT_SetOutVol_parameter_error[];
extern char E02080824_ADXT_GetOutVol_parameter_error[];
extern char E02080840_ADXT_SetSvrFreq_parameter_error[];
extern char E02080838_ADXT_SetReloadTime_parameter_error[];
extern char E03111501_ADXT_ResetReloadTime_parameter_error[];
extern char E02080839_ADXT_SetReloadSct_parameter_error[];
extern char E02080834_ADXT_GetNumSctIbuf_parameter_error[];
extern char E02080837_ADXT_GetNumSmplObuf_parameter_error[];
extern char E02080835_ADXT_GetIbufRemainTime_parameter_error[];
extern char E02080836_ADXT_IsIbufSafety_parameter_error[];
extern char E02080802_ADXT_IsCompleted_parameter_error[];
extern char E02080843_ADXT_GetErrCode_parameter_error[];
extern char E02080844_ADXT_ClearErrCode_parameter_error[];
extern char E02080829_ADXT_GetLpCnt_parameter_error[];
extern char E02080828_ADXT_SetLpFlg_parameter_error[];
extern char E02080833_ADXT_GetInputSj_parameter_error[];
extern char E02080830_ADXT_SetWaitPlayStart_parameter_error[];
extern char E02080831_ADXT_IsReadyPlayStart_parameter_error[];
extern char E02080846_ADXT_Pause_parameter_error[];
extern char E02080847_ADXT_GetStatPause_parameter_error[];
extern char E02080818_ADXT_GetDecNumSmpl_parameter_error[];
extern char E04041901_ADXT_GetDecDtLen_parameter_error[];
extern char E02080860_ADXT_SetKeyString_parameter_error[];
extern char E02080811_ADXT_StartAfs_parameter_error[];
extern char E8101202_ADXT_StartAfs_can_t_open[];
extern char E02080807_ADXT_StartFnameRange_parameter_error[];
extern char E02080809_ADXT_StartMem2_parameter_error[];
extern char E8101207_can_t_create_sj_ADXT_StartMem[];
extern char E02080810_ADXT_StartMemIdx_parameter_error[];
extern char E8101207_can_t_create_sj_ADXT_StartMemIdx[];

void scePrintf(const char *format, ...);
char *strcpy(char *dst, const char *src);
SfdSj *PS2RNA_GetSjUni(AdxRna *rna, int ch);
int PS2RNA_GetSjRmt(AdxRna *rna, int ch);
int SJRMT_GetNumData(int sjrmt, int line);
SfdSj *SJRBF_Create(char *buf, int bsize, int xsize);
SfdSj *SJMEM_Create(char *buf, int size);
AdxStmObj *ADXSTM_Create(SfdSj *sj, int maxsct);
void ADXSTM_Destroy(AdxStmObj *stm);
void ADXSTM_BindFileNw(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct);
void ADXSTM_ReleaseFileNw(AdxStmObj *stm);
void ADXSTM_StopNw(AdxStmObj *stm);
int ADXSTM_SetBufSize(AdxStmObj *stm, int min, int max);
AdxSjdObj *ADXSJD_Create(SfdSj *sji, int nch, SfdSj **sjo);
void ADXSJD_Destroy(AdxSjdObj *sjd);
int ADXSJD_GetHdrLen(AdxSjdObj *sjd);
int ADXSJD_GetFmtBps(AdxSjdObj *sjd);
short ADXSJD_GetDefPan(AdxSjdObj *sjd, int ch);
char *ADXSJD_GetDataId(AdxSjdObj *sjd);
int ADXSJD_GetDecDtLen(AdxSjdObj *sjd);
void ADXSJD_EntryDecFunc(AdxSjdObj *sjd, AdxtDecFunc func, void *obj);
void ADXSJD_SetLnkSw(AdxSjdObj *sjd, int sw);
void ADXSJD_SetKeyString(AdxSjdObj *sjd, char *str);
void ADXSJD_SetDefKeyString(char *str);
void ADXSJD_ResetDefFmt(AdxSjdObj *sjd);
int ADXSJD_AdjustSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_EntryFltFunc(AdxSjdObj *sjd, AdxtFltFunc func, void *obj);
void ADXSJD_ExecServer(void);
AdxRna *ADXRNA_Create(SfdSj **sjo, int nch);
void ADXRNA_Destroy(AdxRna *rna);
void ADXRNA_GetTime(AdxRna *rna, int *ncount, int *tscale);
void ADXRNA_ExecServer(void);
void ADXRNA_SetOutPan(AdxRna *rna, int ch, int pan);
void ADXRNA_SetOutBalance(AdxRna *rna, int balance);
int ADXRNA_DiscardData(AdxRna *rna, int nsmpl);
void ADXRNA_SetOutMode(int mode);
int ADXRNA_GetOutMode(void);
void ADXAMP_Destroy(AdxAmpObj *amp);
void ADXAMP_Start(AdxAmpObj *amp);
void ADXAMP_Stop(AdxAmpObj *amp);
LscObj *LSC_Create(SfdSj *sj);
void LSC_Destroy(LscObj *lsc);
void LSC_SetStmHndl(LscObj *lsc, AdxStmObj *stm);
void LSC_Stop(LscObj *lsc);
void ADXERR_EntryErrFunc(AdxtErrFunc func, void *obj);
int ADXF_GetFnameRangeEx(int ptid, int flid, char *fname, void **dir, int *ofst, int *nsct);
int ADX_DecodeInfoAinf(unsigned char *hdr, int size, int *ainfsiz, char *dataid, short *volume, short *pan);
int ADX_DecodeHeader(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize,
                     signed char *bits, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl);
void ADXT_AttachPl2(AdxtObj *adxt, char *work, int worksize);

AdxtObj *ADXT_Create(int maxnch, char *work, int worksize);
void ADXT_Destroy(AdxtObj *adxt);
void ADXT_GetTime(AdxtObj *adxt, int *ncount, int *tscale);
int ADXT_GetSfreq(AdxtObj *adxt);
int ADXT_GetNumSmplObuf(AdxtObj *adxt, int ch);
void ADXT_ExecServer(void);

/* Prints how much of channel 0's output sits in the EE-side SJ and in the IOP-side SJ. */
void ADXT_DumpBufStat(AdxtObj *adxt)
{
    AdxRna *rna = adxt->rna;
    int sjrmt = PS2RNA_GetSjRmt(rna, 0);
    SfdSj *sjuni = PS2RNA_GetSjUni(rna, 0);
    int ntmp1 = sjuni->vtbl->getNumData(sjuni, SJ_LIN_DATA);
    int ntmp0 = sjuni->vtbl->getNumData(sjuni, SJ_LIN_FREE);
    int niop1 = SJRMT_GetNumData(sjrmt, SJ_LIN_DATA);
    int niop0 = SJRMT_GetNumData(sjrmt, SJ_LIN_FREE);

    scePrintf(ntmp0_4d_ntmp2_4d_sum_4d, ntmp1, ntmp0, ntmp1 + ntmp0);
    scePrintf(niop0_4d_niop2_4d_sum_4d, niop1, niop0, niop1 + niop0);
    scePrintf(stat_4d_ttl_4d, adxt->stat, ntmp1 + ntmp0 + niop1 + niop0);
}

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
    adxt->ercode = ADXT_ERR_OK;
    adxt->edecpos = 0;
    adxt->edeccnt = 0;
    adxt->eshrtcnt = 0;
    adxt->autorcvr = ADXT_RMODE_STOP;
    adxt->pause_flag = 0;
    adxt->time_ofst = 0;
    ADXT_SetLnkSw(adxt, 0);
    adxt->used = 1;
    ADXCRS_Unlock();
    return adxt;
}

/* A stereo handle with Dolby Pro Logic II attached, its work at the head of the buffer. */
AdxtObj *ADXT_CreatePl2(char *work, int worksize)
{
    AdxtObj *adxt = ADXT_Create(2, work + ADXT_PL2_WORK, worksize - ADXT_PL2_WORK);

    if (adxt == 0) {
        return 0;
    }
    ADXT_AttachPl2(adxt, work, ADXT_PL2_WORK);
    return adxt;
}

void ADXT_DetachAhx(AdxtObj *adxt)
{
    if (adxt_detach_ahx != 0) {
        adxt_detach_ahx(adxt);
    }
}

void ADXT_DetachMpa(AdxtObj *adxt)
{
    if (adxt_detach_mpa != 0) {
        adxt_detach_mpa(adxt);
    }
}

void ADXT_DetachPl2(AdxtObj *adxt)
{
    if (adxt_detach_pl2 != 0) {
        adxt_detach_pl2(adxt);
    }
}

void ADXT_Destroy(AdxtObj *adxt)
{
    AdxStmObj *stm;
    int i;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080805_ADXT_Destroy_parameter_error);
        return;
    }
    ADXT_DetachAhx(adxt);
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

void ADXT_DestroyAll(void)
{
    AdxtObj *adxt = adxt_obj;
    int i;

    for (i = ADXT_MAX_OBJ - 1; i >= 0; i--, adxt++) {
        if (adxt->used == 1) {
            ADXT_Destroy(adxt);
        }
    }
}

void ADXT_CloseAllHandles(void)
{
    ADXT_DestroyAll();
}

/* Starts decoding from an input SJ: clears the outputs and the playback counters. */
void adxt_start_sj(AdxtObj *adxt, SfdSj *sji)
{
    int i;

    for (i = 0; i < adxt->maxnch; i++) {
        adxt->sjo[i]->vtbl->reset(adxt->sjo[i]);
    }
    ADXSJD_SetInSj(adxt->sjd, sji);
    adxt->sji = sji;
    ADXSJD_Start(adxt->sjd);
    /* matching construct: statement-order sweep — lesct is written before trpnsmpl */
    adxt->stat = ADXT_STAT_DECINFO;
    adxt->lesct = 0x7fffffff;
    adxt->trpnsmpl = -1;
    adxt->lpcnt = 0;
    adxt->pstready_flag = 0;
    adxt->vtime = 0;
    adxt->decofst = 0;
    adxt->vbase = adxt_vsync_cnt;
    if (adxt->amp != 0) {
        ADXAMP_Start(adxt->amp);
    }
}

/* Opens a file range on the handle's stream and starts decoding from the ring buffer it fills. */
void adxt_start_stm(AdxtObj *adxt, char *fname, void *dir, int ofst, int nsct)
{
    ADXSTM_SetBufSize(adxt->stm, adxt->minsct * ADXT_SCT_LEN, adxt->maxsct * ADXT_SCT_LEN);
    ADXSTM_SetEos(adxt->stm, adxt_stm_eos);
    ADXSTM_EntryEosFunc(adxt->stm, 0, 0);
    ADXSTM_Seek(adxt->stm, 0);
    ADXSTM_StopNw(adxt->stm);
    ADXSTM_ReleaseFileNw(adxt->stm);
    ADXSTM_BindFileNw(adxt->stm, fname, dir, ofst, nsct);
    ADXSTM_Start(adxt->stm);
    adxt_start_sj(adxt, adxt->sjf);
}

void ADXT_StartSj(AdxtObj *adxt, SfdSj *sj)
{
    if (adxt == 0 || sj == 0) {
        ADXERR_CallErrFunc1(E02080812_ADXT_StartSj_parameter_error);
        return;
    }
    ADXT_Stop(adxt);
    ADXCRS_Lock();
    adxt_start_sj(adxt, sj);
    adxt->pmode = ADXT_PMODE_SJ;
    ADXT_SetLnkSw(adxt, 1);
    ADXCRS_Unlock();
}

/* Stops the renderer and the decoder, leaving a seamless file list to the caller. */
void ADXT_StopWithoutLsc(AdxtObj *adxt)
{
    SfdSj *sji;

    ADXCRS_Lock();
    ADXRNA_SetTransSw(adxt->rna, 0);
    ADXRNA_SetPlaySw(adxt->rna, 0);
    PS2RNA_SetStopFlag(adxt->rna, 1);
    ADXSJD_Stop(adxt->sjd);
    if (adxt->pmode == ADXT_PMODE_MEM) {
        sji = adxt->sji;
        if (sji != 0) {
            adxt->sji = 0;
            sji->vtbl->destroy(sji);
        }
    }
    if (adxt->amp != 0) {
        ADXAMP_Stop(adxt->amp);
    }
    adxt->sji = 0;
    adxt->stat = ADXT_STAT_STOP;
    adxt->stm_req = 0;
    ADXCRS_Unlock();
}

void ADXT_Stop(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080813_ADXT_Stop_parameter_error);
        return;
    }
    if (adxt_stop_func != 0) {
        ADXSJD_Stop(adxt->sjd);
        adxt_stop_func(adxt);
    }
    if (adxt->stm != 0) {
        ADXSTM_ReleaseFileNw(adxt->stm);
    }
    if (adxt->pmode == ADXT_PMODE_SLFILE) {
        LSC_Stop(adxt->lsc);
        if (adxt->sji != 0) {
            adxt->sji->vtbl->reset(adxt->sji);
        }
    }
    ADXT_StopWithoutLsc(adxt);
}

int ADXT_GetStat(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080814_ADXT_GetStat_parameter_error);
        return -1;
    }
    return adxt->stat;
}

void ADXT_SetTimeMode(int mode)
{
    if (mode == ADXT_TMODE_NTSC) {
        adxt_time_unit = 5994;
    } else if (mode == ADXT_TMODE_PAL) {
        adxt_time_unit = 5000;
    }
    adxt_time_mode = mode;
}

/* The time the renderer has played, as a sample count and a rate. */
void ADXT_GetTimeRna(AdxtObj *adxt, int *ncount, int *tscale)
{
    if (adxt->stat == ADXT_STAT_PLAYING || adxt->stat == ADXT_STAT_DECEND) {
        ADXRNA_GetTime(adxt->rna, ncount, tscale);
    } else if (adxt->stat == ADXT_STAT_PLAYEND) {
        *ncount = ADXSJD_GetTotalNumSmpl(adxt->sjd);
        *tscale = ADXSJD_GetSfreq(adxt->sjd);
        *ncount *= 16 / ADXSJD_GetOutBps(adxt->sjd);
    } else {
        *ncount = 0;
        *tscale = 1;
    }
    *ncount += adxt->time_ofst;
}

/* The time played, from the decoded samples less those still queued for the renderer. */
void adxt_GetTimeSmpl(AdxtObj *adxt, int *ncount, int *tscale)
{
    int ndec;
    int nrna;

    if (adxt->stat == ADXT_STAT_PLAYING || adxt->stat == ADXT_STAT_DECEND) {
        *tscale = ADXSJD_GetSfreq(adxt->sjd);
        ndec = ADXSJD_GetDecNumSmpl(adxt->sjd);
        nrna = ADXRNA_GetNumData(adxt->rna);
        *ncount = ndec - (nrna - adxt->pad_nsmpl + ADXT_GetNumSmplObuf(adxt, 0)) + adxt->decofst;
    } else if (adxt->stat == ADXT_STAT_PLAYEND) {
        *ncount = ADXSJD_GetTotalNumSmpl(adxt->sjd);
        *tscale = ADXSJD_GetSfreq(adxt->sjd);
        *ncount *= 16 / ADXSJD_GetOutBps(adxt->sjd);
        *ncount += adxt->decofst;
    } else {
        *ncount = 0;
        *tscale = 1;
    }
    *ncount += adxt->time_ofst;
}

void adxt_IncTimeResync(void)
{
    adxt_time_resync_cnt++;
}

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
    if (adxt_time_mode == ADXT_TMODE_STD) {
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
                adxt_time_mode = ADXT_TMODE_STD;
                ADXT_GetTime(adxt, &nsmpl, &sfreq);
                adxt_time_mode = mode;
                adxt_IncTimeResync();
            }
            adxt->vtime = (float)nsmpl / (float)sfreq * (float)adxt_time_unit;
            adxt->vbase = adxt_vsync_cnt;
        }
    } else if (adxt->stat == ADXT_STAT_PLAYEND) {
        nsmpl = ADXSJD_GetTotalNumSmpl(adxt->sjd);
        sfreq = ADXSJD_GetSfreq(adxt->sjd);
        nsmpl *= 16 / ADXSJD_GetOutBps(adxt->sjd);
        *ncount = (int)((float)nsmpl / (float)sfreq * (float)adxt_time_unit);
        *ncount += (int)(adxt->vtime + 1);
    } else {
        *ncount = 0;
    }
    *ncount += adxt->time_ofst;
    *tscale = adxt_time_unit;
}

/* The time played in hundredths of a second. */
int ADXT_GetTimeReal(AdxtObj *adxt)
{
    int ncount;
    int tscale;

    ADXT_GetTime(adxt, &ncount, &tscale);
    return (float)ncount / (float)tscale * 100.0f;
}

int ADXT_GetNumSmpl(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080817_ADXT_GetNumSmpl_parameter_error);
        return -1;
    }
    if (adxt->stat >= ADXT_STAT_PREP) {
        return ADXSJD_GetTotalNumSmpl(adxt->sjd);
    }
    return 0;
}

int ADXT_GetSfreq(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080819_ADXT_GetSfreq_parameter_error);
        return -1;
    }
    if (adxt->stat >= ADXT_STAT_PREP) {
        return ADXSJD_GetSfreq(adxt->sjd);
    }
    return 0;
}

int ADXT_GetNumChan(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080820_ADXT_GetNumChan_parameter_error);
        return -1;
    }
    if (adxt->stat >= ADXT_STAT_PREP) {
        return ADXSJD_GetNumChan(adxt->sjd);
    }
    return 0;
}

int ADXT_GetHdrLen(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080822_ADXT_GetHdrLen_parameter_error);
        return -1;
    }
    if (adxt->stat >= ADXT_STAT_PREP) {
        return ADXSJD_GetHdrLen(adxt->sjd);
    }
    return 0;
}

int ADXT_GetFmtBps(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080821_ADXT_GetFmtBps_parameter_error);
        return -1;
    }
    if (adxt->stat >= ADXT_STAT_PREP) {
        return ADXSJD_GetFmtBps(adxt->sjd);
    }
    return 0;
}

/* -128 asks for the header's pan; a stereo stream then puts its channels 15 to either side. */
void ADXT_SetOutPan(AdxtObj *adxt, int ch, int pan)
{
    int defpan;
    int outpan;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080825_ADXT_SetOutPan_parameter_error);
        return;
    }
    defpan = ADXSJD_GetDefPan(adxt->sjd, ch);
    if (defpan == -128) {
        defpan = 0;
    }
    if (adxt_output_mono != 0) {
        outpan = 0;
    } else {
        if (pan == -128) {
            if (ADXSJD_GetNumChan(adxt->sjd) == 2) {
                outpan = (ch == 0) ? -15 : 15;
            } else {
                outpan = 0;
            }
            outpan += defpan;
        } else {
            outpan = pan + defpan;
        }
    }
    adxt->outpan[ch] = pan;
    if (ch < adxt->maxnch) {
        ADXRNA_SetOutPan(adxt->rna, ch, outpan);
    } else {
        ADXERR_CallErrFunc1(E8101208_ADXT_SetOutPan_parameter_error);
    }
}

int ADXT_GetOutPan(AdxtObj *adxt, int ch)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080826_ADXT_GetOutPan_parameter_error);
        return 0;
    }
    return adxt->outpan[ch];
}

void ADXT_SetOutBalance(AdxtObj *adxt, int balance)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080870_ADXT_SetOutBalance_parameter_error);
        return;
    }
    if (balance < -15) {
        adxt->outbalance = -15;
    } else if (balance >= 16) {
        adxt->outbalance = 15;
    } else {
        adxt->outbalance = balance;
    }
    if (adxt_output_mono == 0) {
        ADXRNA_SetOutBalance(adxt->rna, adxt->outbalance);
    } else {
        ADXRNA_SetOutBalance(adxt->rna, -128);
    }
}

int ADXT_GetOutBalance(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080871_ADXT_GetOutBalance_parameter_error);
        return 0;
    }
    return adxt->outbalance;
}

/* The volume is relative to the one the header asks for. */
void ADXT_SetOutVol(AdxtObj *adxt, int vol)
{
    AdxRna *rna;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080823_ADXT_SetOutVol_parameter_error);
        return;
    }
    adxt->outvol = vol;
    rna = adxt->rna;
    ADXRNA_SetOutVol(rna, adxt->outvol + ADXSJD_GetDefOutVol(adxt->sjd));
}

int ADXT_GetOutVol(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080824_ADXT_GetOutVol_parameter_error);
        return 0;
    }
    return adxt->outvol;
}

short ADXT_GetDefOutVol(AdxtObj *adxt)
{
    return ADXSJD_GetDefOutVol(adxt->sjd);
}

short ADXT_GetDefPan(AdxtObj *adxt, int ch)
{
    return ADXSJD_GetDefPan(adxt->sjd, ch);
}

char *ADXT_GetDataId(AdxtObj *adxt)
{
    return ADXSJD_GetDataId(adxt->sjd);
}

/* The 16-byte data id of an ADX header's AINF block, or 0 when the header has none. */
char *ADXT_GetHdrDataId(unsigned char *hdr)
{
    short pan[8];
    struct {
        short volume;
        int ainfsiz;
    } ainf;

    ADX_DecodeInfoAinf(hdr, ADXT_SCT_LEN, &ainf.ainfsiz, adxt_hdr_dataid, &ainf.volume, pan);
    return (ainf.ainfsiz != 0) ? adxt_hdr_dataid : 0;
}

void ADXT_SetDefSvrFreq(int freq)
{
    adxt_def_svrfreq = freq;
    adxt_svrfreq = freq;
}

void ADXT_SetSvrFreq(AdxtObj *adxt, int freq)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080840_ADXT_SetSvrFreq_parameter_error);
        return;
    }
    adxt->svrfreq = freq;
    adxt_svrfreq = freq;
}

/* Reloads once the input buffer holds `time` seconds of ADX data (18-byte frames of 32 samples). */
void ADXT_SetReloadTime(AdxtObj *adxt, float time, int nch, int sfreq)
{
    int nsct;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080838_ADXT_SetReloadTime_parameter_error);
        return;
    }
    nsct = (int)(time * (float)sfreq) / 32 * nch * 18 / ADXT_SCT_LEN;
    adxt->minsct = nsct < adxt->maxsct ? nsct : adxt->maxsct;
    if (adxt->stm != 0) {
        ADXSTM_SetBufSize(adxt->stm, adxt->minsct << 11, adxt->maxsct << 11);
    }
}

void ADXT_ResetReloadTime(AdxtObj *adxt)
{
    short maxsct;
    AdxStmObj *stm;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E03111501_ADXT_ResetReloadTime_parameter_error);
        return;
    }
    maxsct = adxt->maxsct;
    stm = adxt->stm;
    /* The constant is 0x3F599999, one ulp below 0.85f: it is folded from 1.0f - 0.15f. */
    adxt->minsct = maxsct * (1.0f - 0.15f);
    if (stm != 0) {
        ADXSTM_SetBufSize(stm, adxt->minsct << 11, maxsct << 11);
    }
}

/* matching construct: int parameter — retail narrows the 16-bit count only where it is scaled, not on entry */
void ADXT_SetReloadSct(AdxtObj *adxt, int minsct)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080839_ADXT_SetReloadSct_parameter_error);
        return;
    }
    adxt->minsct = minsct;
    if (adxt->stm != 0) {
        ADXSTM_SetBufSize(adxt->stm, (short)minsct * ADXT_SCT_LEN, adxt->maxsct * ADXT_SCT_LEN);
    }
}

short ADXT_GetReloadSct(AdxtObj *adxt)
{
    return adxt->minsct;
}

int ADXT_GetNumSctIbuf(AdxtObj *adxt)
{
    SfdSj *sji;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080834_ADXT_GetNumSctIbuf_parameter_error);
        return -1;
    }
    sji = adxt->sji;
    if (sji != 0) {
        return sji->vtbl->getNumData(sji, SJ_LIN_DATA) / ADXT_SCT_LEN;
    }
    return 0;
}

int ADXT_GetNumSmplObuf(AdxtObj *adxt, int ch)
{
    SfdSj *sjo;

    if (adxt == 0 || ch < 0) {
        ADXERR_CallErrFunc1(E02080837_ADXT_GetNumSmplObuf_parameter_error);
        return -1;
    }
    sjo = adxt->sjo[ch];
    if (sjo != 0) {
        return sjo->vtbl->getNumData(sjo, SJ_LIN_DATA) / 2;
    }
    return 0;
}

/* Seconds of sound the input buffer holds. */
float ADXT_GetIbufRemainTime(AdxtObj *adxt)
{
    float time;
    int nbyte;
    int nch;

    time = 0.0f;
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080835_ADXT_GetIbufRemainTime_parameter_error);
        return -1.0f;
    }
    if (ADXT_GetStat(adxt) >= ADXT_STAT_PREP && adxt->sji != 0) {
        nbyte = adxt->sji->vtbl->getNumData(adxt->sji, SJ_LIN_DATA);
        nch = ADXT_GetNumChan(adxt);
        time = (float)(nbyte / (nch * 18) * 32) / (float)ADXT_GetSfreq(adxt);
    }
    return time;
}

/* Whether the input buffer holds at least the reload size. */
int ADXT_IsIbufSafety(AdxtObj *adxt)
{
    SfdSj *sji;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080836_ADXT_IsIbufSafety_parameter_error);
        return -1;
    }
    sji = adxt->sji;
    if (sji != 0) {
        if (sji->vtbl->getNumData(sji, SJ_LIN_DATA) < adxt->minsct << 11) {
            return 0;
        }
        return 1;
    }
    return 0;
}

void ADXT_SetAutoRcvr(AdxtObj *adxt, int rmode)
{
    adxt->autorcvr = rmode;
}

int ADXT_IsCompleted(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080802_ADXT_IsCompleted_parameter_error);
        return -1;
    }
    return adxt->stat == ADXT_STAT_PLAYEND;
}

/* One server pass over every handle, guarded against re-entry; the renderer runs twice below 51 calls a second. */
void ADXT_ExecServer(void)
{
    int i;

    ADXCRS_Lock();
    if (adxt_svr_phase != 0) {
        ADXCRS_Unlock();
        return;
    }
    adxt_svr_phase = 1;
    ADXCRS_Unlock();
    ADXCRS_Lock();
    ADXSJD_ExecServer();
    adxt_svr_phase = 2;
    for (i = 0; i < ADXT_MAX_OBJ; i++) {
        if (adxt_obj[i].used == 1) {
            ADXT_ExecHndl(&adxt_obj[i]);
        }
    }
    adxt_svr_phase = 3;
    ADXRNA_ExecServer();
    if (adxt_svrfreq < 51) {
        ADXRNA_ExecServer();
    }
    adxt_svr_phase = 0;
    ADXCRS_Unlock();
}

void ADXT_ExecSvr(void)
{
    ADXT_ExecServer();
}

int ADXT_GetErrCode(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080843_ADXT_GetErrCode_parameter_error);
        return -1;
    }
    return adxt->ercode;
}

void ADXT_ClearErrCode(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080844_ADXT_ClearErrCode_parameter_error);
        return;
    }
    adxt->ercode = ADXT_ERR_OK;
    adxt->edecpos = 0;
    adxt->edeccnt = 0;
    adxt->eshrtcnt = 0;
}

int ADXT_GetLpCnt(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080829_ADXT_GetLpCnt_parameter_error);
        return -1;
    }
    return adxt->lpcnt;
}

void ADXT_SetLpFlg(AdxtObj *adxt, int flg)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080828_ADXT_SetLpFlg_parameter_error);
        return;
    }
    adxt->lpflg = flg;
}

SfdSj *ADXT_GetInputSj(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080833_ADXT_GetInputSj_parameter_error);
        return 0;
    }
    return adxt->sji;
}

void ADXT_SetWaitPlayStart(AdxtObj *adxt, int flg)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080830_ADXT_SetWaitPlayStart_parameter_error);
        return;
    }
    adxt->pstwait_flag = flg;
}

int ADXT_IsReadyPlayStart(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080831_ADXT_IsReadyPlayStart_parameter_error);
        return -1;
    }
    return adxt->pstready_flag;
}

/* Pausing stops the renderer and keeps the V-sync time where it stood. */
void ADXT_Pause(AdxtObj *adxt, int sw)
{
    int stat;
    int mode;
    int ncount;
    int tscale;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080846_ADXT_Pause_parameter_error);
        return;
    }
    stat = adxt->stat;
    if (sw == adxt->pause_flag) {
        return;
    }
    ADXCRS_Lock();
    adxt->pause_flag = sw;
    if (stat == ADXT_STAT_PLAYING || stat == ADXT_STAT_DECEND) {
        if (sw == 1) {
            ADXRNA_SetPlaySw(adxt->rna, 0);
        } else {
            ADXRNA_SetPlaySw(adxt->rna, 1);
            adxt->vbase = adxt_vsync_cnt;
        }
        mode = adxt_time_mode;
        adxt_time_mode = ADXT_TMODE_STD;
        ADXT_GetTime(adxt, &ncount, &tscale);
        adxt_time_mode = mode;
        adxt->vtime = (float)ncount / (float)tscale * (float)adxt_time_unit;
    }
    ADXCRS_Unlock();
}

int ADXT_GetStatPause(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080847_ADXT_GetStatPause_parameter_error);
        return 0;
    }
    return adxt->pause_flag;
}

void ADXT_SetOutMode(int mode)
{
    ADXRNA_SetOutMode(mode);
}

int ADXT_GetOutMode(void)
{
    return ADXRNA_GetOutMode();
}

void ADXT_SetFx(AdxtObj *adxt, int fxch, int fxlev)
{
}

void ADXT_GetFx(AdxtObj *adxt, int *fxch, int *fxlev)
{
}

AdxStmObj *ADXT_GetStm(AdxtObj *adxt)
{
    return adxt->stm;
}

/* No more data follows what the input holds. */
void ADXT_TermSupply(AdxtObj *adxt)
{
    ADXSJD_TermSupply(adxt->sjd);
}

void ADXT_SetDrctLvl(AdxtObj *adxt, int lvl)
{
}

int ADXT_GetDrctLvl(AdxtObj *adxt)
{
    return 0;
}

void ADXT_SetFilter(AdxtObj *adxt, int coff, int q)
{
}

void ADXT_GetFilter(AdxtObj *adxt, int *coff, int *q)
{
}

void ADXT_SetSurround(AdxtObj *adxt, int sw)
{
}

void ADXT_GetSurround(AdxtObj *adxt, int *sw)
{
}

void ADXT_EntryErrFunc(AdxtErrFunc func, void *obj)
{
    ADXERR_EntryErrFunc(func, obj);
}

/* Drops queued samples from the renderer, runs a server pass and restarts the V-sync time from there. */
int ADXT_DiscardSmpl(AdxtObj *adxt, int nsmpl)
{
    int ndiscard;
    int mode;
    int ncount;
    int tscale;

    if (adxt->pause_flag == 0) {
        return 0;
    }
    ndiscard = ADXRNA_DiscardData(adxt->rna, nsmpl);
    ADXT_ExecServer();
    mode = adxt_time_mode;
    adxt_time_mode = ADXT_TMODE_STD;
    ADXT_GetTime(adxt, &ncount, &tscale);
    adxt_time_mode = mode;
    adxt->vtime = (float)ncount / (float)tscale * (float)adxt_time_unit;
    adxt->vbase = adxt_vsync_cnt;
    return ndiscard;
}

int ADXT_GetTimeOfst(AdxtObj *adxt)
{
    return adxt->time_ofst;
}

void ADXT_SetTimeOfst(AdxtObj *adxt, int ofst)
{
    adxt->time_ofst = ofst;
}

/* A positive count pads the output with silence, a negative one drops samples. */
void ADXT_AdjustSmpl(AdxtObj *adxt, int nsmpl)
{
    ADXSJD_AdjustSmpl(adxt->sjd, nsmpl);
}

void ADXT_SetLnkSw(AdxtObj *adxt, int sw)
{
    adxt->lnkflg = sw;
    if (adxt->sjd != 0) {
        ADXSJD_SetLnkSw(adxt->sjd, sw);
    }
}

int ADXT_GetLnkSw(AdxtObj *adxt)
{
    return adxt->lnkflg;
}

void ADXT_EntryFltFunc(AdxtObj *adxt, AdxtFltFunc func, void *obj)
{
    ADXSJD_EntryFltFunc(adxt->sjd, func, obj);
}

int ADXT_GetDecNumSmpl(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080818_ADXT_GetDecNumSmpl_parameter_error);
        return -1;
    }
    return ADXSJD_GetDecNumSmpl(adxt->sjd);
}

int ADXT_GetDecDtLen(AdxtObj *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E04041901_ADXT_GetDecDtLen_parameter_error);
        return -1;
    }
    return ADXSJD_GetDecDtLen(adxt->sjd);
}

/* Its message is ADXT_GetDecDtLen's. */
void ADXT_EntryDecFunc(AdxtObj *adxt, AdxtDecFunc func, void *obj)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E04041901_ADXT_GetDecDtLen_parameter_error);
        return;
    }
    ADXSJD_EntryDecFunc(adxt->sjd, func, obj);
}

/* Whether the data starts with an ADX header (0x8000 then its length); returns the length. */
int adxt_IsHeader(unsigned char *buf, int len, int *hdrlen)
{
    short ofst;
    signed char type;
    signed char bsize;
    signed char bits;
    signed char nch;
    int nsmpl;
    int blksmpl;
    int sfreq;
    unsigned short word;

    if (len < 2) {
        return 0;
    }
    word = *(unsigned short *)buf;
    if ((unsigned short)((word >> 8) | (word << 8)) != 0x8000) {
        return 0;
    }
    if (ADX_DecodeHeader(buf, len, &ofst, &type, &bsize, &bits, &nch, &sfreq, &nsmpl, &blksmpl) < 0) {
        return 0;
    }
    *hdrlen = ofst;
    return 1;
}

/* Whether the data starts with an ADX footer (0x8001). */
int adxt_IsFooter(unsigned char *buf, int len, int *ftrlen)
{
    unsigned short word;

    if (len < 2) {
        return 0;
    }
    word = *(unsigned short *)buf;
    if ((unsigned short)((word >> 8) | (word << 8)) != 0x8001) {
        return 0;
    }
    *ftrlen = len;
    return 1;
}

/* Mono output centres every channel and drops the balance; the handles' settings are reapplied. */
void ADXT_SetOutputMono(int flag)
{
    AdxtObj *adxt;
    int i;
    int ch;

    adxt_output_mono = flag;
    adxt = adxt_obj;
    for (i = ADXT_MAX_OBJ - 1; i >= 0; i--, adxt++) {
        if (adxt->used == 1) {
            for (ch = 0; ch < adxt->maxnch; ch++) {
                ADXT_SetOutPan(adxt, ch, ADXT_GetOutPan(adxt, ch));
            }
            ADXT_SetOutBalance(adxt, ADXT_GetOutBalance(adxt));
        }
    }
}

void ADXT_SetKeyString(AdxtObj *adxt, char *str)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080860_ADXT_SetKeyString_parameter_error);
        return;
    }
    ADXSJD_SetKeyString(adxt->sjd, str);
}

void ADXT_SetDefKeyString(char *str)
{
    ADXSJD_SetDefKeyString(str);
}

AdxRna *ADXT_GetRna(AdxtObj *adxt)
{
    return adxt->rna;
}

void ADXT_ResetDefFmt(AdxtObj *adxt)
{
    ADXSJD_ResetDefFmt(adxt->sjd);
}

/* Plays file `flid` of AFS partition `ptid`; the stream itself starts once the handle has stopped. */
void ADXT_StartAfs(AdxtObj *adxt, int ptid, int flid)
{
    char idstr[16];
    void *dir;
    int ofst;
    int nsct;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080811_ADXT_StartAfs_parameter_error);
        return;
    }
    ADXT_Stop(adxt);
    if (ADXF_GetFnameRangeEx(ptid, flid, adxt->fnbuf, &dir, &ofst, &nsct) != 0) {
        return;
    }
    if (adxt->stm == 0) {
        ADXERR_ItoA2(ptid, flid, idstr, 16);
        ADXERR_CallErrFunc2(E8101202_ADXT_StartAfs_can_t_open, idstr);
        adxt->ercode = ADXT_ERR_SHRTBUF;
        adxt->stat = ADXT_STAT_ERROR;
    } else {
        adxt->fname = adxt->fnbuf;
        adxt->dir = dir;
        adxt->ofst = ofst;
        adxt->nsct = nsct;
        adxt->stat = ADXT_STAT_DECINFO;
        adxt->stm_req = 1;
        adxt->pmode = ADXT_PMODE_AFS;
        ADXT_SetLnkSw(adxt, 0);
    }
}

/* Plays sectors `ofst` up to `ofst + nsct` of a file; the stream itself starts once the handle has stopped. */
void ADXT_StartFnameRange(AdxtObj *adxt, char *fname, int ofst, int nsct)
{
    if (adxt == 0 || fname == 0) {
        ADXERR_CallErrFunc1(E02080807_ADXT_StartFnameRange_parameter_error);
        return;
    }
    ADXT_Stop(adxt);
    strcpy(adxt->fnbuf, fname);
    adxt->fname = adxt->fnbuf;
    adxt->ofst = ofst;
    adxt->nsct = nsct;
    adxt->dir = 0;
    adxt->stat = ADXT_STAT_DECINFO;
    adxt->stm_req = 1;
    adxt->pmode = ADXT_PMODE_FNAME;
    ADXT_SetLnkSw(adxt, 0);
}

void ADXT_StartFname(AdxtObj *adxt, char *fname)
{
    ADXT_StartFnameRange(adxt, fname, 0, 0xfffff);
}

void ADXT_StartMem2(AdxtObj *adxt, char *data, int size);

void ADXT_StartMem(AdxtObj *adxt, char *data)
{
    ADXT_StartMem2(adxt, data, ADXT_MEM_SIZE);
}

void ADXT_StartMem2(AdxtObj *adxt, char *data, int size)
{
    SfdSj *sj;

    if (adxt == 0 || data == 0 || size < 0) {
        ADXERR_CallErrFunc1(E02080809_ADXT_StartMem2_parameter_error);
        return;
    }
    ADXT_Stop(adxt);
    ADXCRS_Lock();
    sj = SJMEM_Create(data, size);
    if (sj == 0) {
        ADXCRS_Unlock();
        ADXERR_CallErrFunc1(E8101207_can_t_create_sj_ADXT_StartMem);
        return;
    }
    adxt_start_sj(adxt, sj);
    adxt->pmode = ADXT_PMODE_MEM;
    ADXT_SetLnkSw(adxt, 0);
    ADXCRS_Unlock();
}

/* Plays stream `no` of an ACX file in memory. */
void ADXT_StartMemIdx(AdxtObj *adxt, AcxHeader *acx, int no)
{
    SfdSj *sj;

    if (adxt == 0 || acx == 0 || no < 0) {
        ADXERR_CallErrFunc1(E02080810_ADXT_StartMemIdx_parameter_error);
        return;
    }
    ADXT_Stop(adxt);
    if (no >= BSWAP32(acx->count) || no < 0) {
        return;
    }
    ADXCRS_Lock();
    sj = SJMEM_Create((char *)acx + BSWAP32((acx->ent + no)->ofst), ADXT_MEM_SIZE);
    if (sj == 0) {
        ADXCRS_Unlock();
        ADXERR_CallErrFunc1(E8101207_can_t_create_sj_ADXT_StartMemIdx);
        return;
    }
    adxt_start_sj(adxt, sj);
    adxt->pmode = ADXT_PMODE_MEM;
    ADXT_SetLnkSw(adxt, 0);
    ADXCRS_Unlock();
}
