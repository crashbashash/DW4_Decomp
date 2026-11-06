typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db60(int stm);

void FUN_00267330(Adxt *adxt)
{
    FUN_0025db60(adxt->stm);
}
