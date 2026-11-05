extern "C" {
void FUN_003b21a0(void);
extern struct G *DAT_0058aa50[4];
void *FUN_003b20e0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b20e0(void) {
    struct G *g = DAT_0058aa50[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b21a0();
end:
    return DAT_0058aa50[0];
}
