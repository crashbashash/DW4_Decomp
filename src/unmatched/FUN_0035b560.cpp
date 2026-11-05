extern "C" {
void FUN_0035b5f0(void);
extern struct G *DAT_005891f0[4];
void *FUN_0035b560(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035b560(void) {
    struct G *g = DAT_005891f0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0035b5f0();
end:
    return DAT_005891f0[0];
}
