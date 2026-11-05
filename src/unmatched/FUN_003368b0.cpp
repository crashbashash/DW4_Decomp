extern "C" {
void FUN_00336a70(void);
extern struct G *DAT_00587860[4];
void *FUN_003368b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003368b0(void) {
    struct G *g = DAT_00587860[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00336a70();
end:
    return DAT_00587860[0];
}
