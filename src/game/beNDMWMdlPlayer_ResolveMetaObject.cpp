extern "C" {
void FUN_003bfae0(void);
extern struct MetaObjectValidityView *DAT_0058b3a8[4];
void *beNDMWMdlPlayer_ResolveMetaObject(void);
}
struct MetaObjectValidityView { int pad[9]; int f; };
void *beNDMWMdlPlayer_ResolveMetaObject(void) {
    struct MetaObjectValidityView *g = DAT_0058b3a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bfae0();
    }
    return DAT_0058b3a8[0];
}
