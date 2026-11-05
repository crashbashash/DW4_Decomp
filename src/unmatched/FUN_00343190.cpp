extern "C" {
void FUN_003432e0(void);
extern struct G *DAT_00587de0[4];
void *FUN_00343190(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343190(void) {
    struct G *g = DAT_00587de0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003432e0();
end:
    return DAT_00587de0[0];
}
