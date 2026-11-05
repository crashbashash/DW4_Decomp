extern "C" {
void FUN_00359640(void);
extern struct G *DAT_005890c0[4];
void *FUN_00359510(void);
}
struct G { int pad[9]; int f; };
void *FUN_00359510(void) {
    struct G *g = DAT_005890c0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00359640();
end:
    return DAT_005890c0[0];
}
