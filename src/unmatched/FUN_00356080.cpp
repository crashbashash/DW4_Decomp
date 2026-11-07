extern "C" {
void FUN_003561a0(void);
extern struct G *DAT_00588e10[4];
void *FUN_00356080(void);
}
struct G { int pad[9]; int f; };
void *FUN_00356080(void) {
    struct G *g = DAT_00588e10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003561a0();
    }
    return DAT_00588e10[0];
}
