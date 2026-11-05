extern "C" {
int FUN_003b3bd0();
struct G { char pad[36]; int f; };
extern G *DAT_0058ab68[4];
G *FUN_003b3b00(void);
}
G *FUN_003b3b00(void) {
    G *g = DAT_0058ab68[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b3bd0();
    return DAT_0058ab68[0];
}
