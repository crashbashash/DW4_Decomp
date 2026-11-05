extern "C" {
void FUN_00365120(void);
extern struct G *DAT_00589898[4];
void *FUN_00365040(void);
}
struct G { int pad[9]; int f; };
void *FUN_00365040(void) {
    struct G *g = DAT_00589898[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00365120();
end:
    return DAT_00589898[0];
}
