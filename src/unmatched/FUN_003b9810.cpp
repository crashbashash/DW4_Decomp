extern "C" {
void FUN_003b98f0(void);
extern struct G *DAT_0058aeb0[4];
void *FUN_003b9810(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b9810(void) {
    struct G *g = DAT_0058aeb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b98f0();
    }
    return DAT_0058aeb0[0];
}
