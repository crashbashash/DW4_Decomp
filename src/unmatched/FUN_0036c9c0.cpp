struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0036ca50();
extern S *DAT_00589f70[4];
S *FUN_0036c9c0(void);
}
S *FUN_0036c9c0(void) {
    S *g = DAT_00589f70[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0036ca50();
done:
    return DAT_00589f70[0];
}
