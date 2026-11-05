extern "C" {
void FUN_00342b00(void);
extern struct G *DAT_00587ce8[4];
void *FUN_00342a00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00342a00(void) {
    struct G *g = DAT_00587ce8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00342b00();
end:
    return DAT_00587ce8[0];
}
