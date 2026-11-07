extern "C" {
void FUN_0034cda0(void);
extern struct G *DAT_00588548[4];
void *FUN_0034cd10(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034cd10(void) {
    struct G *g = DAT_00588548[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034cda0();
    }
    return DAT_00588548[0];
}
