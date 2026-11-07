extern "C" {
void FUN_0035abe0(void);
extern struct G *DAT_005891b0[4];
void *FUN_0035aab0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035aab0(void) {
    struct G *g = DAT_005891b0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035abe0();
    }
    return DAT_005891b0[0];
}
