extern "C" {
void FUN_00345fd0(void);
extern struct G *DAT_00587fb8[4];
void *FUN_00345ea0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00345ea0(void) {
    struct G *g = DAT_00587fb8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00345fd0();
end:
    return DAT_00587fb8[0];
}
