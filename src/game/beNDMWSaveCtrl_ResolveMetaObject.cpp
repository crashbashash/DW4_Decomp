extern "C" {
void FUN_003bd540(void);
extern struct G *DAT_0058b1d8[4];
void *beNDMWSaveCtrl_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWSaveCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058b1d8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bd540();
    }
    return DAT_0058b1d8[0];
}
