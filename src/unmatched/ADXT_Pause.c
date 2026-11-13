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

extern int DAT_004a8e4c;
extern int DAT_004a8e98;
extern int DAT_0049c8f0;
extern char DAT_004eeb98[];
void FUN_002607e8(const char *message);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_00265cd0(int adx, int sw);
void FUN_0026bf90(AdxtPause *adxt, int *ncount, int *tscale);

void ADXT_Pause(AdxtPause *adxt, int sw)
{
    int stat;
    int saved;
    int ncount;
    int tscale;

    if (adxt == 0) {
        FUN_002607e8(DAT_004eeb98);
        return;
    }
    stat = adxt->stat;
    if (sw == adxt->pause) {
        return;
    }
    FUN_0025f2d0();
    adxt->pause = sw;
    if (stat == 3 || stat == 4) {
        if (sw == 1) {
            FUN_00265cd0(adxt->adx, 0);
        } else {
            FUN_00265cd0(adxt->adx, 1);
            adxt->f160 = DAT_0049c8f0;
        }
        saved = DAT_004a8e4c;
        DAT_004a8e4c = 0;
        FUN_0026bf90(adxt, &ncount, &tscale);
        DAT_004a8e4c = saved;
        adxt->f156 = (float)ncount / (float)tscale * (float)DAT_004a8e98;
    }
    FUN_0025f2e8();
}
