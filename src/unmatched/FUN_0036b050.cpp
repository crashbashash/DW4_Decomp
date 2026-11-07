extern "C" {
void FUN_0036b0a0(void);
extern struct G *DAT_00589e08[4];
void *FUN_0036b050(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036b050(void) {
    struct G *g = DAT_00589e08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036b0a0();
    }
    return DAT_00589e08[0];
}
