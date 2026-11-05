extern "C" {
void FUN_003caa70(void);
extern struct G *DAT_0058c130[4];
void *beNDMWAfsSetupData_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWAfsSetupData_ResolveMetaObject(void) {
    struct G *g = DAT_0058c130[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003caa70();
end:
    return DAT_0058c130[0];
}
