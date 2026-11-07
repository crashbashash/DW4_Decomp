extern "C" {
void FUN_003533c0(void);
extern struct G *DAT_00588bd0[4];
void *FUN_00353290(void);
}
struct G { int pad[9]; int f; };
void *FUN_00353290(void) {
    struct G *g = DAT_00588bd0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003533c0();
    }
    return DAT_00588bd0[0];
}
