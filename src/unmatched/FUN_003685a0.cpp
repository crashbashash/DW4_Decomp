struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00368660();
extern S *DAT_00589b78[4];
S *FUN_003685a0(void);
}
S *FUN_003685a0(void) {
    S *g = DAT_00589b78[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00368660();
done:
    return DAT_00589b78[0];
}
