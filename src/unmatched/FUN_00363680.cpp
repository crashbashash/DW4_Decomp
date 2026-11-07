extern "C" {
void FUN_00363710(void);
extern struct G *DAT_005897d0[4];
void *FUN_00363680(void);
}
struct G { int pad[9]; int f; };
void *FUN_00363680(void) {
    struct G *g = DAT_005897d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00363710();
    }
    return DAT_005897d0[0];
}
