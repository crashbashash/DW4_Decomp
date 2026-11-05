struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0033fe50();
extern S *DAT_00587a98[4];
S *FUN_0033fdc0(void);
}
S *FUN_0033fdc0(void) {
    S *g = DAT_00587a98[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_0033fe50();
done:
    return DAT_00587a98[0];
}
