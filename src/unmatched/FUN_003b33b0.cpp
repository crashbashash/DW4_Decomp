extern "C" {
void FUN_003b3480(void);
extern struct G *DAT_0058ab48[4];
void *FUN_003b33b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b33b0(void) {
    struct G *g = DAT_0058ab48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b3480();
    }
    return DAT_0058ab48[0];
}
