extern "C" {
void FUN_00345010(void);
extern struct G *DAT_00587f10[4];
void *FUN_00344ed0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00344ed0(void) {
    struct G *g = DAT_00587f10[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00345010();
end:
    return DAT_00587f10[0];
}
