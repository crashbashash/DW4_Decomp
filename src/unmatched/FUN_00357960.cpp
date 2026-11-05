extern "C" {
void FUN_00357d10(void);
extern struct G *DAT_00588f38[4];
void *FUN_00357960(void);
}
struct G { int pad[9]; int f; };
void *FUN_00357960(void) {
    struct G *g = DAT_00588f38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00357d10();
end:
    return DAT_00588f38[0];
}
