struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003c8310();
extern S *DAT_0058bf20[4];
S *beNDMWItemImportant_GetReadyMetaObject(void);
}
S *beNDMWItemImportant_GetReadyMetaObject(void) {
    S *g = DAT_0058bf20[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003c8310();
done:
    return DAT_0058bf20[0];
}
