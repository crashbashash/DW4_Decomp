typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db18(int stm);

void FUN_00267270(Adxt *adxt)
{
    FUN_0025db18(adxt->stm);
}
