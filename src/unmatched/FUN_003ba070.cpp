struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003ba140();
extern S *DAT_0058af08[4];
S *FUN_003ba070(void);
}
S *FUN_003ba070(void) {
    S *g = DAT_0058af08[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003ba140();
done:
    return DAT_0058af08[0];
}
