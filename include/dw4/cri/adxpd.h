/* CRI ADX packet decoder (ADXPD): a table of decode jobs the ADXB layer queues and the server runs. */
#ifndef DW4_CRI_ADXPD_H
#define DW4_CRI_ADXPD_H

#define ADXPD_MAX_OBJ 16

enum AdxPdStat {
    ADXPD_STAT_STOP = 0,
    ADXPD_STAT_DECODE_QUEUED = 1,
    ADXPD_STAT_DECODING = 2,
    ADXPD_STAT_DECEND = 3
};

/* Which decoder a queued job runs. */
enum AdxPdChannels {
    ADXPD_CH_MONO = 1,
    ADXPD_CH_STEREO = 2
};

typedef struct AdxPdObj {
    int used;
    int id;
    int mode;
    int stat;
    int nblk_decoded;
    int channels;
    unsigned char *ibuf;
    int nblk;
    short *obufl;
    short *obufr;
    /* Decoder history, two samples per channel. */
    short dly[2][2];
    short k0;
    short k1;
    /* Extended parameters: a 16-bit seed the decoder updates, then a multiplier and an addend. */
    short seed;
    short mul;
    short add;
} AdxPdObj;

void ADXPD_Init(void);
void ADXPD_Finish(void);
AdxPdObj *ADXPD_Create(void);
void ADXPD_SetCoef(AdxPdObj *pd, int sfreq, int cutoff);
void ADXPD_SetDly(AdxPdObj *pd, unsigned short *dly1, unsigned short *dly2);
void ADXPD_GetDly(AdxPdObj *pd, unsigned short *dly1, unsigned short *dly2);
void ADXPD_SetExtPrm(AdxPdObj *pd, short seed, short mul, short add);
void ADXPD_GetExtPrm(AdxPdObj *pd, unsigned short *seed, unsigned short *mul, unsigned short *add);
void ADXPD_Destroy(AdxPdObj *pd);
void ADXPD_SetMode(AdxPdObj *pd, int mode);
int ADXPD_GetStat(AdxPdObj *pd);
int ADXPD_EntryMono(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr);
int ADXPD_EntrySte(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr);
int ADXPD_EntryPl2(AdxPdObj *pd, unsigned char *ibuf, int nblk, short *obufl, short *obufr);
void ADXPD_Start(AdxPdObj *pd);
void ADXPD_Stop(AdxPdObj *pd);
void ADXPD_Reset(AdxPdObj *pd);
int ADXPD_GetNumBlk(AdxPdObj *pd);
void ADXPD_ExecHndl(AdxPdObj *pd);
void ADXPD_ExecServer(void);

#endif
