extern "C" {
void FUN_00345490(void);
extern struct G *DAT_00587f30[4];
void *FUN_003452e0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003452e0(void) {
    struct G *g = DAT_00587f30[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00345490();
end:
    return DAT_00587f30[0];
}
