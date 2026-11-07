extern "C" {
void FUN_0036e3b0(void);
extern struct G *DAT_0058a040[4];
void *FUN_0036e2c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036e2c0(void) {
    struct G *g = DAT_0058a040[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036e3b0();
    }
    return DAT_0058a040[0];
}
