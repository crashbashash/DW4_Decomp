extern "C" {
void FUN_003bb8e0(void);
extern struct G *DAT_0058b028[4];
void *FUN_003bb820(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb820(void) {
    struct G *g = DAT_0058b028[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb8e0();
    }
    return DAT_0058b028[0];
}
