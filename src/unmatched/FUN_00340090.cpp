extern "C" {
void FUN_003402c0(void);
extern struct G *DAT_00587aa8[4];
void *FUN_00340090(void);
}
struct G { int pad[9]; int f; };
void *FUN_00340090(void) {
    struct G *g = DAT_00587aa8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003402c0();
end:
    return DAT_00587aa8[0];
}
