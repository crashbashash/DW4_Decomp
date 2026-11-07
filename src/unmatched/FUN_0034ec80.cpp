extern "C" {
void FUN_0034ed80(void);
extern struct G *DAT_00588760[4];
void *FUN_0034ec80(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034ec80(void) {
    struct G *g = DAT_00588760[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034ed80();
    }
    return DAT_00588760[0];
}
