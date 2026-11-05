struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_0035b280();
extern S *DAT_005891d8[4];
S *FUN_0035b150(void);
}
S *FUN_0035b150(void) {
    S *g = DAT_005891d8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
        asm { nop }
    }
    FUN_0035b280();
done:
    return DAT_005891d8[0];
}
