typedef struct {
    char pad0[3];
    signed char nch;
    int sjd;
    char pad8[4];
    int adx;
    char pad16[50];
    short pan[2];
} AdxtPan;

extern int DAT_0049c8e8;
extern char DAT_004ee730[];
extern char DAT_004ee760[];
void ADXERR_CallErrFunc1(const char *message);
int FUN_002673d0(int sjd);
int ADXSJD_GetNumChan();
void FUN_00265de0(int adx, int ch, int pan);

void FUN_0026c468(AdxtPan *adxt, int ch, int pan)
{
    int base;
    int out;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee730);
        return;
    }
    base = FUN_002673d0(adxt->sjd);
    if (base == -128) {
        base = 0;
    }
    if (DAT_0049c8e8 != 0) {
        out = 0;
    } else {
        if (pan == -128) {
            if (ADXSJD_GetNumChan(adxt->sjd) == 2) {
                out = (ch == 0) ? -15 : 15;
            } else {
                out = 0;
            }
            out += base;
        } else {
            out = pan + base;
        }
    }
    adxt->pan[ch] = pan;
    if (ch < adxt->nch) {
        FUN_00265de0(adxt->adx, ch, out);
    } else {
        ADXERR_CallErrFunc1(DAT_004ee760);
    }
}
