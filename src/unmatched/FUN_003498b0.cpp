extern "C" {
void FUN_00349a40(void);
extern struct G *DAT_00588270[4];
void *FUN_003498b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003498b0(void) {
    struct G *g = DAT_00588270[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00349a40();
end:
    return DAT_00588270[0];
}
