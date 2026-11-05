extern "C" {
void FUN_00356ff0(void);
extern struct G *DAT_00588e98[4];
void *FUN_00356f60(void);
}
struct G { int pad[9]; int f; };
void *FUN_00356f60(void) {
    struct G *g = DAT_00588e98[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00356ff0();
end:
    return DAT_00588e98[0];
}
