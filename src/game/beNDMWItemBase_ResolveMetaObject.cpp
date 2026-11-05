extern "C" {
void FUN_003c9360(void);
extern struct G *DAT_0058bf90[4];
void *beNDMWItemBase_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemBase_ResolveMetaObject(void) {
    struct G *g = DAT_0058bf90[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c9360();
end:
    return DAT_0058bf90[0];
}
