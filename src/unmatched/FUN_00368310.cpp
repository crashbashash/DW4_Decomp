extern "C" {
int FUN_00368450();
struct G { char pad[36]; int f; };
extern G *DAT_00589b68[4];
G *FUN_00368310(void);
}
G *FUN_00368310(void) {
    G *g = DAT_00589b68[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00368450();
    return DAT_00589b68[0];
}
