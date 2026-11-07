extern "C" {
void FUN_0033f290(void);
extern struct G *DAT_00587a50[4];
void *FUN_0033f170(void);
}
struct G { int pad[9]; int f; };
void *FUN_0033f170(void) {
    struct G *g = DAT_00587a50[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0033f290();
    }
    return DAT_00587a50[0];
}
