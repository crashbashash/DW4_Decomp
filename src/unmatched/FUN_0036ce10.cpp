extern "C" {
void FUN_0036cef0(void);
extern struct G *DAT_00589f98[4];
void *FUN_0036ce10(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036ce10(void) {
    struct G *g = DAT_00589f98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036cef0();
    }
    return DAT_00589f98[0];
}
