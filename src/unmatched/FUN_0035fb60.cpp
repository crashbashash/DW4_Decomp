extern "C" {
void FUN_0035fd50(void);
extern struct G *DAT_005894f0[4];
void *FUN_0035fb60(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035fb60(void) {
    struct G *g = DAT_005894f0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035fd50();
end:
    return DAT_005894f0[0];
}
