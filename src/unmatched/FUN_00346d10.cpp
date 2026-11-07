extern "C" {
void FUN_00346ef0(void);
extern struct G *DAT_00588020[4];
void *FUN_00346d10(void);
}
struct G { int pad[9]; int f; };
void *FUN_00346d10(void) {
    struct G *g = DAT_00588020[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00346ef0();
    }
    return DAT_00588020[0];
}
