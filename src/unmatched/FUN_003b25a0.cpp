extern "C" {
void FUN_003b2680(void);
extern struct G *DAT_0058aab8[4];
void *FUN_003b25a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b25a0(void) {
    struct G *g = DAT_0058aab8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b2680();
end:
    return DAT_0058aab8[0];
}
