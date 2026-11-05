extern "C" {
void FUN_0036e160(void);
extern struct G *DAT_0058a030[4];
void *FUN_0036e030(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036e030(void) {
    struct G *g = DAT_0058a030[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0036e160();
end:
    return DAT_0058a030[0];
}
