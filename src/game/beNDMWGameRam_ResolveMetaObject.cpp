struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003c9f70();
extern S *DAT_0058c0a0[4];
S *beNDMWGameRam_ResolveMetaObject(void);
}
S *beNDMWGameRam_ResolveMetaObject(void) {
    S *g = DAT_0058c0a0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003c9f70();
done:
    return DAT_0058c0a0[0];
}
