typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db68(int stm);

void FUN_00267348(Adxt *adxt)
{
    FUN_0025db68(adxt->stm);
}
