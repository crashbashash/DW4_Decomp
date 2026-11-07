extern "C" {
void FUN_0035fd50(void);
extern struct G *DAT_005894f0[4];
void *FUN_0035fb60(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035fb60(void) {
    struct G *g = DAT_005894f0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035fd50();
    }
    return DAT_005894f0[0];
}
