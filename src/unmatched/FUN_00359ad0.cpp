extern "C" {
void FUN_00359cd0(void);
extern struct G *DAT_005890e8[4];
void *FUN_00359ad0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00359ad0(void) {
    struct G *g = DAT_005890e8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00359cd0();
end:
    return DAT_005890e8[0];
}
