extern "C" {
void FUN_00363930(void);
extern struct G *DAT_005897d8[4];
void *FUN_00363850(void);
}
struct G { int pad[9]; int f; };
void *FUN_00363850(void) {
    struct G *g = DAT_005897d8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00363930();
end:
    return DAT_005897d8[0];
}
