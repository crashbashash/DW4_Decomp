extern "C" {
void FUN_003b30f0(void);
extern struct G *DAT_0058ab38[4];
void *FUN_003b2c40(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b2c40(void) {
    struct G *g = DAT_0058ab38[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b30f0();
    }
    return DAT_0058ab38[0];
}
