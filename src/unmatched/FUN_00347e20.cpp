extern "C" {
void FUN_00347f50(void);
extern struct G *DAT_00588160[4];
void *FUN_00347e20(void);
}
struct G { int pad[9]; int f; };
void *FUN_00347e20(void) {
    struct G *g = DAT_00588160[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00347f50();
    }
    return DAT_00588160[0];
}
