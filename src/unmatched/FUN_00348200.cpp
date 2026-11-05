extern "C" {
void FUN_00348530(void);
extern struct G *DAT_005881d8[4];
void *FUN_00348200(void);
}
struct G { int pad[9]; int f; };
void *FUN_00348200(void) {
    struct G *g = DAT_005881d8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00348530();
end:
    return DAT_005881d8[0];
}
