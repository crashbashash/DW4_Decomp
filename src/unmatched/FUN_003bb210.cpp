extern "C" {
void FUN_003bb2e0(void);
extern struct G *DAT_0058afe0[4];
void *FUN_003bb210(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb210(void) {
    struct G *g = DAT_0058afe0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bb2e0();
end:
    return DAT_0058afe0[0];
}
