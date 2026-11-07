struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00363fa0();
extern S *DAT_00589838[4];
S *FUN_00363f10(void);
}
S *FUN_00363f10(void) {
    S *g = DAT_00589838[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00363fa0();
done:
    return DAT_00589838[0];
}
