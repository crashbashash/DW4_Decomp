extern "C" {
void FUN_00360860(void);
extern struct G *DAT_005895a0[4];
void *FUN_003607d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003607d0(void) {
    struct G *g = DAT_005895a0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00360860();
end:
    return DAT_005895a0[0];
}
