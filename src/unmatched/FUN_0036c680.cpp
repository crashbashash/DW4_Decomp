extern "C" {
int FUN_0036c810();
struct G { char pad[36]; int f; };
extern G *DAT_00589f48[4];
G *FUN_0036c680(void);
}
G *FUN_0036c680(void) {
    G *g = DAT_00589f48[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0036c810();
    return DAT_00589f48[0];
}
