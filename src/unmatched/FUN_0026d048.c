typedef struct {
    char pad0[12];
    int f12;
    char pad16[98];
    signed char f114;
    char pad115[41];
    unsigned int f156;
    int f160;
} AdxtTimer;

extern int DAT_004a8e4c;
extern int DAT_004a8e98;
extern int DAT_0049c8f0;
int FUN_00265ea0(int a0);
void FUN_0026cbd8(void);
void FUN_0026bf90(AdxtTimer *adxt, int *ncount, int *tscale);

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
    saved = DAT_004a8e4c;
    DAT_004a8e4c = 0;
    FUN_0026bf90(adxt, &ncount, &tscale);
    DAT_004a8e4c = saved;
    adxt->f156 = (float)ncount / (float)tscale * (float)DAT_004a8e98;
    adxt->f160 = DAT_0049c8f0;
    return ret;
}
