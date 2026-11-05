extern "C" {
int FUN_003440d0();
struct G { char pad[36]; int f; };
extern G *DAT_00587e68[4];
G *FUN_00343f50(void);
}
G *FUN_00343f50(void) {
    G *g = DAT_00587e68[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003440d0();
    return DAT_00587e68[0];
}
