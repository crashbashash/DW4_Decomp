extern "C" {
void FUN_003563a0(void);
extern struct G *DAT_00588e20[4];
void *FUN_003562c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003562c0(void) {
    struct G *g = DAT_00588e20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003563a0();
    }
    return DAT_00588e20[0];
}
