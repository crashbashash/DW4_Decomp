extern "C" {
void FUN_00355cb0(void);
extern struct G *DAT_00588df8[4];
void *FUN_00355bd0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00355bd0(void) {
    struct G *g = DAT_00588df8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00355cb0();
    }
    return DAT_00588df8[0];
}
