extern "C" {
void FUN_00346b70(void);
extern struct G *DAT_00588010[4];
void *FUN_00346ab0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00346ab0(void) {
    struct G *g = DAT_00588010[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00346b70();
end:
    return DAT_00588010[0];
}
