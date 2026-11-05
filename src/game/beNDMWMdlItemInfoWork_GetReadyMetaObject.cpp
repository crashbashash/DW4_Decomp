struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003c15b0();
extern S *DAT_0058b4c0[4];
S *beNDMWMdlItemInfoWork_GetReadyMetaObject(void);
}
S *beNDMWMdlItemInfoWork_GetReadyMetaObject(void) {
    S *g = DAT_0058b4c0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003c15b0();
done:
    return DAT_0058b4c0[0];
}
