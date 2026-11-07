extern "C" {
void FUN_003677b0(void);
extern struct G *DAT_00589ad0[4];
void *FUN_003676d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003676d0(void) {
    struct G *g = DAT_00589ad0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003677b0();
    }
    return DAT_00589ad0[0];
}
