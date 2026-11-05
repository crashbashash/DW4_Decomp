extern "C" {
int FUN_00341b30();
struct G { char pad[36]; int f; };
extern G *DAT_00587c78[4];
G *FUN_00341aa0(void);
}
G *FUN_00341aa0(void) {
    G *g = DAT_00587c78[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00341b30();
    return DAT_00587c78[0];
}
