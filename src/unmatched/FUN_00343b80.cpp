extern "C" {
void FUN_00343bd0(void);
extern struct G *DAT_00587e28[4];
void *FUN_00343b80(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343b80(void) {
    struct G *g = DAT_00587e28[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00343bd0();
    }
    return DAT_00587e28[0];
}
