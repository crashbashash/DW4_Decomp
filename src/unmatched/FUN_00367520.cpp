extern "C" {
void FUN_003675b0(void);
extern struct G *DAT_00589ab0[4];
void *FUN_00367520(void);
}
struct G { int pad[9]; int f; };
void *FUN_00367520(void) {
    struct G *g = DAT_00589ab0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003675b0();
end:
    return DAT_00589ab0[0];
}
