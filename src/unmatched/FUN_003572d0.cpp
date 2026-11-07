extern "C" {
void FUN_00357450(void);
extern struct G *DAT_00588eb0[4];
void *FUN_003572d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003572d0(void) {
    struct G *g = DAT_00588eb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00357450();
    }
    return DAT_00588eb0[0];
}
