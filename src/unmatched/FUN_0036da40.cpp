extern "C" {
void FUN_0036db70(void);
extern struct G *DAT_0058a010[4];
void *FUN_0036da40(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036da40(void) {
    struct G *g = DAT_0058a010[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036db70();
    }
    return DAT_0058a010[0];
}
