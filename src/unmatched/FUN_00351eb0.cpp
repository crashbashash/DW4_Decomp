extern "C" {
void FUN_00351ff0(void);
extern struct G *DAT_00588aa8[4];
void *FUN_00351eb0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00351eb0(void) {
    struct G *g = DAT_00588aa8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00351ff0();
end:
    return DAT_00588aa8[0];
}
