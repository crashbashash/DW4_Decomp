extern "C" {
void FUN_003522b0(void);
extern struct G *DAT_00588ad0[4];
void *FUN_003521d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003521d0(void) {
    struct G *g = DAT_00588ad0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003522b0();
end:
    return DAT_00588ad0[0];
}
