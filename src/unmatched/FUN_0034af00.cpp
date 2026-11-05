struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0034af90();
extern S *DAT_005883b0[4];
S *FUN_0034af00(void);
}
S *FUN_0034af00(void) {
    S *g = DAT_005883b0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_0034af90();
done:
    return DAT_005883b0[0];
}
