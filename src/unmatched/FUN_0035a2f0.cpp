extern "C" {
void FUN_0035a380(void);
extern struct G *DAT_00589140[4];
void *FUN_0035a2f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035a2f0(void) {
    struct G *g = DAT_00589140[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035a380();
end:
    return DAT_00589140[0];
}
