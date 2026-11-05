extern "C" {
void FUN_00366b20(void);
extern struct G *DAT_005899c8[4];
void *FUN_003669a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003669a0(void) {
    struct G *g = DAT_005899c8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00366b20();
end:
    return DAT_005899c8[0];
}
