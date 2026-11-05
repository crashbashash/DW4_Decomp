extern "C" {
void FUN_00369f80(void);
extern struct G *DAT_00589d10[4];
void *FUN_00369e50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00369e50(void) {
    struct G *g = DAT_00589d10[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00369f80();
end:
    return DAT_00589d10[0];
}
