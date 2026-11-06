typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025d830(int stm);

void FUN_00267130(Adxt *adxt)
{
    FUN_0025d830(adxt->stm);
}
