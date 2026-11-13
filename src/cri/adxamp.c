/* CRI ADXAMP: measures the peak amplitude of each channel of decoded samples, one frame at a time, and writes
 * one record per frame to the channel's output stream joint. */
#include "dw4/cri/sfdsj.h"

#define ADXAMP_MAX_OBJ 16
#define ADXAMP_MAX_CH 2

/* AdxAmpObj.stat */
enum AdxAmpStat {
    ADXAMP_STAT_STOP = 0,
    ADXAMP_STAT_EXEC = 2
};

typedef struct AdxAmpObj {
    signed char used;               /* 0x00 */
    signed char stat;               /* 0x01: ADXAMP_STAT_* */
    signed char maxnch;             /* 0x02 */
    char pad3;
    SfdSj *sji[ADXAMP_MAX_CH];      /* 0x04: decoded samples in */
    SfdSj *sjo[ADXAMP_MAX_CH];      /* 0x0c: amplitude records out */
    int nsmpl[ADXAMP_MAX_CH];       /* 0x14: samples measured, per channel */
    int nch;                        /* 0x1c */
    int sfreq;                      /* 0x20 */
    float frmlen;                   /* 0x24: seconds per measured frame */
    float frmprd;                   /* 0x28 */
    int nfrm;                       /* 0x2c: frames measured */
} AdxAmpObj;

extern int adxamp_init_cnt;
extern AdxAmpObj adxamp_obj[ADXAMP_MAX_OBJ];

void *memset(void *dst, int value, unsigned int size);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void adxamp_Extract(AdxAmpObj *amp);

void ADXAMP_Init(void)
{
    if (adxamp_init_cnt == 0) {
        memset(adxamp_obj, 0, sizeof(adxamp_obj));
    }
    adxamp_init_cnt++;
}

void ADXAMP_Finish(void)
{
    if (--adxamp_init_cnt == 0) {
        memset(adxamp_obj, 0, sizeof(adxamp_obj));
    }
}

AdxAmpObj *ADXAMP_Create(int maxnch, SfdSj **sji, SfdSj **sjo)
{
    AdxAmpObj *amp;
    int i;
    int ch;

    for (i = 0; i < ADXAMP_MAX_OBJ; i++) {
        if (adxamp_obj[i].used == 0) {
            break;
        }
    }
    if (i == ADXAMP_MAX_OBJ) {
        return 0;
    }
    ADXCRS_Lock();
    amp = &adxamp_obj[i];
    amp->maxnch = maxnch;
    for (ch = 0; ch < maxnch; ch++) {
        amp->nsmpl[ch] = 0;
        amp->sji[ch] = sji[ch];
        amp->sjo[ch] = sjo[ch];
    }
    amp->sfreq = 44100;
    amp->stat = ADXAMP_STAT_STOP;
    amp->nfrm = 0;
    amp->frmlen = 0.1f;
    amp->nch = maxnch;
    amp->frmprd = 0.1f;
    amp->used = 1;
    ADXCRS_Unlock();
    return amp;
}

void ADXAMP_Destroy(AdxAmpObj *amp)
{
    if (amp != 0) {
        ADXCRS_Lock();
        memset(amp, 0, sizeof(AdxAmpObj));
        ADXCRS_Unlock();
    }
}

int ADXAMP_GetStat(AdxAmpObj *amp)
{
    return amp->stat;
}

/* Empties every input and output stream joint and starts measuring. */
void ADXAMP_Start(AdxAmpObj *amp)
{
    SfdSjChunk ck;
    SfdSj *sj;
    int ch;

    for (ch = 0; ch < amp->maxnch; ch++) {
        amp->nsmpl[ch] = 0;
    }
    amp->nfrm = 0;
    for (ch = 0; ch < amp->maxnch; ch++) {
        sj = amp->sji[ch];
        sj->vtbl->reset(sj);
        sj->vtbl->getChunk(sj, 0, sj->vtbl->getNumData(sj, 0), &ck);
        memset(ck.data, 0, ck.len);
        sj->vtbl->ungetChunk(sj, 0, &ck);
    }
    for (ch = 0; ch < amp->maxnch; ch++) {
        sj = amp->sjo[ch];
        sj->vtbl->reset(sj);
        sj->vtbl->getChunk(sj, 0, sj->vtbl->getNumData(sj, 0), &ck);
        memset(ck.data, 0, ck.len);
        sj->vtbl->ungetChunk(sj, 0, &ck);
    }
    amp->stat = ADXAMP_STAT_EXEC;
}

void ADXAMP_Stop(AdxAmpObj *amp)
{
    amp->stat = ADXAMP_STAT_STOP;
}

void ADXAMP_ExecHndl(AdxAmpObj *amp)
{
    if (amp->stat == ADXAMP_STAT_EXEC) {
        adxamp_Extract(amp);
    }
}

void ADXAMP_ExecServer(void)
{
    AdxAmpObj *amp;
    int i;

    for (i = 0, amp = adxamp_obj; i < ADXAMP_MAX_OBJ; i++, amp++) {
        if (amp->used == 1) {
            ADXAMP_ExecHndl(amp);
        }
    }
}

int ADXAMP_GetNumSmpl(AdxAmpObj *amp)
{
    return amp->nsmpl[0];
}

void ADXAMP_SetSfreq(AdxAmpObj *amp, int sfreq)
{
    amp->sfreq = sfreq;
}

int ADXAMP_GetSfreq(AdxAmpObj *amp)
{
    return amp->sfreq;
}

void ADXAMP_SetFrmLen(AdxAmpObj *amp, float frmlen)
{
    amp->frmlen = frmlen;
}

float ADXAMP_GetFrmLen(AdxAmpObj *amp)
{
    return amp->frmlen;
}

void ADXAMP_SetFrmPrd(AdxAmpObj *amp, float frmprd)
{
    amp->frmprd = frmprd;
}

float ADXAMP_GetFrmPrd(AdxAmpObj *amp)
{
    return amp->frmprd;
}
