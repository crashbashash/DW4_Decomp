extern "C" {
void FUN_00350fb0(void);
extern struct G *DAT_00588888[4];
void *FUN_003500b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003500b0(void) {
    struct G *g = DAT_00588888[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00350fb0();
end:
    return DAT_00588888[0];
}
