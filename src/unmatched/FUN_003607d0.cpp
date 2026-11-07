extern "C" {
void FUN_00360860(void);
extern struct G *DAT_005895a0[4];
void *FUN_003607d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003607d0(void) {
    struct G *g = DAT_005895a0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360860();
    }
    return DAT_005895a0[0];
}
