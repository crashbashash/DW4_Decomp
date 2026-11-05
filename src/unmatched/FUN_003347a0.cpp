extern "C" {
void FUN_003348d0(void);
extern struct G *DAT_00587638[4];
void *FUN_003347a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003347a0(void) {
    struct G *g = DAT_00587638[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003348d0();
end:
    return DAT_00587638[0];
}
