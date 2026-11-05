extern "C" {
void FUN_0035dd30(void);
extern struct G *DAT_00589380[4];
void *FUN_0035dc60(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035dc60(void) {
    struct G *g = DAT_00589380[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035dd30();
end:
    return DAT_00589380[0];
}
