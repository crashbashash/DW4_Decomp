extern "C" {
void FUN_00347ce0(void);
extern struct G *DAT_00588148[4];
void *FUN_00347c50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00347c50(void) {
    struct G *g = DAT_00588148[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00347ce0();
end:
    return DAT_00588148[0];
}
