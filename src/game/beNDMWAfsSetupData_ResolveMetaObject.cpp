extern "C" {
void FUN_003caa70(void);
extern struct G *DAT_0058c130[4];
void *beNDMWAfsSetupData_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWAfsSetupData_ResolveMetaObject(void) {
    struct G *g = DAT_0058c130[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003caa70();
    }
    return DAT_0058c130[0];
}
