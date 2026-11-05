extern "C" {
void FUN_00353fc0(void);
extern struct G *DAT_00588c80[4];
void *FUN_00353e90(void);
}
struct G { int pad[9]; int f; };
void *FUN_00353e90(void) {
    struct G *g = DAT_00588c80[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00353fc0();
end:
    return DAT_00588c80[0];
}
