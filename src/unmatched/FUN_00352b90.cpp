struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00352c20();
extern S *DAT_00588b98[4];
S *FUN_00352b90(void);
}
S *FUN_00352b90(void) {
    S *g = DAT_00588b98[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_00352c20();
done:
    return DAT_00588b98[0];
}
