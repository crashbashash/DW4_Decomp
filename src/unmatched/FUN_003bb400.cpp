extern "C" {
void FUN_003bb450(void);
extern struct G *DAT_0058aff0[4];
void *FUN_003bb400(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb400(void) {
    struct G *g = DAT_0058aff0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb450();
    }
    return DAT_0058aff0[0];
}
