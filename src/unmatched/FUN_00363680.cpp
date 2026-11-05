extern "C" {
void FUN_00363710(void);
extern struct G *DAT_005897d0[4];
void *FUN_00363680(void);
}
struct G { int pad[9]; int f; };
void *FUN_00363680(void) {
    struct G *g = DAT_005897d0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00363710();
end:
    return DAT_005897d0[0];
}
