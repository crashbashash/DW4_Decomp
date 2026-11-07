extern "C" {
void FUN_003b3640(void);
extern struct G *DAT_0058ab50[4];
void *FUN_003b3570(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b3570(void) {
    struct G *g = DAT_0058ab50[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b3640();
    }
    return DAT_0058ab50[0];
}
