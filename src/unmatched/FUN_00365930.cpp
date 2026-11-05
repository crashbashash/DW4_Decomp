extern "C" {
void FUN_00365b00(void);
extern struct G *DAT_005898d0[4];
void *FUN_00365930(void);
}
struct G { int pad[9]; int f; };
void *FUN_00365930(void) {
    struct G *g = DAT_005898d0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00365b00();
end:
    return DAT_005898d0[0];
}
