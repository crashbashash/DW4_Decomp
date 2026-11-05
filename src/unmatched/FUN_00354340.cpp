extern "C" {
void FUN_00354510(void);
extern struct G *DAT_00588ca0[4];
void *FUN_00354340(void);
}
struct G { int pad[9]; int f; };
void *FUN_00354340(void) {
    struct G *g = DAT_00588ca0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00354510();
end:
    return DAT_00588ca0[0];
}
