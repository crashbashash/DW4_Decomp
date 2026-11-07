extern "C" {
void FUN_003b2680(void);
extern struct G *DAT_0058aab8[4];
void *FUN_003b25a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b25a0(void) {
    struct G *g = DAT_0058aab8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b2680();
    }
    return DAT_0058aab8[0];
}
