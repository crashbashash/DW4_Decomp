extern "C" {
void FUN_003b8c70(void);
extern struct G *DAT_0058ae18[4];
void *FUN_003b8ba0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b8ba0(void) {
    struct G *g = DAT_0058ae18[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b8c70();
    }
    return DAT_0058ae18[0];
}
