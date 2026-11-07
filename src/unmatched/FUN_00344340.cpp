struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003444c0();
extern S *DAT_00587ea8[4];
S *FUN_00344340(void);
}
S *FUN_00344340(void) {
    S *g = DAT_00587ea8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003444c0();
done:
    return DAT_00587ea8[0];
}
