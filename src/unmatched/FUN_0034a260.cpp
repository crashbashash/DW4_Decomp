extern "C" {
void FUN_0034a340(void);
extern struct G *DAT_00588308[4];
void *FUN_0034a260(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034a260(void) {
    struct G *g = DAT_00588308[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034a340();
    }
    return DAT_00588308[0];
}
