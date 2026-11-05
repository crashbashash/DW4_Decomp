extern "C" {
int FUN_00356720();
struct G { char pad[36]; int f; };
extern G *DAT_00588e38[4];
G *FUN_00356690(void);
}
G *FUN_00356690(void) {
    G *g = DAT_00588e38[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00356720();
    return DAT_00588e38[0];
}
