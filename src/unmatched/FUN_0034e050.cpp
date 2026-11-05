extern "C" {
void FUN_0034e0e0(void);
extern struct G *DAT_005886c8[4];
void *FUN_0034e050(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034e050(void) {
    struct G *g = DAT_005886c8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034e0e0();
end:
    return DAT_005886c8[0];
}
