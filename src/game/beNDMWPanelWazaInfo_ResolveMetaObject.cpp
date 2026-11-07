extern "C" {
void FUN_003bd750(void);
extern struct G *DAT_0058b1e8[4];
void *beNDMWPanelWazaInfo_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWPanelWazaInfo_ResolveMetaObject(void) {
    struct G *g = DAT_0058b1e8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bd750();
    }
    return DAT_0058b1e8[0];
}
