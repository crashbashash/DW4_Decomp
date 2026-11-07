extern "C" {
void FUN_00353a00(void);
extern struct G *DAT_00588c00[4];
void *FUN_003538d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003538d0(void) {
    struct G *g = DAT_00588c00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00353a00();
    }
    return DAT_00588c00[0];
}
