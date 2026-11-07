extern "C" {
void FUN_003b6f80(void);
extern struct G *DAT_0058ace0[4];
void *FUN_003b6ea0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b6ea0(void) {
    struct G *g = DAT_0058ace0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b6f80();
    }
    return DAT_0058ace0[0];
}
