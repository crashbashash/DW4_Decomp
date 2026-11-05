extern "C" {
void FUN_003bd540(void);
extern struct G *DAT_0058b1d8[4];
void *beNDMWSaveCtrl_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWSaveCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058b1d8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bd540();
end:
    return DAT_0058b1d8[0];
}
