struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0035f870();
extern S *DAT_005894d8[4];
S *FUN_0035f720(void);
}
S *FUN_0035f720(void) {
    S *g = DAT_005894d8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0035f870();
done:
    return DAT_005894d8[0];
}
