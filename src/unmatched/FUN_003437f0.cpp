extern "C" {
void FUN_003438b0(void);
extern struct G *DAT_00587e10[4];
void *FUN_003437f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003437f0(void) {
    struct G *g = DAT_00587e10[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003438b0();
end:
    return DAT_00587e10[0];
}
