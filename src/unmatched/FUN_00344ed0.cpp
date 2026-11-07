extern "C" {
void FUN_00345010(void);
extern struct G *DAT_00587f10[4];
void *FUN_00344ed0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00344ed0(void) {
    struct G *g = DAT_00587f10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00345010();
    }
    return DAT_00587f10[0];
}
