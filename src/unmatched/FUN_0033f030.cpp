extern "C" {
void FUN_0033f0c0(void);
extern struct G *DAT_00587a48[4];
void *FUN_0033f030(void);
}
struct G { int pad[9]; int f; };
void *FUN_0033f030(void) {
    struct G *g = DAT_00587a48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0033f0c0();
    }
    return DAT_00587a48[0];
}
