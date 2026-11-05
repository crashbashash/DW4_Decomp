extern "C" {
void FUN_0035c570(void);
extern struct G *DAT_00589268[4];
void *FUN_0035c420(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035c420(void) {
    struct G *g = DAT_00589268[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035c570();
end:
    return DAT_00589268[0];
}
