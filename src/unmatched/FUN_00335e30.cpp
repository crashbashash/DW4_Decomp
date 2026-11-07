struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00335ec0();
extern S *DAT_00587790[4];
S *FUN_00335e30(void);
}
S *FUN_00335e30(void) {
    S *g = DAT_00587790[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00335ec0();
done:
    return DAT_00587790[0];
}
