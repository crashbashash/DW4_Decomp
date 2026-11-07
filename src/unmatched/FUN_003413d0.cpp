extern "C" {
void FUN_00341500(void);
extern struct G *DAT_00587c18[4];
void *FUN_003413d0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003413d0(void) {
    struct G *g = DAT_00587c18[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00341500();
    }
    return DAT_00587c18[0];
}
