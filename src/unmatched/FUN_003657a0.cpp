extern "C" {
void FUN_00365830(void);
extern struct G *DAT_005898c8[4];
void *FUN_003657a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003657a0(void) {
    struct G *g = DAT_005898c8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00365830();
    }
    return DAT_005898c8[0];
}
