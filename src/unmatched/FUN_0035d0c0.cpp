extern "C" {
int FUN_0035d1a0();
struct G { char pad[36]; int f; };
extern G *DAT_00589308[4];
G *FUN_0035d0c0(void);
}
G *FUN_0035d0c0(void) {
    G *g = DAT_00589308[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0035d1a0();
    return DAT_00589308[0];
}
