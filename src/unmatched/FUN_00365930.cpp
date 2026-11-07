extern "C" {
void FUN_00365b00(void);
extern struct G *DAT_005898d0[4];
void *FUN_00365930(void);
}
struct G { int pad[9]; int f; };
void *FUN_00365930(void) {
    struct G *g = DAT_005898d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00365b00();
    }
    return DAT_005898d0[0];
}
