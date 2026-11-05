extern "C" {
void FUN_003c5600(void);
extern struct G *DAT_0058bc10[4];
void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void) {
    struct G *g = DAT_0058bc10[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c5600();
end:
    return DAT_0058bc10[0];
}
