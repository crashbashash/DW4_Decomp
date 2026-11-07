struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003b7b50();
extern S *DAT_0058ad80[4];
S *FUN_003b7a80(void);
}
S *FUN_003b7a80(void) {
    S *g = DAT_0058ad80[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003b7b50();
done:
    return DAT_0058ad80[0];
}
