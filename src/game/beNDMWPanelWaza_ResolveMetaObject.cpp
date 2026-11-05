extern "C" {
void FUN_003bf050(void);
extern struct G *DAT_0058b358[4];
void *beNDMWPanelWaza_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWPanelWaza_ResolveMetaObject(void) {
    struct G *g = DAT_0058b358[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bf050();
end:
    return DAT_0058b358[0];
}
