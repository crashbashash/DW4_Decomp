struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0034f5c0();
extern S *DAT_005887b0[4];
S *FUN_0034f4e0(void);
}
S *FUN_0034f4e0(void) {
    S *g = DAT_005887b0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0034f5c0();
done:
    return DAT_005887b0[0];
}
