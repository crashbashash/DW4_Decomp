extern "C" {
void FUN_003b7200(void);
extern struct G *DAT_0058ad10[4];
void *FUN_003b7120(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b7120(void) {
    struct G *g = DAT_0058ad10[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b7200();
    }
    return DAT_0058ad10[0];
}
