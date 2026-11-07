extern "C" {
void FUN_003653b0(void);
extern struct G *DAT_005898a8[4];
void *FUN_00365280(void);
}
struct G { int pad[9]; int f; };
void *FUN_00365280(void) {
    struct G *g = DAT_005898a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003653b0();
    }
    return DAT_005898a8[0];
}
