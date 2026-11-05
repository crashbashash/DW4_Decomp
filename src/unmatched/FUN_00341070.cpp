extern "C" {
void FUN_003411e0(void);
extern struct G *DAT_00587c08[4];
void *FUN_00341070(void);
}
struct G { int pad[9]; int f; };
void *FUN_00341070(void) {
    struct G *g = DAT_00587c08[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003411e0();
end:
    return DAT_00587c08[0];
}
