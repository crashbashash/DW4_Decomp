extern "C" {
void FUN_003bbb20(void);
extern struct G *DAT_0058b048[4];
void *FUN_003bba30(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bba30(void) {
    struct G *g = DAT_0058b048[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bbb20();
end:
    return DAT_0058b048[0];
}
