extern "C" {
void FUN_00366b20(void);
extern struct G *DAT_005899c8[4];
void *FUN_003669a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003669a0(void) {
    struct G *g = DAT_005899c8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00366b20();
    }
    return DAT_005899c8[0];
}
