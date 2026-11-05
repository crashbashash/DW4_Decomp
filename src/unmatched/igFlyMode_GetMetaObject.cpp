struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0045ca20();
extern S *DAT_0058cc80[4];
S *igFlyMode_GetMetaObject(void);
}
S *igFlyMode_GetMetaObject(void) {
    S *g = DAT_0058cc80[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_0045ca20();
done:
    return DAT_0058cc80[0];
}
