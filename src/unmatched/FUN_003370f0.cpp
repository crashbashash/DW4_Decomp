extern "C" {
void FUN_003371d0(void);
extern struct G *DAT_005878a8[4];
void *FUN_003370f0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003370f0(void) {
    struct G *g = DAT_005878a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003371d0();
    }
    return DAT_005878a8[0];
}
