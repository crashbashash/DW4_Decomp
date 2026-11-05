extern "C" {
void FUN_0034ddb0(void);
extern struct G *DAT_005886a8[4];
void *FUN_0034dd20(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034dd20(void) {
    struct G *g = DAT_005886a8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0034ddb0();
end:
    return DAT_005886a8[0];
}
