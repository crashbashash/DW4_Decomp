extern "C" {
void FUN_0035e350(void);
extern struct G *DAT_005893e0[4];
void *FUN_0035e2c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035e2c0(void) {
    struct G *g = DAT_005893e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035e350();
    }
    return DAT_005893e0[0];
}
