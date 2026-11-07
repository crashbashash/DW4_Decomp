extern "C" {
void FUN_003b6cf0(void);
extern struct G *DAT_0058acc8[4];
void *FUN_003b6c00(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b6c00(void) {
    struct G *g = DAT_0058acc8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b6cf0();
    }
    return DAT_0058acc8[0];
}
