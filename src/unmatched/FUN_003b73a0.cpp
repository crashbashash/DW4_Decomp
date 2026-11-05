extern "C" {
void FUN_003b7470(void);
extern struct G *DAT_0058ad20[4];
void *FUN_003b73a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b73a0(void) {
    struct G *g = DAT_0058ad20[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b7470();
end:
    return DAT_0058ad20[0];
}
