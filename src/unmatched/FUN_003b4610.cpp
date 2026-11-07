extern "C" {
void FUN_003b46e0(void);
extern struct G *DAT_0058ab98[4];
void *FUN_003b4610(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4610(void) {
    struct G *g = DAT_0058ab98[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b46e0();
    }
    return DAT_0058ab98[0];
}
