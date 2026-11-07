extern "C" {
void FUN_003432e0(void);
extern struct G *DAT_00587de0[4];
void *FUN_00343190(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343190(void) {
    struct G *g = DAT_00587de0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003432e0();
    }
    return DAT_00587de0[0];
}
