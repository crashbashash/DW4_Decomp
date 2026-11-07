extern "C" {
void FUN_003bb2e0(void);
extern struct G *DAT_0058afe0[4];
void *FUN_003bb210(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb210(void) {
    struct G *g = DAT_0058afe0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb2e0();
    }
    return DAT_0058afe0[0];
}
