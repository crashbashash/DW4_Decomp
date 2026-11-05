extern "C" {
void FUN_0036b8c0(void);
extern struct G *DAT_00589e38[4];
void *FUN_0036b790(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036b790(void) {
    struct G *g = DAT_00589e38[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0036b8c0();
end:
    return DAT_00589e38[0];
}
