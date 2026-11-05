extern "C" {
void FUN_00340fc0(void);
extern struct G *DAT_00587c00[4];
void *FUN_00340f30(void);
}
struct G { int pad[9]; int f; };
void *FUN_00340f30(void) {
    struct G *g = DAT_00587c00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00340fc0();
end:
    return DAT_00587c00[0];
}
