extern "C" {
void FUN_003547b0(void);
extern struct G *DAT_00588cf8[4];
void *FUN_00354720(void);
}
struct G { int pad[9]; int f; };
void *FUN_00354720(void) {
    struct G *g = DAT_00588cf8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003547b0();
end:
    return DAT_00588cf8[0];
}
