extern "C" {
void FUN_00366860(void);
extern struct G *DAT_005899c0[4];
void *FUN_003667d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003667d0(void) {
    struct G *g = DAT_005899c0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00366860();
end:
    return DAT_005899c0[0];
}
