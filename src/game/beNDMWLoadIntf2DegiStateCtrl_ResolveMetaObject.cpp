struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003c3ac0();
extern S *DAT_0058b958[4];
S *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void);
}
S *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void) {
    S *g = DAT_0058b958[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003c3ac0();
done:
    return DAT_0058b958[0];
}
