extern "C" {
int FUN_003b78a0();
struct G { char pad[36]; int f; };
extern G *DAT_0058ad40[4];
G *FUN_003b7790(void);
}
G *FUN_003b7790(void) {
    G *g = DAT_0058ad40[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b78a0();
    return DAT_0058ad40[0];
}
