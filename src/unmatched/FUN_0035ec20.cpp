extern "C" {
void FUN_0035ed50(void);
extern struct G *DAT_00589460[4];
void *FUN_0035ec20(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035ec20(void) {
    struct G *g = DAT_00589460[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035ed50();
    }
    return DAT_00589460[0];
}
