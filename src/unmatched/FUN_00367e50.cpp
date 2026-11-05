extern "C" {
void FUN_00367f40(void);
extern struct G *DAT_00589b48[4];
void *FUN_00367e50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00367e50(void) {
    struct G *g = DAT_00589b48[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00367f40();
end:
    return DAT_00589b48[0];
}
