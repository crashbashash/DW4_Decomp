extern "C" {
int FUN_00361610();
struct G { char pad[36]; int f; };
extern G *DAT_00589640[4];
G *FUN_00361530(void);
}
G *FUN_00361530(void) {
    G *g = DAT_00589640[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00361610();
    return DAT_00589640[0];
}
