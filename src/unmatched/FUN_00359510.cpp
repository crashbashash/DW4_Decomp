extern "C" {
void FUN_00359640(void);
extern struct G *DAT_005890c0[4];
void *FUN_00359510(void);
}
struct G { int pad[9]; int f; };
void *FUN_00359510(void) {
    struct G *g = DAT_005890c0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00359640();
    }
    return DAT_005890c0[0];
}
