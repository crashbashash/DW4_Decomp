struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003bc140();
extern S *DAT_0058b070[4];
S *FUN_003bc080(void);
}
S *FUN_003bc080(void) {
    S *g = DAT_0058b070[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003bc140();
done:
    return DAT_0058b070[0];
}
