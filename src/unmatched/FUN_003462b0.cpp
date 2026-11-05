extern "C" {
int FUN_003463d0();
struct G { char pad[36]; int f; };
extern G *DAT_00587fd0[4];
G *FUN_003462b0(void);
}
G *FUN_003462b0(void) {
    G *g = DAT_00587fd0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003463d0();
    return DAT_00587fd0[0];
}
