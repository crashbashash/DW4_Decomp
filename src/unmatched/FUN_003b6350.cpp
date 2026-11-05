extern "C" {
void FUN_003b64f0(void);
extern struct G *DAT_0058ac88[4];
void *FUN_003b6350(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b6350(void) {
    struct G *g = DAT_0058ac88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b64f0();
end:
    return DAT_0058ac88[0];
}
