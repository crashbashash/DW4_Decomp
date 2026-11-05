extern "C" {
int FUN_003c3680();
struct G { char pad[36]; int f; };
extern G *DAT_0058b890[4];
G *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void);
}
G *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void) {
    G *g = DAT_0058b890[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c3680();
    return DAT_0058b890[0];
}
