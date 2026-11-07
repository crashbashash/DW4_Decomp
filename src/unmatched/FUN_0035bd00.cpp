extern "C" {
void FUN_0035be50(void);
extern struct G *DAT_00589238[4];
void *FUN_0035bd00(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035bd00(void) {
    struct G *g = DAT_00589238[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035be50();
    }
    return DAT_00589238[0];
}
