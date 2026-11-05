extern "C" {
int FUN_0034f340();
struct G { char pad[36]; int f; };
extern G *DAT_005887a0[4];
G *FUN_0034f260(void);
}
G *FUN_0034f260(void) {
    G *g = DAT_005887a0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0034f340();
    return DAT_005887a0[0];
}
