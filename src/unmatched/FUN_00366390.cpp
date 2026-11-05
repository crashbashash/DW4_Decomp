struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_00366420();
extern S *DAT_00589960[4];
S *FUN_00366390(void);
}
S *FUN_00366390(void) {
    S *g = DAT_00589960[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_00366420();
done:
    return DAT_00589960[0];
}
