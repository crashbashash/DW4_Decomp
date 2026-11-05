extern "C" {
void FUN_00360d30(void);
extern struct G *DAT_005895d0[4];
void *FUN_00360c00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00360c00(void) {
    struct G *g = DAT_005895d0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00360d30();
end:
    return DAT_005895d0[0];
}
