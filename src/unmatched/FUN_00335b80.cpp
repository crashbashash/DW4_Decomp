extern "C" {
int FUN_00335c10();
struct G { char pad[36]; int f; };
extern G *DAT_00587760[4];
G *FUN_00335b80(void);
}
G *FUN_00335b80(void) {
    G *g = DAT_00587760[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00335c10();
    return DAT_00587760[0];
}
