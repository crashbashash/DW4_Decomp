extern "C" {
void FUN_00341500(void);
extern struct G *DAT_00587c18[4];
void *FUN_003413d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003413d0(void) {
    struct G *g = DAT_00587c18[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00341500();
end:
    return DAT_00587c18[0];
}
