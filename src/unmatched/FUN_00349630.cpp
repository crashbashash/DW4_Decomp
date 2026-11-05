extern "C" {
void FUN_003497c0(void);
extern struct G *DAT_00588268[4];
void *FUN_00349630(void);
}
struct G { int pad[9]; int f; };
void *FUN_00349630(void) {
    struct G *g = DAT_00588268[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003497c0();
end:
    return DAT_00588268[0];
}
