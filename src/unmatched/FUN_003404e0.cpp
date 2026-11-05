extern "C" {
void FUN_003405c0(void);
extern struct G *DAT_00587b88[4];
void *FUN_003404e0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003404e0(void) {
    struct G *g = DAT_00587b88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003405c0();
end:
    return DAT_00587b88[0];
}
