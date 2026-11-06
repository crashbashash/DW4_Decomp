typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db38(int stm);

void FUN_002672b8(Adxt *adxt)
{
    FUN_0025db38(adxt->stm);
}
