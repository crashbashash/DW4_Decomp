extern "C" {
void FUN_00349e90(void);
extern struct G *DAT_00588280[4];
void *FUN_00349db0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00349db0(void) {
    struct G *g = DAT_00588280[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00349e90();
end:
    return DAT_00588280[0];
}
