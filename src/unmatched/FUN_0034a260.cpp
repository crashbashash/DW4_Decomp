extern "C" {
void FUN_0034a340(void);
extern struct G *DAT_00588308[4];
void *FUN_0034a260(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034a260(void) {
    struct G *g = DAT_00588308[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034a340();
end:
    return DAT_00588308[0];
}
