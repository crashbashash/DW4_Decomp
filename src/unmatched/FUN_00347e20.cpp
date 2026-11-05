extern "C" {
void FUN_00347f50(void);
extern struct G *DAT_00588160[4];
void *FUN_00347e20(void);
}
struct G { int pad[9]; int f; };
void *FUN_00347e20(void) {
    struct G *g = DAT_00588160[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00347f50();
end:
    return DAT_00588160[0];
}
