extern "C" {
void FUN_0033ee30(void);
extern struct G *DAT_00587a28[4];
void *FUN_0033eb00(void);
}
struct G { int pad[9]; int f; };
void *FUN_0033eb00(void) {
    struct G *g = DAT_00587a28[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0033ee30();
    }
    return DAT_00587a28[0];
}
