extern "C" {
void FUN_00367080(void);
extern struct G *DAT_00589a20[4];
void *FUN_00366ff0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00366ff0(void) {
    struct G *g = DAT_00589a20[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00367080();
end:
    return DAT_00589a20[0];
}
