extern "C" {
void FUN_00369f80(void);
extern struct G *DAT_00589d10[4];
void *FUN_00369e50(void);
}
struct G { int pad[9]; int f; };
void *FUN_00369e50(void) {
    struct G *g = DAT_00589d10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00369f80();
    }
    return DAT_00589d10[0];
}
