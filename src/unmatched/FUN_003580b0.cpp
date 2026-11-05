extern "C" {
void beMessengerWork_EnsureRegistered(void);
extern struct G *DAT_00588f88[4];
void *FUN_003580b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003580b0(void) {
    struct G *g = DAT_00588f88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    beMessengerWork_EnsureRegistered();
end:
    return DAT_00588f88[0];
}
