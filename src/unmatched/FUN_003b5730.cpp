struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003b5800();
extern S *DAT_0058abf0[4];
S *FUN_003b5730(void);
}
S *FUN_003b5730(void) {
    S *g = DAT_0058abf0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003b5800();
done:
    return DAT_0058abf0[0];
}
