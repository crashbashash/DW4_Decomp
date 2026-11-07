extern "C" {
void FUN_00355520(void);
extern struct G *DAT_00588d88[4];
void *FUN_003553c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003553c0(void) {
    struct G *g = DAT_00588d88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00355520();
    }
    return DAT_00588d88[0];
}
