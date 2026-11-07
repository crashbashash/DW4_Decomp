extern "C" {
void FUN_0036d940(void);
extern struct G *DAT_0058a008[4];
void *FUN_0036d8b0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036d8b0(void) {
    struct G *g = DAT_0058a008[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036d940();
    }
    return DAT_0058a008[0];
}
