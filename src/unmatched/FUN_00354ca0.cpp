extern "C" {
int FUN_00354d80();
struct G { char pad[36]; int f; };
extern G *DAT_00588d50[4];
G *FUN_00354ca0(void);
}
G *FUN_00354ca0(void) {
    G *g = DAT_00588d50[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00354d80();
    return DAT_00588d50[0];
}
