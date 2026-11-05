extern "C" {
int FUN_003be6d0();
struct G { char pad[36]; int f; };
extern G *DAT_0058b288[4];
G *beNDMWPanelObjectItem_ResolveMetaObject(void);
}
G *beNDMWPanelObjectItem_ResolveMetaObject(void) {
    G *g = DAT_0058b288[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003be6d0();
    return DAT_0058b288[0];
}
