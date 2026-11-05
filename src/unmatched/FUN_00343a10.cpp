extern "C" {
void FUN_00343ad0(void);
extern struct G *DAT_00587e20[4];
void *FUN_00343a10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343a10(void) {
    struct G *g = DAT_00587e20[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00343ad0();
end:
    return DAT_00587e20[0];
}
