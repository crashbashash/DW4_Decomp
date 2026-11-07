extern "C" {
void FUN_003b4360(void);
extern struct G *DAT_0058ab88[4];
void *FUN_003b4290(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4290(void) {
    struct G *g = DAT_0058ab88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b4360();
    }
    return DAT_0058ab88[0];
}
