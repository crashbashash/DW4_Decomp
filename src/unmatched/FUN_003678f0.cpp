extern "C" {
void FUN_00367b20(void);
extern struct G *DAT_00589ad8[4];
void *FUN_003678f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003678f0(void) {
    struct G *g = DAT_00589ad8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00367b20();
end:
    return DAT_00589ad8[0];
}
