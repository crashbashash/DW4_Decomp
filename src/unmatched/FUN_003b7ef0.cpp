extern "C" {
void FUN_003b8060(void);
extern struct G *DAT_0058ada0[4];
void *FUN_003b7ef0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b7ef0(void) {
    struct G *g = DAT_0058ada0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b8060();
    }
    return DAT_0058ada0[0];
}
