extern "C" {
void FUN_003cb020(void);
extern struct G *DAT_0058c158[4];
void *beNDMWAfsSetup_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWAfsSetup_ResolveMetaObject(void) {
    struct G *g = DAT_0058c158[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003cb020();
    }
    return DAT_0058c158[0];
}
