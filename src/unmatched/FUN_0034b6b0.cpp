extern "C" {
void FUN_0034b810(void);
extern struct G *DAT_00588478[4];
void *FUN_0034b6b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034b6b0(void) {
    struct G *g = DAT_00588478[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034b810();
end:
    return DAT_00588478[0];
}
