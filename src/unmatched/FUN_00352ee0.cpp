extern "C" {
void FUN_00353040(void);
extern struct G *DAT_00588bb0[4];
void *FUN_00352ee0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00352ee0(void) {
    struct G *g = DAT_00588bb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00353040();
    }
    return DAT_00588bb0[0];
}
