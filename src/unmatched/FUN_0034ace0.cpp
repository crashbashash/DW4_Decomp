extern "C" {
int FUN_0034ad70();
struct G { char pad[36]; int f; };
extern G *DAT_005883a0[4];
G *FUN_0034ace0(void);
}
G *FUN_0034ace0(void) {
    G *g = DAT_005883a0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0034ad70();
    return DAT_005883a0[0];
}
