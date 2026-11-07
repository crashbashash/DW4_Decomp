extern "C" {
void FUN_003c3f10(void);
extern struct G *DAT_0058b978[4];
void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void) {
    struct G *g = DAT_0058b978[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c3f10();
    }
    return DAT_0058b978[0];
}
