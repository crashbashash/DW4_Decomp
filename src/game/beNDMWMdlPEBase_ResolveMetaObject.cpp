extern "C" {
void FUN_003c0550(void);
extern struct G *DAT_0058b428[4];
void *beNDMWMdlPEBase_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMdlPEBase_ResolveMetaObject(void) {
    struct G *g = DAT_0058b428[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c0550();
    }
    return DAT_0058b428[0];
}
