struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0036abd0();
extern S *DAT_00589de0[4];
S *FUN_0036ab40(void);
}
S *FUN_0036ab40(void) {
    S *g = DAT_00589de0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_0036abd0();
done:
    return DAT_00589de0[0];
}
