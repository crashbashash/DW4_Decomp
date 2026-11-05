extern "C" {
void FUN_00354940(void);
extern struct G *DAT_00588d00[4];
void *FUN_00354860(void);
}
struct G { int pad[9]; int f; };
void *FUN_00354860(void) {
    struct G *g = DAT_00588d00[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00354940();
end:
    return DAT_00588d00[0];
}
