extern "C" {
void FUN_00353a00(void);
extern struct G *DAT_00588c00[4];
void *FUN_003538d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003538d0(void) {
    struct G *g = DAT_00588c00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00353a00();
end:
    return DAT_00588c00[0];
}
