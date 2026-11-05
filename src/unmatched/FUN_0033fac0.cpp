extern "C" {
int FUN_0033fbf0();
struct G { char pad[36]; int f; };
extern G *DAT_00587a80[4];
G *FUN_0033fac0(void);
}
G *FUN_0033fac0(void) {
    G *g = DAT_00587a80[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0033fbf0();
    return DAT_00587a80[0];
}
