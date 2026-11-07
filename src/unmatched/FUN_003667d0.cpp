extern "C" {
void FUN_00366860(void);
extern struct G *DAT_005899c0[4];
void *FUN_003667d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003667d0(void) {
    struct G *g = DAT_005899c0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00366860();
    }
    return DAT_005899c0[0];
}
