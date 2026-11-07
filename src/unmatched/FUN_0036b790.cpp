extern "C" {
void FUN_0036b8c0(void);
extern struct G *DAT_00589e38[4];
void *FUN_0036b790(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036b790(void) {
    struct G *g = DAT_00589e38[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036b8c0();
    }
    return DAT_00589e38[0];
}
