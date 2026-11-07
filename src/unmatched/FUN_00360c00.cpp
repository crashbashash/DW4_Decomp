extern "C" {
void FUN_00360d30(void);
extern struct G *DAT_005895d0[4];
void *FUN_00360c00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00360c00(void) {
    struct G *g = DAT_005895d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360d30();
    }
    return DAT_005895d0[0];
}
