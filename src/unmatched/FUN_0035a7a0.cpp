extern "C" {
void FUN_0035a880(void);
extern struct G *DAT_00589160[4];
void *FUN_0035a7a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035a7a0(void) {
    struct G *g = DAT_00589160[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a880();
    }
    return DAT_00589160[0];
}
