extern "C" {
void FUN_0036a630(void);
extern struct G *DAT_00589d78[4];
void *FUN_0036a550(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036a550(void) {
    struct G *g = DAT_00589d78[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0036a630();
end:
    return DAT_00589d78[0];
}
