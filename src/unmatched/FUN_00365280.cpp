extern "C" {
void FUN_003653b0(void);
extern struct G *DAT_005898a8[4];
void *FUN_00365280(void);
}
struct G { int pad[9]; int f; };
void *FUN_00365280(void) {
    struct G *g = DAT_005898a8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003653b0();
end:
    return DAT_005898a8[0];
}
