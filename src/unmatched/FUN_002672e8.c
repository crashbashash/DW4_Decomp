typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db40(int stm);

void FUN_002672e8(Adxt *adxt)
{
    FUN_0025db40(adxt->stm);
}
