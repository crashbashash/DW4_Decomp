extern "C" {
void FUN_0035eee0(void);
extern struct G *DAT_00589468[4];
void *FUN_0035ee50(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035ee50(void) {
    struct G *g = DAT_00589468[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035eee0();
    }
    return DAT_00589468[0];
}
