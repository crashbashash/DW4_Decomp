extern "C" {
void FUN_00335260(void);
extern struct G *DAT_005876e0[4];
void *FUN_00335180(void);
}
struct G { int pad[9]; int f; };
void *FUN_00335180(void) {
    struct G *g = DAT_005876e0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00335260();
end:
    return DAT_005876e0[0];
}
