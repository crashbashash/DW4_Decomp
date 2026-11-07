extern "C" {
void FUN_003487c0(void);
extern struct G *DAT_005881e0[4];
void *FUN_00348630(void);
}
struct G { int pad[9]; int f; };
void *FUN_00348630(void) {
    struct G *g = DAT_005881e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003487c0();
    }
    return DAT_005881e0[0];
}
