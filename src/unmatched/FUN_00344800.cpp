extern "C" {
void FUN_00344890(void);
extern struct G *DAT_00587ed0[4];
void *FUN_00344800(void);
}
struct G { int pad[9]; int f; };
void *FUN_00344800(void) {
    struct G *g = DAT_00587ed0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00344890();
    }
    return DAT_00587ed0[0];
}
