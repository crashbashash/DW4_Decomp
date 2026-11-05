extern "C" {
void FUN_003b5070(void);
extern struct G *DAT_0058abc8[4];
void *FUN_003b4f90(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4f90(void) {
    struct G *g = DAT_0058abc8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b5070();
end:
    return DAT_0058abc8[0];
}
