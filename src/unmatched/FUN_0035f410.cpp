extern "C" {
int FUN_0035f5d0();
struct G { char pad[36]; int f; };
extern G *DAT_005894c8[4];
G *FUN_0035f410(void);
}
G *FUN_0035f410(void) {
    G *g = DAT_005894c8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0035f5d0();
    return DAT_005894c8[0];
}
