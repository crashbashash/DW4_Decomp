extern "C" {
void FUN_003b8740(void);
extern struct G *DAT_0058adf8[4];
void *FUN_003b8670(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b8670(void) {
    struct G *g = DAT_0058adf8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b8740();
    }
    return DAT_0058adf8[0];
}
