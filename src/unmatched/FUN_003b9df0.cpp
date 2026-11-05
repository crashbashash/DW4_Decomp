extern "C" {
int FUN_003b9ed0();
struct G { char pad[36]; int f; };
extern G *DAT_0058aef8[4];
G *FUN_003b9df0(void);
}
G *FUN_003b9df0(void) {
    G *g = DAT_0058aef8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b9ed0();
    return DAT_0058aef8[0];
}
