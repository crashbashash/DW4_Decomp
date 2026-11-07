extern "C" {
void FUN_0035c570(void);
extern struct G *DAT_00589268[4];
void *FUN_0035c420(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035c420(void) {
    struct G *g = DAT_00589268[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035c570();
    }
    return DAT_00589268[0];
}
