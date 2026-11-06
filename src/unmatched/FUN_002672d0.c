typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db30(int stm);

void FUN_002672d0(Adxt *adxt)
{
    FUN_0025db30(adxt->stm);
}
