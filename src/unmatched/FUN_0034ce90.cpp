extern "C" {
void FUN_0034cf20(void);
extern struct G *DAT_00588550[4];
void *FUN_0034ce90(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034ce90(void) {
    struct G *g = DAT_00588550[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034cf20();
    }
    return DAT_00588550[0];
}
