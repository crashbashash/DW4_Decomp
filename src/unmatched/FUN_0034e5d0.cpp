extern "C" {
void FUN_0034e710(void);
extern struct G *DAT_005886e8[4];
void *FUN_0034e5d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034e5d0(void) {
    struct G *g = DAT_005886e8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034e710();
    }
    return DAT_005886e8[0];
}
