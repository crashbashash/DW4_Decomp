extern "C" {
void FUN_003bd1d0(void);
extern struct G *DAT_0058b188[4];
void *FUN_003bd0f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bd0f0(void) {
    struct G *g = DAT_0058b188[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bd1d0();
    }
    return DAT_0058b188[0];
}
