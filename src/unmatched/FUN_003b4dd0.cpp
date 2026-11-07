extern "C" {
void FUN_003b4ea0(void);
extern struct G *DAT_0058abc0[4];
void *FUN_003b4dd0(void);
}
struct G { int pad[9]; int f; };
void *FUN_003b4dd0(void) {
    struct G *g = DAT_0058abc0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b4ea0();
    }
    return DAT_0058abc0[0];
}
