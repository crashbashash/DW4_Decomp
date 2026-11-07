extern "C" {
void FUN_00354510(void);
extern struct G *DAT_00588ca0[4];
void *FUN_00354340(void);
}
struct G { int pad[9]; int f; };
void *FUN_00354340(void) {
    struct G *g = DAT_00588ca0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00354510();
    }
    return DAT_00588ca0[0];
}
