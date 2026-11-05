extern "C" {
void FUN_003b30f0(void);
extern struct G *DAT_0058ab38[4];
void *FUN_003b2c40(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b2c40(void) {
    struct G *g = DAT_0058ab38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b30f0();
end:
    return DAT_0058ab38[0];
}
