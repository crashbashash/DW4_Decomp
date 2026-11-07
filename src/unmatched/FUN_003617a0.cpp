struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00361830();
extern S *DAT_00589650[4];
S *FUN_003617a0(void);
}
S *FUN_003617a0(void) {
    S *g = DAT_00589650[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00361830();
done:
    return DAT_00589650[0];
}
