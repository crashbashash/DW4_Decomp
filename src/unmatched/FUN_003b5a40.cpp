extern "C" {
void FUN_003b5b00(void);
extern struct G *DAT_0058ac30[4];
void *FUN_003b5a40(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b5a40(void) {
    struct G *g = DAT_0058ac30[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003b5b00();
end:
    return DAT_0058ac30[0];
}
