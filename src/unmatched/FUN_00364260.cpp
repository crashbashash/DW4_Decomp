extern "C" {
void FUN_00364390(void);
extern struct G *DAT_00589848[4];
void *FUN_00364260(void);
}
struct G { int pad[9]; int f; };
void *FUN_00364260(void) {
    struct G *g = DAT_00589848[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00364390();
    }
    return DAT_00589848[0];
}
