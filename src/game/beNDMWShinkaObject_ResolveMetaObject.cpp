extern "C" {
int FUN_003c9ac0();
struct G { char pad[36]; int f; };
extern G *DAT_0058bff0[4];
G *beNDMWShinkaObject_ResolveMetaObject(void);
}
G *beNDMWShinkaObject_ResolveMetaObject(void) {
    G *g = DAT_0058bff0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c9ac0();
    return DAT_0058bff0[0];
}
