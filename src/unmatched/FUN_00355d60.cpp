extern "C" {
void FUN_00355e40(void);
extern struct G *DAT_00588e00[4];
void *FUN_00355d60(void);
}
struct G { int pad[9]; int f; };
void *FUN_00355d60(void) {
    struct G *g = DAT_00588e00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00355e40();
    }
    return DAT_00588e00[0];
}
