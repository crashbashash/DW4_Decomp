struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00358cd0();
extern S *DAT_00589030[4];
S *FUN_00358c40(void);
}
S *FUN_00358c40(void) {
    S *g = DAT_00589030[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_00358cd0();
done:
    return DAT_00589030[0];
}
