extern "C" {
void FUN_00351910(void);
extern struct G *DAT_00588a58[4];
void *FUN_003517c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003517c0(void) {
    struct G *g = DAT_00588a58[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00351910();
    }
    return DAT_00588a58[0];
}
