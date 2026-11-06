typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db10(int stm);

void FUN_00267258(Adxt *adxt)
{
    FUN_0025db10(adxt->stm);
}
