extern "C" {
int FUN_0036a970();
struct G { char pad[36]; int f; };
extern G *DAT_00589db8[4];
G *FUN_0036a920(void);
}
G *FUN_0036a920(void) {
    G *g = DAT_00589db8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0036a970();
    return DAT_00589db8[0];
}
