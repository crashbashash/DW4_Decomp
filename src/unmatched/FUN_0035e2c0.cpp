extern "C" {
void FUN_0035e350(void);
extern struct G *DAT_005893e0[4];
void *FUN_0035e2c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035e2c0(void) {
    struct G *g = DAT_005893e0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035e350();
end:
    return DAT_005893e0[0];
}
