extern "C" {
void FUN_00364bf0(void);
extern struct G *DAT_00589878[4];
void *FUN_00364ad0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00364ad0(void) {
    struct G *g = DAT_00589878[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00364bf0();
end:
    return DAT_00589878[0];
}
