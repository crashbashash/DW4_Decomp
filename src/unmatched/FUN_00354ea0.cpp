struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00354f80();
extern S *DAT_00588d60[4];
S *FUN_00354ea0(void);
}
S *FUN_00354ea0(void) {
    S *g = DAT_00588d60[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00354f80();
done:
    return DAT_00588d60[0];
}
