extern "C" {
void FUN_00361210(void);
extern struct G *DAT_005895f8[4];
void *FUN_00361130(void);
}
struct G { int pad[9]; int f; };
void *FUN_00361130(void) {
    struct G *g = DAT_005895f8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00361210();
end:
    return DAT_005895f8[0];
}
