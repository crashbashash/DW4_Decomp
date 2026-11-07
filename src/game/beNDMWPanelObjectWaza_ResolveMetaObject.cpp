struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003bea10();
extern S *DAT_0058b2a8[4];
S *beNDMWPanelObjectWaza_ResolveMetaObject(void);
}
S *beNDMWPanelObjectWaza_ResolveMetaObject(void) {
    S *g = DAT_0058b2a8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003bea10();
done:
    return DAT_0058b2a8[0];
}
