struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0034d740();
extern S *DAT_00588650[4];
S *FUN_0034d540(void);
}
S *FUN_0034d540(void) {
    S *g = DAT_00588650[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0034d740();
done:
    return DAT_00588650[0];
}
