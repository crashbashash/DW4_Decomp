extern "C" {
int FUN_00363d60();
struct G { char pad[36]; int f; };
extern G *DAT_005897f8[4];
G *FUN_00363c60(void);
}
G *FUN_00363c60(void) {
    G *g = DAT_005897f8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00363d60();
    return DAT_005897f8[0];
}
