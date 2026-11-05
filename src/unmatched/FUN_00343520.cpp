extern "C" {
void FUN_00343650(void);
extern struct G *DAT_00587df8[4];
void *FUN_00343520(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343520(void) {
    struct G *g = DAT_00587df8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00343650();
end:
    return DAT_00587df8[0];
}
