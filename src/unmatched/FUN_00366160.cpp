extern "C" {
int FUN_00366290();
struct G { char pad[36]; int f; };
extern G *DAT_00589958[4];
G *FUN_00366160(void);
}
G *FUN_00366160(void) {
    G *g = DAT_00589958[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00366290();
    return DAT_00589958[0];
}
