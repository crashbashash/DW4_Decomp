extern "C" {
int FUN_0035b0a0();
struct G { char pad[36]; int f; };
extern G *DAT_005891d0[4];
G *FUN_0035b010(void);
}
G *FUN_0035b010(void) {
    G *g = DAT_005891d0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0035b0a0();
    return DAT_005891d0[0];
}
