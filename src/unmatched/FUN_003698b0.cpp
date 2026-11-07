extern "C" {
void FUN_00369a20(void);
extern struct G *DAT_00589c90[4];
void *FUN_003698b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003698b0(void) {
    struct G *g = DAT_00589c90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00369a20();
    }
    return DAT_00589c90[0];
}
