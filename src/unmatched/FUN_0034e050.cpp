extern "C" {
void FUN_0034e0e0(void);
extern struct G *DAT_005886c8[4];
void *FUN_0034e050(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034e050(void) {
    struct G *g = DAT_005886c8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034e0e0();
    }
    return DAT_005886c8[0];
}
