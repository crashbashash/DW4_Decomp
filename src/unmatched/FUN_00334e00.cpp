extern "C" {
void FUN_00334ec0(void);
extern struct G *DAT_00587668[4];
void *FUN_00334e00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00334e00(void) {
    struct G *g = DAT_00587668[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00334ec0();
end:
    return DAT_00587668[0];
}
