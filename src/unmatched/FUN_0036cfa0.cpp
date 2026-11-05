extern "C" {
void FUN_0036d080(void);
extern struct G *DAT_00589fa0[4];
void *FUN_0036cfa0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036cfa0(void) {
    struct G *g = DAT_00589fa0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0036d080();
end:
    return DAT_00589fa0[0];
}
