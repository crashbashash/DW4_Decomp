extern "C" {
void FUN_003405c0(void);
extern struct G *DAT_00587b88[4];
void *FUN_003404e0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003404e0(void) {
    struct G *g = DAT_00587b88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003405c0();
    }
    return DAT_00587b88[0];
}
