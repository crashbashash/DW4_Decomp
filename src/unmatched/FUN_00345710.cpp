extern "C" {
void FUN_00345830(void);
extern struct G *DAT_00587f60[4];
void *FUN_00345710(void);
}
struct G { int pad[9]; int f; };
void *FUN_00345710(void) {
    struct G *g = DAT_00587f60[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00345830();
end:
    return DAT_00587f60[0];
}
