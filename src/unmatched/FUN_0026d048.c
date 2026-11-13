typedef struct {
    char pad0[12];
    int f12;
    char pad16[98];
    signed char f114;
    char pad115[41];
    unsigned int f156;
    int f160;
} AdxtTimer;

extern int adxt_time_mode;
extern int adxt_time_unit;
extern int adxt_vsync_cnt;
int FUN_00265ea0(int a0);
void FUN_0026cbd8(void);
void ADXT_GetTime(AdxtTimer *adxt, int *ncount, int *tscale);

int FUN_0026d048(AdxtTimer *adxt)
{
    int ret;
    int saved;
    int ncount;
    int tscale;

    if (adxt->f114 == 0) {
        return 0;
    }
    ret = FUN_00265ea0(adxt->f12);
    FUN_0026cbd8();
    saved = adxt_time_mode;
    adxt_time_mode = 0;
    ADXT_GetTime(adxt, &ncount, &tscale);
    adxt_time_mode = saved;
    adxt->f156 = (float)ncount / (float)tscale * (float)adxt_time_unit;
    adxt->f160 = adxt_vsync_cnt;
    return ret;
}
