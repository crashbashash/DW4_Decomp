extern "C" {
void FUN_003ca690(void);
extern struct MetaObjectValidityView *DAT_0058c110[4];
void *beNDMWAfsSetupInfo_ResolveMetaObject(void);
}
struct MetaObjectValidityView { int pad[9]; int f; };
void *beNDMWAfsSetupInfo_ResolveMetaObject(void) {
    struct MetaObjectValidityView *g = DAT_0058c110[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003ca690();
    }
    return DAT_0058c110[0];
}
