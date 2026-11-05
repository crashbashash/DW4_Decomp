extern "C" {
void FUN_003bb450(void);
extern struct G *DAT_0058aff0[4];
void *FUN_003bb400(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb400(void) {
    struct G *g = DAT_0058aff0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bb450();
end:
    return DAT_0058aff0[0];
}
