extern "C" {
void FUN_003364c0(void);
extern struct G *DAT_005877b0[4];
void *FUN_00336240(void);
}
struct G { int pad[9]; int f; };
void *FUN_00336240(void) {
    struct G *g = DAT_005877b0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003364c0();
end:
    return DAT_005877b0[0];
}
