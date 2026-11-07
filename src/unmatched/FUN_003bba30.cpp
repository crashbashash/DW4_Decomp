extern "C" {
void FUN_003bbb20(void);
extern struct G *DAT_0058b048[4];
void *FUN_003bba30(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bba30(void) {
    struct G *g = DAT_0058b048[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bbb20();
    }
    return DAT_0058b048[0];
}
