extern "C" {
void FUN_003552a0(void);
extern struct G *DAT_00588d70[4];
void *FUN_003551c0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003551c0(void) {
    struct G *g = DAT_00588d70[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003552a0();
end:
    return DAT_00588d70[0];
}
