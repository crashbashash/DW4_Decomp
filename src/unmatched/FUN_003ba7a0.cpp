extern "C" {
void FUN_003ba850(void);
extern struct G *DAT_0058af20[4];
void *FUN_003ba7a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003ba7a0(void) {
    struct G *g = DAT_0058af20[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003ba850();
end:
    return DAT_0058af20[0];
}
