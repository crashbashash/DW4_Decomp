extern "C" {
void FUN_003c4850(void);
extern struct G *DAT_0058bac8[4];
void *beNDMWLoadIntf2_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2_ResolveMetaObject(void) {
    struct G *g = DAT_0058bac8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c4850();
    }
    return DAT_0058bac8[0];
}
