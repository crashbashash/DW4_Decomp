extern "C" {
void FUN_003bd9c0(void);
extern struct G *DAT_0058b1f0[4];
void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void) {
    struct G *g = DAT_0058b1f0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bd9c0();
end:
    return DAT_0058b1f0[0];
}
