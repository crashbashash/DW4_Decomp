extern "C" {
void FUN_003c4850(void);
extern struct G *DAT_0058bac8[4];
void *beNDMWLoadIntf2_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadIntf2_ResolveMetaObject(void) {
    struct G *g = DAT_0058bac8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c4850();
end:
    return DAT_0058bac8[0];
}
