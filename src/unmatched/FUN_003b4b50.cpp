extern "C" {
void FUN_003b4c30(void);
extern struct G *DAT_0058abb0[4];
void *FUN_003b4b50(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4b50(void) {
    struct G *g = DAT_0058abb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b4c30();
    }
    return DAT_0058abb0[0];
}
