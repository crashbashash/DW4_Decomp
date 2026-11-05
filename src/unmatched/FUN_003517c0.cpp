extern "C" {
void FUN_00351910(void);
extern struct G *DAT_00588a58[4];
void *FUN_003517c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003517c0(void) {
    struct G *g = DAT_00588a58[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00351910();
end:
    return DAT_00588a58[0];
}
