extern "C" {
void FUN_003badf0(void);
extern struct G *DAT_0058af88[4];
void *FUN_003bad20(void);
}
struct G { int pad[9]; int f; };
void *FUN_003bad20(void) {
    struct G *g = DAT_0058af88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003badf0();
end:
    return DAT_0058af88[0];
}
