struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0035d3f0();
extern S *DAT_00589318[4];
S *FUN_0035d300(void);
}
S *FUN_0035d300(void) {
    S *g = DAT_00589318[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0035d3f0();
done:
    return DAT_00589318[0];
}
