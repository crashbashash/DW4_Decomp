extern "C" {
void FUN_00365680(void);
extern struct G *DAT_005898b8[4];
void *FUN_003655a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003655a0(void) {
    struct G *g = DAT_005898b8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00365680();
end:
    return DAT_005898b8[0];
}
