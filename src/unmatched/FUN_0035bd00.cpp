extern "C" {
void FUN_0035be50(void);
extern struct G *DAT_00589238[4];
void *FUN_0035bd00(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035bd00(void) {
    struct G *g = DAT_00589238[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035be50();
end:
    return DAT_00589238[0];
}
