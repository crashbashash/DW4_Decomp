extern "C" {
void FUN_00335520(void);
extern struct G *DAT_00587730[4];
void *FUN_00335490(void);
}
struct G { int pad[9]; int f; };
void *FUN_00335490(void) {
    struct G *g = DAT_00587730[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00335520();
    }
    return DAT_00587730[0];
}
