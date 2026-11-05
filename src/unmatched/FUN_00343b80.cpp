extern "C" {
void FUN_00343bd0(void);
extern struct G *DAT_00587e28[4];
void *FUN_00343b80(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343b80(void) {
    struct G *g = DAT_00587e28[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00343bd0();
end:
    return DAT_00587e28[0];
}
