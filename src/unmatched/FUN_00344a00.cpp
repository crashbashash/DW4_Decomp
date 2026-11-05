extern "C" {
void FUN_00344a90(void);
extern struct G *DAT_00587ee8[4];
void *FUN_00344a00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00344a00(void) {
    struct G *g = DAT_00587ee8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00344a90();
end:
    return DAT_00587ee8[0];
}
