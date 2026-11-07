extern "C" {
void FUN_00343ad0(void);
extern struct G *DAT_00587e20[4];
void *FUN_00343a10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00343a10(void) {
    struct G *g = DAT_00587e20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00343ad0();
    }
    return DAT_00587e20[0];
}
