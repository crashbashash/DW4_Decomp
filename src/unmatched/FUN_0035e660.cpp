extern "C" {
void FUN_0035e7a0(void);
extern struct G *DAT_00589400[4];
void *FUN_0035e660(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035e660(void) {
    struct G *g = DAT_00589400[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035e7a0();
    }
    return DAT_00589400[0];
}
