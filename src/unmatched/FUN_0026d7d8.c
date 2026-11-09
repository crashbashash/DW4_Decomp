typedef struct {
    char pad0[2];
    signed char stat;
} AdxtState;

extern char DAT_004eed08[];
extern char DAT_004eed38[];
void FUN_002607e8(const char *message);
void FUN_0026bc60(AdxtState *adxt);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
int FUN_0027b408(void *buf, int size);
void FUN_0026b978(AdxtState *adxt, int sj);
void FUN_0026d158(AdxtState *adxt, int a1);

void FUN_0026d7d8(AdxtState *adxt, void *buf, int size)
{
    int sj;

    if (adxt == 0 || buf == 0 || size < 0) {
        FUN_002607e8(DAT_004eed08);
        return;
    }
    FUN_0026bc60(adxt);
    FUN_0025f2d0();
    sj = FUN_0027b408(buf, size);
    if (sj == 0) {
        FUN_0025f2e8();
        FUN_002607e8(DAT_004eed38);
        return;
    }
    FUN_0026b978(adxt, sj);
    adxt->stat = 2;
    FUN_0026d158(adxt, 0);
    FUN_0025f2e8();
}
