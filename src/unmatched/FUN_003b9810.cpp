extern "C" {
void FUN_003b98f0(void);
extern struct G *DAT_0058aeb0[4];
void *FUN_003b9810(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b9810(void) {
    struct G *g = DAT_0058aeb0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b98f0();
end:
    return DAT_0058aeb0[0];
}
