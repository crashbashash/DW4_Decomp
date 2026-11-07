extern "C" {
void FUN_0035c370(void);
extern struct G *DAT_00589260[4];
void *FUN_0035c280(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035c280(void) {
    struct G *g = DAT_00589260[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035c370();
    }
    return DAT_00589260[0];
}
