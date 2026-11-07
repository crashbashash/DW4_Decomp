extern "C" {
void FUN_00335260(void);
extern struct G *DAT_005876e0[4];
void *FUN_00335180(void);
}
struct G { int pad[9]; int f; };
void *FUN_00335180(void) {
    struct G *g = DAT_005876e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00335260();
    }
    return DAT_005876e0[0];
}
