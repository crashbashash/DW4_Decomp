extern "C" {
void FUN_003c0550(void);
extern struct G *DAT_0058b428[4];
void *beNDMWMdlPEBase_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPEBase_ResolveMetaObject(void) {
    struct G *g = DAT_0058b428[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c0550();
end:
    return DAT_0058b428[0];
}
