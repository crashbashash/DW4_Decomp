typedef struct Adxt {
    char used;
    signed char state;
    signed char kind;
    char pad;
    int stm;
    int obj;
} Adxt;

extern int FUN_0026bd20(Adxt *adxt);
extern int ADXSTM_GetStat(int obj);
extern void FUN_00266268(int stm);

void FUN_0026ec78(Adxt *adxt)
{
    if (adxt->obj == 0)
        return;
    if (FUN_0026bd20(adxt) == 0)
        return;
    switch (adxt->kind) {
    case 0:
    case 1:
        if (ADXSTM_GetStat(adxt->obj) == 3)
            FUN_00266268(adxt->stm);
        break;
    case 2:
        FUN_00266268(adxt->stm);
        break;
    case 3:
    case 4:
        break;
    }
}
