extern "C" {
int FUN_00348e40();
struct G { char pad[36]; int f; };
extern G *DAT_00588200[4];
G *FUN_00348cb0(void);
}
G *FUN_00348cb0(void) {
    G *g = DAT_00588200[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00348e40();
    return DAT_00588200[0];
}
