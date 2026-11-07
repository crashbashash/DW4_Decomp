extern "C" {
void FUN_0035a120(void);
extern struct G *DAT_00589110[4];
void *FUN_0035a040(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035a040(void) {
    struct G *g = DAT_00589110[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a120();
    }
    return DAT_00589110[0];
}
