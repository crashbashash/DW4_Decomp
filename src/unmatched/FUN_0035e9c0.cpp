extern "C" {
void FUN_0035ea80(void);
extern struct G *DAT_00589450[4];
void *FUN_0035e9c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035e9c0(void) {
    struct G *g = DAT_00589450[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035ea80();
    }
    return DAT_00589450[0];
}
