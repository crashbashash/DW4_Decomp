typedef struct {
    char f0;
    signed char stat;
    char pad2[10];
    int adx;
    char pad16[98];
    signed char pause;
    char pad115[41];
    unsigned int f156;
    int f160;
} AdxtPause;

extern int adxt_time_mode;
extern int adxt_time_unit;
extern int adxt_vsync_cnt;
extern char DAT_004eeb98[];
void ADXERR_CallErrFunc1(const char *message);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void ADXRNA_SetPlaySw(int adx, int sw);
void ADXT_GetTime(AdxtPause *adxt, int *ncount, int *tscale);

void ADXT_Pause(AdxtPause *adxt, int sw)
{
    int stat;
    int saved;
    int ncount;
    int tscale;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004eeb98);
        return;
    }
    stat = adxt->stat;
    if (sw == adxt->pause) {
        return;
    }
    ADXCRS_Lock();
    adxt->pause = sw;
    if (stat == 3 || stat == 4) {
        if (sw == 1) {
            ADXRNA_SetPlaySw(adxt->adx, 0);
        } else {
            ADXRNA_SetPlaySw(adxt->adx, 1);
            adxt->f160 = adxt_vsync_cnt;
        }
        saved = adxt_time_mode;
        adxt_time_mode = 0;
        ADXT_GetTime(adxt, &ncount, &tscale);
        adxt_time_mode = saved;
        adxt->f156 = (float)ncount / (float)tscale * (float)adxt_time_unit;
    }
    ADXCRS_Unlock();
}
