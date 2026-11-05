extern "C" {
int FUN_0034d3d0();
struct G { char pad[36]; int f; };
extern G *DAT_00588630[4];
G *FUN_0034d340(void);
}
G *FUN_0034d340(void) {
    G *g = DAT_00588630[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0034d3d0();
    return DAT_00588630[0];
}
