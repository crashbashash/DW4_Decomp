typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db28(int stm);

void FUN_002672a0(Adxt *adxt)
{
    FUN_0025db28(adxt->stm);
}
