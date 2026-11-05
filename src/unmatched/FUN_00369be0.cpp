extern "C" {
void FUN_00369ca0(void);
extern struct G *DAT_00589d00[4];
void *FUN_00369be0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00369be0(void) {
    struct G *g = DAT_00589d00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00369ca0();
end:
    return DAT_00589d00[0];
}
