extern "C" {
void FUN_0036d4c0(void);
extern struct G *DAT_00589fc8[4];
void *FUN_0036d3a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036d3a0(void) {
    struct G *g = DAT_00589fc8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036d4c0();
    }
    return DAT_00589fc8[0];
}
