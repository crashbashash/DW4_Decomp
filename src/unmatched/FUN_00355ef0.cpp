extern "C" {
void FUN_00355fd0(void);
extern struct G *DAT_00588e08[4];
void *FUN_00355ef0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00355ef0(void) {
    struct G *g = DAT_00588e08[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00355fd0();
end:
    return DAT_00588e08[0];
}
