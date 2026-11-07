extern "C" {
void FUN_0034b560(void);
extern struct G *DAT_00588460[4];
void *FUN_0034b4a0(void);
}
struct G { int pad[9]; int f; };
void *FUN_0034b4a0(void) {
    struct G *g = DAT_00588460[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034b560();
    }
    return DAT_00588460[0];
}
