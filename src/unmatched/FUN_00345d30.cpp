extern "C" {
void FUN_00345df0(void);
extern struct G *DAT_00587fb0[4];
void *FUN_00345d30(void);
}
struct G { int pad[9]; int f; };
void *FUN_00345d30(void) {
    struct G *g = DAT_00587fb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345df0();
    }
    return DAT_00587fb0[0];
}
