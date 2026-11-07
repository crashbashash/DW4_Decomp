extern "C" {
void FUN_0035b5f0(void);
extern struct G *DAT_005891f0[4];
void *FUN_0035b560(void);
}
struct G { int pad[9]; int f; };
void *FUN_0035b560(void) {
    struct G *g = DAT_005891f0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035b5f0();
    }
    return DAT_005891f0[0];
}
