struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003b3d90();
extern S *DAT_0058ab70[4];
S *FUN_003b3cc0(void);
}
S *FUN_003b3cc0(void) {
    S *g = DAT_0058ab70[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003b3d90();
done:
    return DAT_0058ab70[0];
}
