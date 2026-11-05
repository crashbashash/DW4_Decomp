extern "C" {
void FUN_003692d0(void);
extern struct G *DAT_00589c08[4];
void *FUN_003691b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003691b0(void) {
    struct G *g = DAT_00589c08[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003692d0();
end:
    return DAT_00589c08[0];
}
