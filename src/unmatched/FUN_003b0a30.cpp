struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003b18b0();
extern S *DAT_0058a8f8[4];
S *FUN_003b0a30(void);
}
S *FUN_003b0a30(void) {
    S *g = DAT_0058a8f8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_003b18b0();
done:
    return DAT_0058a8f8[0];
}
