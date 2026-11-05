extern "C" {
void FUN_003b9120(void);
extern struct G *DAT_0058ae38[4];
void *FUN_003b8f90(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b8f90(void) {
    struct G *g = DAT_0058ae38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b9120();
end:
    return DAT_0058ae38[0];
}
