extern "C" {
void FUN_0036bf10(void);
extern struct G *DAT_00589e60[4];
void *FUN_0036bdf0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036bdf0(void) {
    struct G *g = DAT_00589e60[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036bf10();
    }
    return DAT_00589e60[0];
}
