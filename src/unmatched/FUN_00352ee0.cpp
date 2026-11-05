extern "C" {
void FUN_00353040(void);
extern struct G *DAT_00588bb0[4];
void *FUN_00352ee0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00352ee0(void) {
    struct G *g = DAT_00588bb0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00353040();
end:
    return DAT_00588bb0[0];
}
