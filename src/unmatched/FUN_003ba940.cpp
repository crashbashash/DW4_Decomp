extern "C" {
void FUN_003ba9f0(void);
extern struct G *DAT_0058af28[4];
void *FUN_003ba940(void);
}
struct G { int pad[9]; int f; };
void *FUN_003ba940(void) {
    struct G *g = DAT_0058af28[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003ba9f0();
    }
    return DAT_0058af28[0];
}
