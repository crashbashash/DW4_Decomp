extern "C" {
void FUN_00348530(void);
extern struct G *DAT_005881d8[4];
void *FUN_00348200(void);
}
struct G { int pad[9]; int f; };
void *FUN_00348200(void) {
    struct G *g = DAT_005881d8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00348530();
    }
    return DAT_005881d8[0];
}
