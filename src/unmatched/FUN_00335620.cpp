extern "C" {
void FUN_003357a0(void);
extern struct G *DAT_00587738[4];
void *FUN_00335620(void);
}
struct G { int pad[9]; int f; };
void *FUN_00335620(void) {
    struct G *g = DAT_00587738[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003357a0();
end:
    return DAT_00587738[0];
}
