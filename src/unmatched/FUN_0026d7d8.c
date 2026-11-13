typedef struct {
    char pad0[2];
    signed char stat;
} AdxtState;

extern char DAT_004eed08[];
extern char DAT_004eed38[];
void ADXERR_CallErrFunc1(const char *message);
void ADXT_Stop(AdxtState *adxt);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
int FUN_0027b408(void *buf, int size);
void FUN_0026b978(AdxtState *adxt, int sj);
void ADXT_SetLnkSw(AdxtState *adxt, int a1);

void FUN_0026d7d8(AdxtState *adxt, void *buf, int size)
{
    int sj;

    if (adxt == 0 || buf == 0 || size < 0) {
        ADXERR_CallErrFunc1(DAT_004eed08);
        return;
    }
    ADXT_Stop(adxt);
    ADXCRS_Lock();
    sj = FUN_0027b408(buf, size);
    if (sj == 0) {
        ADXCRS_Unlock();
        ADXERR_CallErrFunc1(DAT_004eed38);
        return;
    }
    FUN_0026b978(adxt, sj);
    adxt->stat = 2;
    ADXT_SetLnkSw(adxt, 0);
    ADXCRS_Unlock();
}
