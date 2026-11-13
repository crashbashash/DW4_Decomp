typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern char D_004eec20[];
extern void ADXERR_CallErrFunc1(char *msg);
extern int FUN_002670b8(int stm);

int FUN_0026d1e8(Adxt *adxt)
{
    if (adxt == 0) {
        ADXERR_CallErrFunc1(D_004eec20);
        return -1;
    }
    return FUN_002670b8(adxt->stm);
}
