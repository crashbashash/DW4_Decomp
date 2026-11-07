struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0045a580();
extern S *DAT_0058c8f8[4];
S *igViewerModeChangeMessage_GetMetaObject(void);
}
S *igViewerModeChangeMessage_GetMetaObject(void) {
    S *g = DAT_0058c8f8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0045a580();
done:
    return DAT_0058c8f8[0];
}
