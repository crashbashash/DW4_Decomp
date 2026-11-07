extern "C" {
void FUN_003bb610(void);
extern struct G *DAT_0058b010[4];
void *FUN_003bb5c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb5c0(void) {
    struct G *g = DAT_0058b010[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bb610();
    }
    return DAT_0058b010[0];
}
