extern "C" {
void FUN_003ca480(void);
extern struct G *DAT_0058c108[4];
void *beNDMWGameRamInfo_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWGameRamInfo_ResolveMetaObject(void) {
    struct G *g = DAT_0058c108[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003ca480();
    }
    return DAT_0058c108[0];
}
