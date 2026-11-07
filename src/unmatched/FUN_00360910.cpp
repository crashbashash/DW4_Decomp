extern "C" {
void FUN_003609f0(void);
extern struct G *DAT_005895a8[4];
void *FUN_00360910(void);
}
struct G { int pad[9]; int f; };
void *FUN_00360910(void) {
    struct G *g = DAT_005895a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003609f0();
    }
    return DAT_005895a8[0];
}
