extern "C" {
void FUN_003c0770(void);
extern struct G *DAT_0058b430[4];
void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void) {
    struct G *g = DAT_0058b430[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c0770();
end:
    return DAT_0058b430[0];
}
