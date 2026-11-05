extern "C" {
void FUN_00367da0(void);
extern struct G *DAT_00589b40[4];
void *FUN_00367d10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00367d10(void) {
    struct G *g = DAT_00589b40[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00367da0();
end:
    return DAT_00589b40[0];
}
