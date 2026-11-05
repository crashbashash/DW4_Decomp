extern "C" {
int FUN_003b5640();
struct G { char pad[36]; int f; };
extern G *DAT_0058abe8[4];
G *FUN_003b5570(void);
}
G *FUN_003b5570(void) {
    G *g = DAT_0058abe8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003b5640();
    return DAT_0058abe8[0];
}
