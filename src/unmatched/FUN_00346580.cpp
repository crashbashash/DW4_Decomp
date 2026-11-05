struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003466b0();
extern S *DAT_00587fe8[4];
S *FUN_00346580(void);
}
S *FUN_00346580(void) {
    S *g = DAT_00587fe8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003466b0();
done:
    return DAT_00587fe8[0];
}
