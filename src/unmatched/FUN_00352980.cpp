extern "C" {
int FUN_00352a10();
struct G { char pad[36]; int f; };
extern G *DAT_00588b48[4];
G *FUN_00352980(void);
}
G *FUN_00352980(void) {
    G *g = DAT_00588b48[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00352a10();
    return DAT_00588b48[0];
}
