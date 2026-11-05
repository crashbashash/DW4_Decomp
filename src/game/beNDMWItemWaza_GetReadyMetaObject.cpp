extern "C" {
int FUN_003c8110();
struct G { char pad[36]; int f; };
extern G *DAT_0058bf10[4];
G *beNDMWItemWaza_GetReadyMetaObject(void);
}
G *beNDMWItemWaza_GetReadyMetaObject(void) {
    G *g = DAT_0058bf10[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c8110();
    return DAT_0058bf10[0];
}
