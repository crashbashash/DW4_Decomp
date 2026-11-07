extern "C" {
void FUN_0036d080(void);
extern struct G *DAT_00589fa0[4];
void *FUN_0036cfa0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036cfa0(void) {
    struct G *g = DAT_00589fa0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036d080();
    }
    return DAT_00589fa0[0];
}
