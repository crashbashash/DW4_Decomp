struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00356950();
extern S *DAT_00588e40[4];
S *FUN_00356820(void);
}
S *FUN_00356820(void) {
    S *g = DAT_00588e40[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00356950();
done:
    return DAT_00588e40[0];
}
