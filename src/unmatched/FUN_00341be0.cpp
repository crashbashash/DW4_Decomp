struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00341cb0();
extern S *DAT_00587c80[4];
S *FUN_00341be0(void);
}
S *FUN_00341be0(void) {
    S *g = DAT_00587c80[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00341cb0();
done:
    return DAT_00587c80[0];
}
