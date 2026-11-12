#include "dw4/cri/adxpd.h"

extern int adxpd_odd_block_error;
extern AdxPdObj adxpd_obj[ADXPD_MAX_OBJ];

int memset();
void ADX_GetCoefficient(int cutoff, int sfreq, short *k0, short *k1);
int ADX_DecodeMono4(unsigned char *ibuf, int nblk, short *obuf, short *dly, int k0, int k1,
                    short *seed, int mul, int add);
int ADX_DecodeSte4(unsigned char *ibuf, int nblk, short *obufl, short *dlyl, short *obufr,
                   short *dlyr, int k0, int k1, short *seed, int mul, int add);

void ADXPD_Init(void) {
    memset(adxpd_obj, 0, sizeof(adxpd_obj));
}

void ADXPD_Finish(void) {
    memset(adxpd_obj, 0, sizeof(adxpd_obj));
}

AdxPdObj *ADXPD_Create(void)
{
    AdxPdObj *pd;
    int i;
    for (i = 0; i < ADXPD_MAX_OBJ; i++) {
        if (adxpd_obj[i].used == 0) {
            break;
        }
    }
    if (i == ADXPD_MAX_OBJ) {
        return 0;
    }
    pd = &adxpd_obj[i];
    memset(pd, 0, sizeof(AdxPdObj));
    pd->used = 1;
    pd->id = i;
    pd->mode = 0;
    pd->stat = ADXPD_STAT_STOP;
    ADX_GetCoefficient(500, 44100, &pd->k0, &pd->k1);
    memset(pd->dly, 0, sizeof(pd->dly));
    return pd;
}

void ADXPD_SetCoef(AdxPdObj *pd, int sfreq, int cutoff) {
    ADX_GetCoefficient(cutoff, sfreq, &pd->k0, &pd->k1);
}

void ADXPD_SetDly(AdxPdObj *pd, unsigned short *dly1, unsigned short *dly2) {
    pd->dly[0][0] = dly1[0];
    pd->dly[0][1] = dly2[0];
    pd->dly[1][0] = dly1[1];
    pd->dly[1][1] = dly2[1];
}

void ADXPD_GetDly(AdxPdObj *pd, unsigned short *dly1, unsigned short *dly2) {
    dly1[0] = pd->dly[0][0];
    dly2[0] = pd->dly[0][1];
    dly1[1] = pd->dly[1][0];
    dly2[1] = pd->dly[1][1];
}

void ADXPD_SetExtPrm(AdxPdObj *pd, short seed, short mul, short add) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    pd->seed = seed;
    pd->mul = mul;
    pd->add = add;
}

void ADXPD_GetExtPrm(AdxPdObj *pd, unsigned short *seed, unsigned short *mul, unsigned short *add) {
    *seed = pd->seed;
    *mul = pd->mul;
    *add = pd->add;
}

void ADXPD_Destroy(AdxPdObj *pd)
{
    if (pd != 0) {
        pd->used = 0;
        memset(pd, 0, sizeof(AdxPdObj));
    }
}

void ADXPD_SetMode(AdxPdObj *pd, int mode)
{
    pd->mode = mode;
}

int ADXPD_GetStat(AdxPdObj *pd)
{
    return pd->stat;
}

int ADXPD_EntryMono(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr) {
    if (pd->stat == ADXPD_STAT_STOP) {
        pd->obufr = obufr;
        pd->ibuf = ibuf;
        pd->nblk = nblk;
        pd->obufl = obufl;
        pd->channels = ADXPD_CH_MONO;
        return 1;
    }
    return 0;
}

int ADXPD_EntrySte(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr) {
    if (pd->stat == ADXPD_STAT_STOP) {
        pd->obufr = obufr;
        pd->ibuf = ibuf;
        pd->nblk = nblk;
        pd->obufl = obufl;
        pd->channels = ADXPD_CH_STEREO;
        return 1;
    }
    return 0;
}

int ADXPD_EntryPl2(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr) {
    if (pd->stat == ADXPD_STAT_STOP) {
        pd->obufr = obufr;
        pd->ibuf = ibuf;
        pd->nblk = nblk;
        pd->obufl = obufl;
        pd->channels = ADXPD_CH_MONO;
        return 1;
    }
    return 0;
}

void ADXPD_Start(AdxPdObj *pd) {
    if (pd->stat == ADXPD_STAT_STOP) {
        pd->nblk_decoded = 0;
        pd->stat = ADXPD_STAT_DECODE_QUEUED;
    }
}

void ADXPD_Stop(AdxPdObj *pd) {
    pd->stat = ADXPD_STAT_STOP;
    memset(pd->dly, 0, sizeof(pd->dly));
}

void ADXPD_Reset(AdxPdObj *pd) {
    if (pd->stat == ADXPD_STAT_DECEND) {
        pd->stat = ADXPD_STAT_STOP;
    }
}

int ADXPD_GetNumBlk(AdxPdObj *pd)
{
    return pd->nblk_decoded;
}

void adxpd_SetOddBlockError(void) {
    adxpd_odd_block_error = 1;
}

void ADXPD_ExecHndl(AdxPdObj *pd)
{
    if (pd->stat == ADXPD_STAT_DECODE_QUEUED) {
        pd->stat = ADXPD_STAT_DECODING;
    }
    if (pd->stat != ADXPD_STAT_DECODING) {
        return;
    }
    if (pd->channels == ADXPD_CH_MONO) {
        pd->nblk_decoded = ADX_DecodeMono4(pd->ibuf, pd->nblk, pd->obufl, pd->dly[0], pd->k0,
                                           pd->k1, &pd->seed, pd->mul, pd->add);
    } else {
        pd->nblk_decoded = ADX_DecodeSte4(pd->ibuf, pd->nblk, pd->obufl, pd->dly[0], pd->obufr,
                                          pd->dly[1], pd->k0, pd->k1, &pd->seed, pd->mul, pd->add);
        if (pd->nblk_decoded % 2 == 1) {
            adxpd_SetOddBlockError();
        }
    }
    pd->stat = ADXPD_STAT_DECEND;
}

void ADXPD_ExecServer(void) {
    int i;
    for (i = 0; i < ADXPD_MAX_OBJ; i++) {
        if (adxpd_obj[i].used == 1) {
            ADXPD_ExecHndl(&adxpd_obj[i]);
        }
    }
}
