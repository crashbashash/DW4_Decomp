extern "C" {
void FUN_003b7470(void);
extern struct G *DAT_0058ad20[4];
void *FUN_003b73a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b73a0(void) {
    struct G *g = DAT_0058ad20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b7470();
    }
    return DAT_0058ad20[0];
}
