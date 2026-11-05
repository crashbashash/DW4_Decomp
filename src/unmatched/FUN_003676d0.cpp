extern "C" {
void FUN_003677b0(void);
extern struct G *DAT_00589ad0[4];
void *FUN_003676d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003676d0(void) {
    struct G *g = DAT_00589ad0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003677b0();
end:
    return DAT_00589ad0[0];
}
