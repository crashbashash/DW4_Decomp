extern "C" {
void FUN_003bb610(void);
extern struct G *DAT_0058b010[4];
void *FUN_003bb5c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bb5c0(void) {
    struct G *g = DAT_0058b010[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003bb610();
end:
    return DAT_0058b010[0];
}
