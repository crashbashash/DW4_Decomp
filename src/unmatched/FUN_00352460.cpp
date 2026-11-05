extern "C" {
void FUN_003525e0(void);
extern struct G *DAT_00588b00[4];
void *FUN_00352460(void);
}
struct G { int pad[9]; int f; };
void *FUN_00352460(void) {
    struct G *g = DAT_00588b00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003525e0();
end:
    return DAT_00588b00[0];
}
