extern "C" {
void FUN_003ba850(void);
extern struct G *DAT_0058af20[4];
void *FUN_003ba7a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003ba7a0(void) {
    struct G *g = DAT_0058af20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003ba850();
    }
    return DAT_0058af20[0];
}
