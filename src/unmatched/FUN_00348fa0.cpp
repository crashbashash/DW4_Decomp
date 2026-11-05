struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00349100();
extern S *DAT_00588220[4];
S *FUN_00348fa0(void);
}
S *FUN_00348fa0(void) {
    S *g = DAT_00588220[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_00349100();
done:
    return DAT_00588220[0];
}
