extern "C" {
void FUN_00360fe0(void);
extern struct G *DAT_005895e8[4];
void *FUN_00360e90(void);
}
struct G { int pad[9]; int f; };
void *FUN_00360e90(void) {
    struct G *g = DAT_005895e8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360fe0();
    }
    return DAT_005895e8[0];
}
