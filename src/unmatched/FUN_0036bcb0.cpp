extern "C" {
void FUN_0036bd40(void);
extern struct G *DAT_00589e58[4];
void *FUN_0036bcb0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036bcb0(void) {
    struct G *g = DAT_00589e58[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036bd40();
    }
    return DAT_00589e58[0];
}
