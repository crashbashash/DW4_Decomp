extern "C" {
void FUN_00334ec0(void);
extern struct G *DAT_00587668[4];
void *FUN_00334e00(void);
}
struct G { int pad[9]; int f; };
void *FUN_00334e00(void) {
    struct G *g = DAT_00587668[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00334ec0();
    }
    return DAT_00587668[0];
}
