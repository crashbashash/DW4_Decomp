extern "C" {
void FUN_003b1e70(void);
extern struct G *DAT_0058a9b8[4];
void *FUN_003b1e20(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b1e20(void) {
    struct G *g = DAT_0058a9b8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b1e70();
    }
    return DAT_0058a9b8[0];
}
