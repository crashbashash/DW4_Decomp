extern "C" {
void FUN_003c0770(void);
extern struct G *DAT_0058b430[4];
void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void) {
    struct G *g = DAT_0058b430[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c0770();
    }
    return DAT_0058b430[0];
}
