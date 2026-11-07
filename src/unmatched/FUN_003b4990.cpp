extern "C" {
void FUN_003b4a60(void);
extern struct G *DAT_0058aba8[4];
void *FUN_003b4990(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4990(void) {
    struct G *g = DAT_0058aba8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b4a60();
    }
    return DAT_0058aba8[0];
}
