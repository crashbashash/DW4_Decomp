extern "C" {
void FUN_0034a9a0(void);
extern struct G *DAT_00588348[4];
void *FUN_0034a8c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034a8c0(void) {
    struct G *g = DAT_00588348[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034a9a0();
end:
    return DAT_00588348[0];
}
